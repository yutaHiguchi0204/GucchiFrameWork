/* =====================================================================
//! @param		�uDeviceResources�v�w�b�_
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <windows.h>
#include <wrl/client.h>

#include <algorithm>
#include <assert.h>
#include <memory>
#include <stdexcept>
#include <string>

#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <VertexTypes.h>

#include "SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		IDeviceNotify �N���X�iinterface�j
	// @content		DeviceResources�����L����f�o�C�X�쐬�E�폜���m�p�C���^�t�F�[�X
	*/
	interface IDeviceNotify
	{
		virtual void OnDeviceLost() = 0;
		virtual void OnDeviceRestored() = 0;
	};

	/*
	// @class		DeviceResources �N���X�iSingleton�j
	// @content		�f�o�C�X���\�[�X�֘A
	// @use			�f�o�C�X��R���e�L�X�g�A�R�����X�e�[�g�����K�v�ȏꍇ�����p����
	*/
	class DeviceResources : public SingletonDirector<DeviceResources>
	{
	private:
		// �R�c�I�u�W�F�N�g�֌W
		Microsoft::WRL::ComPtr<ID3D11Device>						d3dDevice_;
		Microsoft::WRL::ComPtr<ID3D11Device1>						d3dDevice1_;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>					d3dContext_;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>				d3dContext1_;
		Microsoft::WRL::ComPtr<IDXGISwapChain>						swapChain_;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>						swapChain1_;
		Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation>			d3dAnnotation_;

		// Direct3D �����_�����O�f�o�C�X
		Microsoft::WRL::ComPtr<ID3D11Texture2D>						renderTarget_;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>						depthStencil_;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>				d3dRenderTargetView_;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>				d3dDepthStencilView_;
		D3D11_VIEWPORT												screenViewport_;

		// Direct3D �v���p�e�B
		DXGI_FORMAT													backBufferFormat_;
		DXGI_FORMAT													depthBufferFormat_;
		UINT														backBufferCount_;
		D3D_FEATURE_LEVEL											d3dMinFeatureLevel_;

		// �L���b�V���f�o�C�X�v���p�e�B
		HWND														window_;
		D3D_FEATURE_LEVEL											d3dFeatureLevel_;
		RECT														outputSize_;

		// DeviceResources�̕ێ�
		IDeviceNotify*												deviceNotify_;

		// �R�����X�e�[�g
		std::unique_ptr<DirectX::CommonStates>						commonStates_;

	private:
		friend class SingletonDirector<DeviceResources>;

		DeviceResources(
			DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
			DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT,
			UINT backBufferCount = 2,
			D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_9_1
		);
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);

	public:
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();
		void SetWindow(HWND window, int width, int height);
		bool WindowSizeChanged(int width, int height);
		void HandleDeviceLost();
		void RegisterDeviceNotify(IDeviceNotify* deviceNotify);
		void Present();

		// Device �A�N�Z�T��
		RECT GetOutputSize() const { return outputSize_; }

		// Direct3D �A�N�Z�T��
		ID3D11Device*				GetD3DDevice() const				{ return d3dDevice_.Get(); }
		ID3D11Device1*				GetD3DDevice1() const				{ return d3dDevice1_.Get(); }
		ID3D11DeviceContext*		GetD3DDeviceContext() const			{ return d3dContext_.Get(); }
		ID3D11DeviceContext1*		GetD3DDeviceContext1() const		{ return d3dContext1_.Get(); }
		IDXGISwapChain*				GetSwapChain() const				{ return swapChain_.Get(); }
		IDXGISwapChain1*			GetSwapChain1() const				{ return swapChain1_.Get(); }
		D3D_FEATURE_LEVEL			GetDeviceFeatureLevel() const		{ return d3dFeatureLevel_; }
		ID3D11Texture2D*			GetRenderTarget() const				{ return renderTarget_.Get(); }
		ID3D11Texture2D*			GetDepthStencil() const				{ return depthStencil_.Get(); }
		ID3D11RenderTargetView*		GetRenderTargetView() const			{ return d3dRenderTargetView_.Get(); }
		ID3D11DepthStencilView*		GetDepthStencilView() const			{ return d3dDepthStencilView_.Get(); }
		DXGI_FORMAT					GetBackBufferFormat() const			{ return backBufferFormat_; }
		DXGI_FORMAT					GetDepthBufferFormat() const		{ return depthBufferFormat_; }
		D3D11_VIEWPORT				GetScreenViewport() const			{ return screenViewport_; }
		UINT						GetBackBufferCount() const			{ return backBufferCount_; }
		DirectX::CommonStates*		GetCommonStates() const				{ return commonStates_.get(); }
		HWND						GetWindow() const					{ return window_; }

		// �p�t�H�[�}���X�C�x���g
		void PIXBeginEvent(_In_z_ const wchar_t* name)
		{
			if (d3dAnnotation_)
			{
				d3dAnnotation_->BeginEvent(name);
			}
		}

		void PIXEndEvent()
		{
			if (d3dAnnotation_)
			{
				d3dAnnotation_->EndEvent();
			}
		}

		void PIXSetMarker(_In_z_ const wchar_t* name)
		{
			if (d3dAnnotation_)
			{
				d3dAnnotation_->SetMarker(name);
			}
		}
	};

	/*
	// @class		DeviceXToolKidResources �N���X�iSingleton�j
	// @content		DirectXTK�̋@�\�֘A
	// @use			�X�v���C�g�o�b�`��v���~�e�B�u�o�b�`�Ȃǂ��K�v�ȏꍇ�͂����p����
	*/
	class DirectXToolKidResources : public SingletonDirector<DirectXToolKidResources>
	{
	private:
		ID3D11Device*																	device_;				// �f�o�C�X
		ID3D11DeviceContext*															context_;				// �R���e�L�X�g

		std::unique_ptr<DirectX::SpriteBatch>											spriteBatch_;			// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteFont>											spriteFont_;			// �X�v���C�g�t�H���g

		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>			primitiveBatchVPN_;		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>	primitiveBatchVPCT_;	// �v���~�e�B�u�o�b�`

	private:
		friend class SingletonDirector<DirectXToolKidResources>;

		DirectXToolKidResources() {}

	public:
		/*
		// @method		Initialize
		// @content		����������
		// @param		�f�o�C�X�iID3D11Device*�j
		// @param		�R���e�L�X�g�iID3D11DeviceContext*�j
		*/
		void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

		/*
		// @method		SetFont
		// @content		�t�H���g�ύX
		// @param		�t�H���g���i�g���q�������j�iwstring�j
		*/
		void SetFont(std::wstring fontName);

		/* �A�N�Z�b�T */

		inline DirectX::SpriteBatch* GetSpriteBatch() const		{ return spriteBatch_.get(); }
		inline DirectX::SpriteFont* GetSpriteFont() const		{ return spriteFont_.get(); }
	};
}