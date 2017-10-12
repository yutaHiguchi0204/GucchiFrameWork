/* =====================================================================
//! @param		�uDeviceResources�v�\�[�X
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "DeviceResources.h"

// ���O���
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		// API �G���[��ߑ�����
		throw std::exception();
	}
}

namespace
{
#if defined(_DEBUG)
	// SDK ���C���[�̃T�|�[�g�����邩�ǂ���
	inline bool SdkLayersAvailable()
	{
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_NULL,			// �n�[�h�E�F�A�f�o�C�X�̍쐬�s�v
			0,
			D3D11_CREATE_DEVICE_DEBUG,		// SDK ���C���[�̃`�F�b�N
			nullptr,						// �ǂ̋@�\���x���ł����p�\
			0,
			D3D11_SDK_VERSION,
			nullptr,						// �f�o�C�X�̃��t�@�����X��ێ�����K�v�͂Ȃ�
			nullptr,						// �@�\���x����m���Ă���K�v�͂Ȃ�
			nullptr							// �f�o�C�X�R���e�L�X�g�̃��t�@�����X��ێ�����K�v�͂Ȃ�
		);

		return SUCCEEDED(hr);
	}
#endif
};

// �R���X�g���N�^
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

// ���p�\�ȃn�[�h�E�F�A�A�_�v�^�̐ݒ�
void DeviceResources::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
{
	// ������Ȃ������ꍇ��nullptr��ݒ�
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
			// �����_�����O�h���C�o�A�_�v�^�͊�{�I�ɑI�����Ȃ�
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

// Direct3D�̃f�o�C�X�ƃR���e�L�X�g���\�����A�n���h�����i�[����
void DeviceResources::CreateDeviceResources()
{
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	if (SdkLayersAvailable())
	{
		// �f�o�b�O�r���h�̏ꍇ��SDK���C���[����ăf�o�b�O��L���ɂ���
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
	else
	{
		OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
	}
#endif

	// DirectX�n�[�h�E�F�A�@�\���x���̐ݒ�
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

	// API �f�o�C�X�I�u�W�F�N�g�Ƃ���ɑΉ�����R���e�L�X�g�̍쐬
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
			d3dDevice_.ReleaseAndGetAddressOf(),	// �쐬���ꂽDirect3D�f�o�C�X�̕ԋp
			&d3dFeatureLevel_,						// �쐬���ꂽ�t���[�`���[���x���̕ԋp
			d3dContext_.ReleaseAndGetAddressOf()	// �f�o�C�X�����R���e�L�X�g�̕ԋp
		);

		if (hr == E_INVALIDARG && featLevelCount > 1)
		{
			assert(s_featureLevels[0] == D3D_FEATURE_LEVEL_11_1);

			// DirectX11�̃v���b�g�t�H�[���� "D3D_FEATURE_LEVEL_11_1" ��F�����Ȃ����߁ADirectX11�̃v���b�g�t�H�[�����g�p�����ɍĎ��s����K�v������
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
		// �����������s�����ꍇ�́AWARP�f�o�C�X�Ƀt�H�[���o�b�N����
		// WARP�f�o�C�X�̏ڍ�: http://go.microsoft.com/fwlink/?LinkId=286690
		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_WARP,		// �n�[�h�E�F�A�f�o�C�X�̑����WARP�f�o�C�X���쐬����
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

			// DirectX11�̃v���b�g�t�H�[���� "D3D_FEATURE_LEVEL_11_1" ��F�����Ȃ����߁ADirectX11�̃v���b�g�t�H�[�����g�p�����ɍĎ��s����K�v������
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

	// �g�p�\�ȏꍇ�ADirect3D 11.1 �̃C���^�t�F�[�X����肷��
	if (SUCCEEDED(d3dDevice_.As(&d3dDevice1_)))
	{
		(void)d3dContext_.As(&d3dContext1_);
		(void)d3dContext_.As(&d3dAnnotation_);
	}

	commonStates_ = std::make_unique<CommonStates>(d3dDevice_.Get());
}

// �����̃��\�[�X�̓E�C���h�E�T�C�Y���ύX����邽�тɍĐݒ肷���p������
void DeviceResources::CreateWindowSizeDependentResources()
{
	if (!window_)
	{
		throw std::exception("Call SetWindow with a valid Win32 window handle");
	}

	// �O�̃E�B���h�E�T�C�Y�ɓ��L�̃R���e�L�X�g���N���A����
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
		// �X���b�v�`�F�[�������łɑ��݂��Ă���ꍇ�́A�T�C�Y��ύX����
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
			// ���炩�̗��R�Ńf�o�C�X���폜���ꂽ�ꍇ�́A�V�����f�o�C�X�ƃX���b�v�`�F�[�����쐬�����p������
			HandleDeviceLost();

			// ���\�b�h�̎��s���p�����Ȃ�
			// �V�����f�o�C�X�𐳂����Z�b�g�A�b�v���Ă�������
			return;
		}
		else
		{
			ThrowIfFailed(hr);
		}
	}
	else
	{
		// ������Direct3D�f�o�C�X�Ɠ����A�_�v�^���g�p���ĐV�����A�_�v�^���쐬

		// Direct3D�f�o�C�X�̍쐬�Ɏg�p���ꂽDXGI�t�@�N�g���̎擾
		ComPtr<IDXGIDevice1> dxgiDevice;
		ThrowIfFailed(d3dDevice_.As(&dxgiDevice));

		ComPtr<IDXGIAdapter> dxgiAdapter;
		ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

		ComPtr<IDXGIFactory1> dxgiFactory;
		ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

		ComPtr<IDXGIFactory2> dxgiFactory2;
		if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
		{
			// DirectX 11.1 ���O�̃o�[�W������
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

			// Win32 �E�C���h�E����X���b�v�`�F�[�����쐬
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

		// �r���I�ȃt���X�N���[�����[�h���T�|�[�g���Ă��Ȃ��̂ŁADXGI��ALT + ENTER�V���[�g�J�b�g�ɉ������Ȃ��悤�ɂ���
		ThrowIfFailed(dxgiFactory->MakeWindowAssociation(window_, DXGI_MWA_NO_ALT_ENTER));
	}

	// �X���b�v�`�F�[���o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g�r���[�̍쐬
	ThrowIfFailed(swapChain_->GetBuffer(0, IID_PPV_ARGS(renderTarget_.ReleaseAndGetAddressOf())));

	ThrowIfFailed(d3dDevice_->CreateRenderTargetView(
		renderTarget_.Get(),
		nullptr,
		d3dRenderTargetView_.ReleaseAndGetAddressOf()
	));

	if (depthBufferFormat_ != DXGI_FORMAT_UNKNOWN)
	{
		// �K�v�ɉ����āA���s���X�e���V���r���[���쐬
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			depthBufferFormat_,
			backBufferWidth,
			backBufferHeight,
			1,							// ���̐[�x�X�e���V���ɂ̓e�N�X�`�����P�����Ȃ�
			1,							// �P��̃~�b�v�}�b�v���x�����g�p
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

	// 3D�����_�����O�r���[�|�[�g��ݒ肵�ăE�B���h�E�S�̂��^�[�Q�b�g�ɂ���
	screenViewport_ = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		static_cast<float>(backBufferWidth),
		static_cast<float>(backBufferHeight)
	);
}

// Win32�E�B���h�E���쐬�i�܂��͍č쐬�j���ꂽ�Ƃ��ɌĂ΂��
void DeviceResources::SetWindow(HWND window, int width, int height)
{
	window_ = window;

	outputSize_.left = outputSize_.top = 0;
	outputSize_.right = width;
	outputSize_.bottom = height;
}

// Win32�E�C���h�E�̃T�C�Y���ύX���ꂽ�Ƃ��ɌĂ΂��
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

// ���ׂẴf�o�C�X���\�[�X���č쐬���A���݂̏�Ԃ܂Ŗ߂�
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

// IDeviceNotify�̓o�^
void DeviceResources::RegisterDeviceNotify(IDeviceNotify* deviceNotify)
{
	deviceNotify_ = deviceNotify;
}

// �X���b�v�`�F�[���̓��e����ʂɕ\��
void DeviceResources::Present()
{
	// VSync�܂Ńu���b�N����悤��DXGI�Ɏw�����A����VSync�܂ŃX���[�v��Ԃɂ���
	// ����ɂ��A�X�N���[���ɕ\������Ȃ��t���[���������_�����O����T�C�N���𖳑ʂɂ��邱�Ƃ͂Ȃ�
	HRESULT hr = swapChain_->Present(1, 0);

	if (d3dContext1_)
	{
		// �����_�[�^�[�Q�b�g�̓��e��j��
		// �_�[�e�B�܂��̓X�N���[����`���g�p����Ă���ꍇ�́A���̌Ăяo�����폜����K�v������
		d3dContext1_->DiscardView(d3dRenderTargetView_.Get());

		if (d3dDepthStencilView_)
		{
			// �[�x�X�e���V���̓��e��j��
			d3dContext1_->DiscardView(d3dDepthStencilView_.Get());
		}
	}

	// �ؒf�܂��̓h���C�o�̃A�b�v�O���[�h�ɂ���ăf�o�C�X���폜���ꂽ�ꍇ�́A���ׂẴf�o�C�X���\�[�X���č쐬����K�v������
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