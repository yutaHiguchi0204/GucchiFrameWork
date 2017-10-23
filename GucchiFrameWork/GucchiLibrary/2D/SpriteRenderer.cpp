/* =====================================================================
//! @param		「SpriteRenderer」ソース
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */

// ヘッダファイルのインクルード
#include "SpriteRenderer.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		スプライトの登録
// @param		スプライト（Sprite*）、表示順（int）
//				デフォルトで-1に設定されていますが、リストの一番最後に登録されるという意味です
// @return		なし
===============================================================*/
void SpriteRenderer::RegisterSprite(Sprite* sprite, int order)
{
	// スプライトの登録
	// ※現在は表示順関係なくただ後ろに追加するだけ
	spriteList_.push_back(*sprite);
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		スプライト（Sprite*）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void SpriteRenderer::SetActive(Sprite* sprite, bool active)
{
	sprite->SetActive(active);
}

/*==============================================================
// @brief		アクティブ状態のスプライトを表示
// @param		なし
// @return		なし
===============================================================*/
void SpriteRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// バッチ処理開始
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// 描画処理
	for (auto sprite : spriteList_)
	{
		// アクティブ状態のスプライトのみ表示
		if (sprite.GetActive())
		{
			dxtk.GetSpriteBatch()->Draw(sprite.GetTexture()->GetShaderResourceView().Get(), sprite.GetPos());
		}
	}

	// バッチ処理終了
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		スプライトの生成
// @param		ファイル名（wstring）
// @return		なし
===============================================================*/
unique_ptr<Sprite> SpriteFactory::CreateSpriteFromFile(const wstring fileName)
{
	unique_ptr<Sprite> sprite = make_unique<Sprite>();

	// テクスチャの格納庫を準備
	TextureCache& cache = TextureCache::GetInstance();

	// テクスチャの読み込み
	Texture* texture = cache.LoadTexture(fileName);
	sprite->SetTexture(texture);

	return std::move(sprite);
}