/* =====================================================================
//! @param		「DeviceResources」ソース
//! @create		樋口 裕太
//! @date		17/10/09
===================================================================== */

// ヘッダファイルのインクルード
#include "DeviceResources.h"

// 名前空間
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		// API エラーを捕捉する
		throw std::exception();
	}
}

namespace
{
#if defined(_DEBUG)
	// SDK レイヤーのサポートがあるかどうか
	inline bool SdkLayersAvailable()
	{
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_NULL,			// ハードウェアデバイスの作成不要
			0,
			D3D11_CREATE_DEVICE_DEBUG,		// SDK レイヤーのチェック
			nullptr,						// どの機能レベルでも利用可能
			0,
			D3D11_SDK_VERSION,
			nullptr,						// デバイスのリファレンスを保持する必要はない
			nullptr,						// 機能レベルを知っている必要はない
			nullptr							// デバイスコンテキストのリファレンスを保持する必要はない
		);

		return SUCCEEDED(hr);
	}
#endif
};

// コンストラクタ
//DeviceResources::DeviceResources(DXGI_FORMAT backBufferFormat, DXGI_FORMAT depthBufferFormat, UINT backBufferCount, D3D_FEATURE_LEVEL minFeatureLevel)
//	: screenViewport_{}
//	, backBufferFormat_(backBufferFormat)
//	, depthBufferFormat_(depthBufferFormat)
//	, backBufferCount_(backBufferCount)
//	, d3dMinFeatureLevel_(minFeatureLevel)
//	, window_(0)
//	, d3dFeatureLevel_(D3D_FEATURE_LEVEL_9_1)
//	, outputSize_{ 0, 0, 1, 1 }
//	, deviceNotify_(nullptr)
//{
//}

// 利用可能なハードウェアアダプタの設定
void DeviceResources::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
{
	// 見つからなかった場合はnullptrを設定
	*ppAdapter = nullptr;

	ComPtr<IDXGIFactory1> dxgiFactory;
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

	ComPtr<IDXGIAdapter1> adapter;
	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != dxgiFactory->EnumAdapters1(adapterIndex, adapter.ReleaseAndGetAddressOf()); adapterIndex++)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// レンダリングドライバアダプタは基本的に選択しない
			continue;
		}

#ifdef _DEBUG
		wchar_t buff[256] = {};
		swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
		OutputDebugStringW(buff);
#endif
		break;
	}

	*ppAdapter = adapter.Detach();
}

// Direct3Dのデバイスとコンテキストを構成し、ハンドルを格納する
void DeviceResources::CreateDeviceResources()
{
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	if (SdkLayersAvailable())
	{
		// デバッグビルドの場合はSDKレイヤーを介してデバッグを有効にする
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
	else
	{
		OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
	}
#endif

	// DirectXハードウェア機能レベルの設定
	static const D3D_FEATURE_LEVEL s_featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	UINT featLevelCount = 0;
	for (; featLevelCount < _countof(s_featureLevels); ++featLevelCount)
	{
		if (s_featureLevels[featLevelCount] < d3dMinFeatureLevel_)
			break;
	}

	if (!featLevelCount)
	{
		throw std::out_of_range("minFeatureLevel too high");
	}

	ComPtr<IDXGIAdapter1> adapter;
	GetHardwareAdapter(adapter.GetAddressOf());

	// API デバイスオブジェクトとそれに対応するコンテキストの作成
	HRESULT hr = E_FAIL;
	if (adapter)
	{
		hr = D3D11CreateDevice(
			adapter.Get(),
			D3D_DRIVER_TYPE_UNKNOWN,
			0,
			creationFlags,
			s_featureLevels,
			featLevelCount,
			D3D11_SDK_VERSION,
			d3dDevice_.ReleaseAndGetAddressOf(),	// 作成されたDirect3Dデバイスの返却
			&d3dFeatureLevel_,						// 作成されたフューチャーレベルの返却
			d3dContext_.ReleaseAndGetAddressOf()	// デバイス即時コンテキストの返却
		);

		if (hr == E_INVALIDARG && featLevelCount > 1)
		{
			assert(s_featureLevels[0] == D3D_FEATURE_LEVEL_11_1);

			// DirectX11のプラットフォームは "D3D_FEATURE_LEVEL_11_1" を認識しないため、DirectX11のプラットフォームを使用せずに再試行する必要がある
			hr = D3D11CreateDevice(
				adapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				creationFlags,
				&s_featureLevels[1],
				featLevelCount - 1,
				D3D11_SDK_VERSION,
				d3dDevice_.ReleaseAndGetAddressOf(),
				&d3dFeatureLevel_,
				d3dContext_.ReleaseAndGetAddressOf()
			);
		}
	}
#if defined(NDEBUG)
	else
	{
		throw std::exception("No Direct3D hardware device found");
	}
#else
	if (FAILED(hr))
	{
		// 初期化が失敗した場合は、WARPデバイスにフォールバックする
		// WARPデバイスの詳細: http://go.microsoft.com/fwlink/?LinkId=286690
		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_WARP,		// ハードウェアデバイスの代わりにWARPデバイスを作成する
			0,
			creationFlags,
			s_featureLevels,
			featLevelCount,
			D3D11_SDK_VERSION,
			d3dDevice_.ReleaseAndGetAddressOf(),
			&d3dFeatureLevel_,
			d3dContext_.ReleaseAndGetAddressOf()
		);

		if (hr == E_INVALIDARG && featLevelCount > 1)
		{
			assert(s_featureLevels[0] == D3D_FEATURE_LEVEL_11_1);

			// DirectX11のプラットフォームは "D3D_FEATURE_LEVEL_11_1" を認識しないため、DirectX11のプラットフォームを使用せずに再試行する必要がある
			hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP,
				nullptr,
				creationFlags,
				&s_featureLevels[1],
				featLevelCount - 1,
				D3D11_SDK_VERSION,
				d3dDevice_.ReleaseAndGetAddressOf(),
				&d3dFeatureLevel_,
				d3dContext_.ReleaseAndGetAddressOf()
			);
		}

		if (SUCCEEDED(hr))
		{
			OutputDebugStringA("Direct3D Adapter - WARP\n");
		}
	}
#endif

	ThrowIfFailed(hr);

#ifndef NDEBUG
	ComPtr<ID3D11Debug> d3dDebug;
	if (SUCCEEDED(d3dDevice_.As(&d3dDebug)))
	{
		ComPtr<ID3D11InfoQueue> d3dInfoQueue;
		if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
		{
#ifdef _DEBUG
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
			D3D11_MESSAGE_ID hide[] =
			{
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
			};
			D3D11_INFO_QUEUE_FILTER filter = {};
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			d3dInfoQueue->AddStorageFilterEntries(&filter);
		}
	}
#endif

	// 使用可能な場合、Direct3D 11.1 のインタフェースを入手する
	if (SUCCEEDED(d3dDevice_.As(&d3dDevice1_)))
	{
		(void)d3dContext_.As(&d3dContext1_);
		(void)d3dContext_.As(&d3dAnnotation_);
	}

	commonStates_ = std::make_unique<CommonStates>(d3dDevice_.Get());
}

// これらのリソースはウインドウサイズが変更されるたびに再設定する費用がある
void DeviceResources::CreateWindowSizeDependentResources()
{
	if (!window_)
	{
		throw std::exception("Call SetWindow with a valid Win32 window handle");
	}

	// 前のウィンドウサイズに特有のコンテキストをクリアする
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	d3dContext_->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
	d3dRenderTargetView_.Reset();
	d3dDepthStencilView_.Reset();
	renderTarget_.Reset();
	depthStencil_.Reset();
	d3dContext_->Flush();

	// Determine the render target size in pixels.
	UINT backBufferWidth = std::max<UINT>(outputSize_.right - outputSize_.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize_.bottom - outputSize_.top, 1);

	if (swapChain_)
	{
		// スワップチェーンがすでに存在している場合は、サイズを変更する
		HRESULT hr = swapChain_->ResizeBuffers(
			backBufferCount_,
			backBufferWidth,
			backBufferHeight,
			backBufferFormat_,
			0
		);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
#ifdef _DEBUG
			char buff[64] = {};
			sprintf_s(buff, "Device Lost on ResizeBuffers: Reason code 0x%08X\n", (hr == DXGI_ERROR_DEVICE_REMOVED) ? d3dDevice_->GetDeviceRemovedReason() : hr);
			OutputDebugStringA(buff);
#endif
			// 何らかの理由でデバイスが削除された場合は、新しいデバイスとスワップチェーンを作成する費用がある
			HandleDeviceLost();

			// メソッドの実行を継続しない
			// 新しいデバイスを正しくセットアップしてください
			return;
		}
		else
		{
			ThrowIfFailed(hr);
		}
	}
	else
	{
		// 既存のDirect3Dデバイスと同じアダプタを使用して新しいアダプタを作成

		// Direct3Dデバイスの作成に使用されたDXGIファクトリの取得
		ComPtr<IDXGIDevice1> dxgiDevice;
		ThrowIfFailed(d3dDevice_.As(&dxgiDevice));

		ComPtr<IDXGIAdapter> dxgiAdapter;
		ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

		ComPtr<IDXGIFactory1> dxgiFactory;
		ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

		ComPtr<IDXGIFactory2> dxgiFactory2;
		if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
		{
			// DirectX 11.1 か前のバージョンか
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
			swapChainDesc.Width = backBufferWidth;
			swapChainDesc.Height = backBufferHeight;
			swapChainDesc.Format = backBufferFormat_;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = backBufferCount_;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
			fsSwapChainDesc.Windowed = TRUE;

			// Win32 ウインドウからスワップチェーンを作成
			ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
				d3dDevice_.Get(),
				window_,
				&swapChainDesc,
				&fsSwapChainDesc,
				nullptr, swapChain1_.ReleaseAndGetAddressOf()
			));

			ThrowIfFailed(swapChain1_.As(&swapChain_));
		}
		else
		{
			// DirectX 11.0
			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			swapChainDesc.BufferDesc.Width = backBufferWidth;
			swapChainDesc.BufferDesc.Height = backBufferHeight;
			swapChainDesc.BufferDesc.Format = backBufferFormat_;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = backBufferCount_;
			swapChainDesc.OutputWindow = window_;
			swapChainDesc.Windowed = TRUE;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			ThrowIfFailed(dxgiFactory->CreateSwapChain(
				d3dDevice_.Get(),
				&swapChainDesc,
				swapChain_.ReleaseAndGetAddressOf()
			));
		}

		// 排他的なフルスクリーンモードをサポートしていないので、DXGIがALT + ENTERショートカットに応答しないようにする
		ThrowIfFailed(dxgiFactory->MakeWindowAssociation(window_, DXGI_MWA_NO_ALT_ENTER));
	}

	// スワップチェーンバックバッファのレンダーターゲットビューの作成
	ThrowIfFailed(swapChain_->GetBuffer(0, IID_PPV_ARGS(renderTarget_.ReleaseAndGetAddressOf())));

	ThrowIfFailed(d3dDevice_->CreateRenderTargetView(
		renderTarget_.Get(),
		nullptr,
		d3dRenderTargetView_.ReleaseAndGetAddressOf()
	));

	if (depthBufferFormat_ != DXGI_FORMAT_UNKNOWN)
	{
		// 必要に応じて、奥行きステンシルビューを作成
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			depthBufferFormat_,
			backBufferWidth,
			backBufferHeight,
			1,							// この深度ステンシルにはテクスチャが１つしかない
			1,							// 単一のミップマップレベルを使用
			D3D11_BIND_DEPTH_STENCIL
		);

		ThrowIfFailed(d3dDevice_->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			depthStencil_.ReleaseAndGetAddressOf()
		));

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		ThrowIfFailed(d3dDevice_->CreateDepthStencilView(
			depthStencil_.Get(),
			&depthStencilViewDesc,
			d3dDepthStencilView_.ReleaseAndGetAddressOf()
		));
	}

	// 3Dレンダリングビューポートを設定してウィンドウ全体をターゲットにする
	screenViewport_ = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		static_cast<float>(backBufferWidth),
		static_cast<float>(backBufferHeight)
	);
}

// Win32ウィンドウが作成（または再作成）されたときに呼ばれる
void DeviceResources::SetWindow(HWND window, int width, int height)
{
	window_ = window;

	outputSize_.left = outputSize_.top = 0;
	outputSize_.right = width;
	outputSize_.bottom = height;
}

// Win32ウインドウのサイズが変更されたときに呼ばれる
bool DeviceResources::WindowSizeChanged(int width, int height)
{
	RECT newRc;

	newRc.left = newRc.top = 0;
	newRc.right = width;
	newRc.bottom = height;

	if (newRc == outputSize_)
	{
		return false;
	}

	outputSize_ = newRc;

	CreateWindowSizeDependentResources();

	return true;
}

// すべてのデバイスリソースを再作成し、現在の状態まで戻す
void DeviceResources::HandleDeviceLost()
{
	if (deviceNotify_)
	{
		deviceNotify_->OnDeviceLost();
	}

	d3dDepthStencilView_.Reset();
	d3dRenderTargetView_.Reset();
	renderTarget_.Reset();
	depthStencil_.Reset();
	swapChain_.Reset();
	swapChain1_.Reset();
	d3dContext_.Reset();
	d3dContext1_.Reset();
	d3dAnnotation_.Reset();
	d3dDevice1_.Reset();

#ifdef _DEBUG
	{
		ComPtr<ID3D11Debug> d3dDebug;
		if (SUCCEEDED(d3dDevice_.As(&d3dDebug)))
		{
			d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY);
		}
	}
#endif

	d3dDevice_.Reset();

	CreateDeviceResources();
	CreateWindowSizeDependentResources();

	if (deviceNotify_)
	{
		deviceNotify_->OnDeviceRestored();
	}
}

// IDeviceNotifyの登録
void DeviceResources::RegisterDeviceNotify(IDeviceNotify* deviceNotify)
{
	deviceNotify_ = deviceNotify;
}

// スワップチェーンの内容を画面に表示
void DeviceResources::Present()
{
	// VSyncまでブロックするようにDXGIに指示し、次のVSyncまでスリープ状態にする
	// これにより、スクリーンに表示されないフレームをレンダリングするサイクルを無駄にすることはない
	HRESULT hr = swapChain_->Present(1, 0);

	if (d3dContext1_)
	{
		// レンダーターゲットの内容を破棄
		// ダーティまたはスクロール矩形が使用されている場合は、この呼び出しを削除する必要がある
		d3dContext1_->DiscardView(d3dRenderTargetView_.Get());

		if (d3dDepthStencilView_)
		{
			// 深度ステンシルの内容を破棄
			d3dContext1_->DiscardView(d3dDepthStencilView_.Get());
		}
	}

	// 切断またはドライバのアップグレードによってデバイスが削除された場合は、すべてのデバイスリソースを再作成する必要がある
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
#ifdef _DEBUG
		char buff[64] = {};
		sprintf_s(buff, "Device Lost on Present: Reason code 0x%08X\n", (hr == DXGI_ERROR_DEVICE_REMOVED) ? d3dDevice_->GetDeviceRemovedReason() : hr);
		OutputDebugStringA(buff);
#endif
		HandleDeviceLost();
	}
	else
	{
		ThrowIfFailed(hr);
	}
}