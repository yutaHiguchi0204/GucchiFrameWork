/* =====================================================================
//! @param		「Framework」ソース
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */

// ヘッダファイルのインクルード
#include "Framework.h"
#include <string>
#include "../Common/Constant.h"
#include "../Common/DebugSwitch.h"
#include "../InputTools/KeyboardUtil.h"
#include "../InputTools/MouseUtil.h"
#include "../Utility/MemoryLeakDetector.h"

// 名前空間
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;

// ウインドウプロシージャ
LRESULT CALLBACK Framework::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static bool s_in_sizemove = false;
	static bool s_in_suspend = false;
	static bool s_minimized = false;
	static bool s_fullscreen = false;

	auto framework = reinterpret_cast<Framework*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			if (!s_minimized)
			{
				s_minimized = true;
				if (!s_in_suspend && framework)
					framework->OnSuspending();
				s_in_suspend = true;
			}
		}
		else if (s_minimized)
		{
			s_minimized = false;
			if (s_in_suspend && framework)
				framework->OnResuming();
			s_in_suspend = false;
		}
		else if (!s_in_sizemove && framework)
		{
			framework->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	case WM_ENTERSIZEMOVE:
		s_in_sizemove = true;
		break;

	case WM_EXITSIZEMOVE:
		s_in_sizemove = false;
		if (framework)
		{
			RECT rc;
			GetClientRect(hWnd, &rc);

			framework->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
		}
		break;

	case WM_GETMINMAXINFO:
	{
		auto info = reinterpret_cast<MINMAXINFO*>(lParam);
		info->ptMinTrackSize.x = 320;
		info->ptMinTrackSize.y = 200;
	}
	break;

	case WM_ACTIVATEAPP:
		Mouse::ProcessMessage(message, wParam, lParam);
		Keyboard::ProcessMessage(message, wParam, lParam);

		if (framework)
		{
			if (wParam)
			{
				framework->OnActivated();
			}
			else
			{
				framework->OnDeactivated();
			}
		}
		break;

	case WM_POWERBROADCAST:
		switch (wParam)
		{
		case PBT_APMQUERYSUSPEND:
			if (!s_in_suspend && framework)
				framework->OnSuspending();
			s_in_suspend = true;
			return TRUE;

		case PBT_APMRESUMESUSPEND:
			if (!s_minimized)
			{
				if (s_in_suspend && framework)
					framework->OnResuming();
				s_in_suspend = false;
			}
			return TRUE;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SYSKEYDOWN:
		Keyboard::ProcessMessage(message, wParam, lParam);
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// フルスクリーンモード（alt + Enter）実装
			if (s_fullscreen)
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

				int width = 800;
				int height = 600;
				if (framework)
					framework->GetDefaultSize(width, height);

				ShowWindow(hWnd, SW_SHOWNORMAL);

				SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			else
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, 0);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

				SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

				ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			}

			s_fullscreen = !s_fullscreen;
		}
		break;

	case WM_MENUCHAR:
		// メニューがアクティブ状態でかつユーザがキーを押した場合、アクセラレータキーに対応していないため、
		// エラー音が鳴る仕様ですが、それを無視します。
		return MAKELRESULT(0, MNC_CLOSE);
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// コンストラクタ
Framework::Framework(HINSTANCE hInstance, int nCmdShow)
{
	// クラスの登録
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, L"IDI_ICON");
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"GameWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
	if (!RegisterClassEx(&wcex))
		throw 0;

	// ウインドウの作成
	int w, h;
	GetDefaultSize(w, h);

	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = static_cast<LONG>(w);
	rc.bottom = static_cast<LONG>(h);

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	hwnd_ = CreateWindowEx(0, wcex.lpszClassName, L"GucchiFrameWork", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	if (!hwnd_)
		throw 0;

	ShowWindow(hwnd_, nCmdShow);

	SetWindowLongPtr(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	GetClientRect(hwnd_, &rc);

	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.RegisterDeviceNotify(this);

	deviceResources.SetWindow(hwnd_, w, h);

	deviceResources.CreateDeviceResources();
	CreateDeviceDependentResources();

	deviceResources.CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// デバイスツール作成
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();
	dxtk.Initialize(deviceResources.GetD3DDevice(), deviceResources.GetD3DDeviceContext());

	// インプットツール作成
	KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
	keyboard.Initialize();
	MouseUtil& mouse = MouseUtil::GetInstance();
	mouse.Initialize();

	// FPS表示有効
	isDispFPS_ = true;

	// メモリリーク検出準備
#if defined(MODE_DEBUG)
	SetUpMemoryLeakDetector();
#endif
}

#pragma region Frame Update
// ゲームループ実行
void Framework::Tick()
{
	timer_.Tick([&]()
	{
		Update(timer_);

		// インプットツールの更新
		KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
		keyboard.Update();
		MouseUtil& mouse = MouseUtil::GetInstance();
		mouse.Update();
	});

#if DRAW_WINDOW_FPS == 1
	// FPSをタイトルバーに表示
	if (isDispFPS_)
	{
		unsigned int fps = timer_.GetFramesPerSecond();
		std::wstring str = L"FPS:" + std::to_wstring(fps);
		SetWindowText(hwnd_, str.c_str());
	}
#endif

	PreRender();
	Render();
	PostRender();
}
#pragma endregion

#pragma region Frame Render
// 描画処理
void Framework::PreRender()
{
	// 更新前の描画防止
	if (timer_.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXBeginEvent(L"Render");
}

// 描画終了処理
void Framework::PostRender()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXEndEvent();

	// 新しいフレーム表示
	deviceResources.Present();
}

// バックバッファクリア
void Framework::Clear()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXBeginEvent(L"Clear");

	// ビューのクリア
	auto context		= deviceResources.GetD3DDeviceContext();
	auto renderTarget   = deviceResources.GetRenderTargetView();
	auto depthStencil   = deviceResources.GetDepthStencilView();

	// ウインドウ設定
	//context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);			// デフォルト
	context->ClearRenderTargetView(renderTarget, Colors::Black);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// ビューポート設定
	auto viewport = deviceResources.GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	deviceResources.PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージ関連
void Framework::OnActivated()
{
#if defined(MODE_DEBUG)
	OutputDebugString(L"Framework is becoming active window.");
#endif
}

void Framework::OnDeactivated()
{
#if defined(MODE_DEBUG)
	OutputDebugString(L"Framework is becoming background window.");
#endif
}

void Framework::OnSuspending()
{
#if defined(MODE_DEBUG)
	OutputDebugString(L"Framework is being power-suspended (or minimized).");
#endif
}

void Framework::OnResuming()
{
#if defined(MODE_DEBUG)
	OutputDebugString(L"Framework is being power-resumed (or returning from minimize).");
#endif
	timer_.ResetElapsedTime();
}

void Framework::OnWindowSizeChanged(int width, int height)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	if (!deviceResources.WindowSizeChanged(width, height))
		return;

#if defined(MODE_DEBUG)
	OutputDebugString(L"Framework window is being resized.");
#endif

	CreateWindowSizeDependentResources();
}

// プロパティ
void Framework::GetDefaultSize(int& width, int& height) const
{
	// ウインドウサイズを変更したい場合は定数ヘッダから変更してください
	// ※最小サイズは（320×200）
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// デバイス依存のリソース
void Framework::OnDeviceRestored()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

void Framework::CreateDeviceDependentResources()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	ID3D11Device* device = deviceResources.GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
}
#pragma endregion