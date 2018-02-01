/* =====================================================================
//! @param		「TextureCache」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <string>
#include <wrl/client.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		Texture クラス
	// @content		テクスチャリソース
	// @use			スプライトやモデルのテクスチャに使用
	// @use			TextureCacheによって管理される
	*/
	class Texture
	{
	private:
		CD3D11_TEXTURE2D_DESC desc_;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView_;

	public:
		/* アクセッサ */

		void SetDesc(const CD3D11_TEXTURE2D_DESC& desc) { desc_ = desc; }
		void SetShaderResourceView(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView) { shaderResourceView_ = shaderResourceView; }

		inline CD3D11_TEXTURE2D_DESC GetDesc() const { return desc_; }
		inline Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return shaderResourceView_; }
	};

	/*
	// @class		TextureCache クラス（Singleton）
	// @content		テクスチャ管理用
	// @use			LoadTexture関数でロードしたテクスチャを管理する
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
		// @content		テクスチャのロード
		// @param		テクスチャファイル名（wstring）
		// @return		テクスチャ（Texture*）
		*/
		Texture* LoadTexture(const std::wstring fileName);
	};
}