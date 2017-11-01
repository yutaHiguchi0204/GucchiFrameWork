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
using namespace DirectX::SimpleMath;
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
	if (order != -1)
	{
		auto itr = spriteList_.begin();

		// 指定場所に登録（これにより表示順が変わる）
		int orderNum = 0;
		while (orderNum < order - 1)
		{
			itr++;
			orderNum++;
		}

		spriteList_.insert(itr, *sprite);
		return;
	}

	// スプライトの登録
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
// @brief		スプライトの表示順
// @param		スプライト（Sprite*）、表示順（int）
// @return		なし
===============================================================*/
void SpriteRenderer::SetOrder(Sprite* sprite, int order)
{
	auto itr = spriteList_.begin();

	// 指定位置を検索
	int orderNum = 0;
	while (orderNum <= order)
	{
		itr++;
		orderNum++;
	}

	// 現在の位置を取得
	auto now = find(spriteList_.begin(), spriteList_.end(), *sprite);

	// 指定位置に移動
	spriteList_.splice(itr, spriteList_, now);
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
			dxtk.GetSpriteBatch()->Draw(sprite.GetTexture()->GetShaderResourceView().Get(), sprite.GetPos(), sprite.GetRect(), Colors::White, sprite.GetAngle(), Vector2(sprite.GetSize().x / 2, sprite.GetSize().y / 2));
		}
	}

	// バッチ処理終了
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		リストリセット
// @param		なし
// @return		なし
===============================================================*/
void SpriteRenderer::Reset()
{
	spriteList_.clear();
}

/*==============================================================
// @brief		スプライトの生成
// @param		ファイル名（wstring）、画像サイズ（Vector2）
// @return		なし
===============================================================*/
unique_ptr<Sprite> SpriteFactory::CreateSpriteFromFile(const wstring fileName, const Vector2& size)
{
	unique_ptr<Sprite> sprite = make_unique<Sprite>(size);

	// テクスチャの格納庫を準備
	TextureCache& cache = TextureCache::GetInstance();

	// テクスチャの読み込み
	Texture* texture = cache.LoadTexture(fileName);
	sprite->SetTexture(texture);

	return std::move(sprite);
}