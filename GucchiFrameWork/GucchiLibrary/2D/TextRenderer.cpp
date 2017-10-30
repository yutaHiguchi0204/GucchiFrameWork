/* =====================================================================
//! @param		「TextRenderer」ソース
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */

// ヘッダファイルのインクルード
#include "TextRenderer.h"
#include <SpriteFont.h>
#include "GucchiLibrary.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// メンバ関数の定義

/*==============================================================
// @brief		テキストの登録
// @param		テキスト（Text*）
// @return		なし
===============================================================*/
void TextRenderer::RegisterText(Text* text)
{
	textList_.push_back(*text);
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		テキスト（Text*）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void TextRenderer::SetActive(Text* text, bool active)
{
	text->SetActive(active);
}

/*==============================================================
// @brief		テキスト描画
// @param		なし
// @return		なし
===============================================================*/
void TextRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// バッチ処理開始
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// 描画処理
	for (auto text : textList_)
	{
		// アクティブ状態のスプライトのみ表示
		if (text.GetActive())
		{
			// 原点設定
			Vector2 origin = dxtk.GetSpriteFont()->MeasureString(text.GetString().c_str()) / 2.f;

			// 描画
			dxtk.GetSpriteFont()->DrawString(dxtk.GetSpriteBatch().get(), text.GetString().c_str(), text.GetPos(), text.GetColor(), 0.f, origin, text.GetFontSize() / DEFAULT_FONT_SIZE);
		}
	}

	// バッチ処理終了
	dxtk.GetSpriteBatch()->End();
}