/* =====================================================================
//! @param		「TextureCache」ソース
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */

// ヘッダファイルのインクルード
#include "TextureCache.h"
#include <cassert>
#include <WICTextureLoader.h>
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace Microsoft::WRL;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		テクスチャ読み込み
// @param		ファイル名（wstring）
// @return		テクスチャ（Texture*）
===============================================================*/
Texture* TextureCache::LoadTexture(const wstring fileName)
{
	// すでに読み込み済みなら読み込まない
	if (textures_.count(fileName) == 0)
	{
		// エラー処理用
		HRESULT res;

		// デバイス準備
		DeviceResources& deviceResources = DeviceResources::GetInstance();

		// テクスチャ関連
		ComPtr<ID3D11ShaderResourceView> shaderResourceView;
		ComPtr<ID3D11Resource> resource;
		ComPtr<ID3D11Texture2D> resourceTexture;

		// フルパス作成
		wstring fullPath = FILE_PATH_SPRITE + fileName + EXT_PNG;

		// テクスチャの作成
		res = CreateWICTextureFromFile(deviceResources.GetD3DDevice(), fullPath.c_str(), resource.GetAddressOf(), shaderResourceView.ReleaseAndGetAddressOf());

		// エラー処理
		if (FAILED(res))
		{
			DebugSystem::DebugLog(L"Texture loading failed.", true);
			assert(false);
		}

		// リソースをテクスチャとして解釈する
		res = resource.As(&resourceTexture);

		// エラー処理
		if (FAILED(res))
		{
			DebugSystem::DebugLog(L"This resource is not texture.", true);
			assert(false);
		}

		// テクスチャ情報取得
		CD3D11_TEXTURE2D_DESC desc;
		resourceTexture->GetDesc(&desc);

		// 読み込んだ情報を格納
		unique_ptr<Texture> texture = make_unique<Texture>();
		texture->SetDesc(desc);
		texture->SetShaderResourceView(shaderResourceView.Get());

		textures_[fileName] = move(texture);
	}

	return textures_[fileName].get();
}