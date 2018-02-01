/* =====================================================================
//! @param		�uTextureCache�v�w�b�_
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <string>
#include <wrl/client.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		Texture �N���X
	// @content		�e�N�X�`�����\�[�X
	// @use			�X�v���C�g�⃂�f���̃e�N�X�`���Ɏg�p
	// @use			TextureCache�ɂ���ĊǗ������
	*/
	class Texture
	{
	private:
		CD3D11_TEXTURE2D_DESC desc_;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView_;

	public:
		/* �A�N�Z�b�T */

		void SetDesc(const CD3D11_TEXTURE2D_DESC& desc) { desc_ = desc; }
		void SetShaderResourceView(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView) { shaderResourceView_ = shaderResourceView; }

		inline CD3D11_TEXTURE2D_DESC GetDesc() const { return desc_; }
		inline Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return shaderResourceView_; }
	};

	/*
	// @class		TextureCache �N���X�iSingleton�j
	// @content		�e�N�X�`���Ǘ��p
	// @use			LoadTexture�֐��Ń��[�h�����e�N�X�`�����Ǘ�����
	*/
	class TextureCache : public SingletonDirector<TextureCache>
	{
	private:
		std::map<std::wstring, std::unique_ptr<Texture>> textures_;

	private:
		friend class SingletonDirector<TextureCache>;

		TextureCache() = default;

	public:
		/*
		// @method		LoadTexture
		// @content		�e�N�X�`���̃��[�h
		// @param		�e�N�X�`���t�@�C�����iwstring�j
		// @return		�e�N�X�`���iTexture*�j
		*/
		Texture* LoadTexture(const std::wstring fileName);
	};
}