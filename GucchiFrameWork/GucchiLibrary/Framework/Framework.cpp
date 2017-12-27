/* =====================================================================
//! @param		�uFramework�v�\�[�X
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Framework.h"
#include <string>
#include "../Common/Constant.h"
#include "../Common/DebugSwitch.h"
#include "../InputTools/KeyboardUtil.h"
#include "../InputTools/MouseUtil.h"
#include "../Utility/MemoryLeakDetector.h"

// ���O���
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;

// �E�C���h�E�v���V�[�W��
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
			// �t���X�N���[�����[�h�ialt + Enter�j����
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
		// ���j���[���A�N�e�B�u��Ԃł����[�U���L�[���������ꍇ�A�A�N�Z�����[�^�L�[�ɑΉ����Ă��Ȃ����߁A
		// �G���[������d�l�ł����A����𖳎����܂��B
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

// �R���X�g���N�^
Framework::Framework(HINSTANCE hInstance, int nCmdShow)
{
	// �N���X�̓o�^
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

	// �E�C���h�E�̍쐬
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

	// �f�o�C�X�c�[���쐬
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();
	dxtk.Initialize(deviceResources.GetD3DDevice(), deviceResources.GetD3DDeviceContext());

	// �C���v�b�g�c�[���쐬
	KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
	keyboard.Initialize();
	MouseUtil& mouse = MouseUtil::GetInstance();
	mouse.Initialize();

	// FPS�\���L��
	isDispFPS_ = true;

	// ���������[�N���o����
#if defined(MODE_DEBUG)
	SetUpMemoryLeakDetector();
#endif
}

#pragma region Frame Update
// �Q�[�����[�v���s
void Framework::Tick()
{
	timer_.Tick([&]()
	{
		Update(timer_);

		// �C���v�b�g�c�[���̍X�V
		KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
		keyboard.Update();
		MouseUtil& mouse = MouseUtil::GetInstance();
		mouse.Update();
	});

#if DRAW_WINDOW_FPS == 1
	// FPS���^�C�g���o�[�ɕ\��
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
// �`�揈��
void Framework::PreRender()
{
	// �X�V�O�̕`��h�~
	if (timer_.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXBeginEvent(L"Render");
}

// �`��I������
void Framework::PostRender()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXEndEvent();

	// �V�����t���[���\��
	deviceResources.Present();
}

// �o�b�N�o�b�t�@�N���A
void Framework::Clear()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	deviceResources.PIXBeginEvent(L"Clear");

	// �r���[�̃N���A
	auto context		= deviceResources.GetD3DDeviceContext();
	auto renderTarget   = deviceResources.GetRenderTargetView();
	auto depthStencil   = deviceResources.GetDepthStencilView();

	// �E�C���h�E�ݒ�
	//context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);			// �f�t�H���g
	context->ClearRenderTargetView(renderTarget, Colors::Black);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// �r���[�|�[�g�ݒ�
	auto viewport = deviceResources.GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	deviceResources.PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// ���b�Z�[�W�֘A
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

// �v���p�e�B
void Framework::GetDefaultSize(int& width, int& height) const
{
	// �E�C���h�E�T�C�Y��ύX�������ꍇ�͒萔�w�b�_����ύX���Ă�������
	// ���ŏ��T�C�Y�́i320�~200�j
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// �f�o�C�X�ˑ��̃��\�[�X
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