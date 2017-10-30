/* =====================================================================
//! @param		�uTextureCache�v�w�b�_
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <d3d11_1.h>
#include <map>
#include <string>
#include <wrl/client.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// �N���X�̒�`�i�e�N�X�`���j
	class Texture
	{
	private:
		CD3D11_TEXTURE2D_DESC desc_;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView_;

	public:
		void SetDesc(const CD3D11_TEXTURE2D_DESC& desc) { desc_ = desc; }
		void SetShaderResourceView(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView) { shaderResourceView_ = shaderResourceView; }

		inline CD3D11_TEXTURE2D_DESC GetDesc() const { return desc_; }
		inline Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return shaderResourceView_; }
	};

	// �N���X�̒�`�i�e�N�X�`���Ǘ��j
	class TextureCache : public SingletonDirector<TextureCache>
	{
	private:
		std::map<std::wstring, std::unique_ptr<Texture>> textures_;

	private:
		friend class SingletonDirector<TextureCache>;

		TextureCache() {};

	public:
		Texture* LoadTexture(const std::wstring fileName);
	};
}