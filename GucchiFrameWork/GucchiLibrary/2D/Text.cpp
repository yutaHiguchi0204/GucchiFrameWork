/* =====================================================================
//! @param		「Text」ソース
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */

// ヘッダファイルのインクルード
#include "Text.h"
#include "GucchiLibrary.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const float Text::DEFAULT_FONT_SIZE = 18.0f;		// フォントサイズの初期設定（フォントを新規で作成する際は、フォントサイズを"18"で作ってください）

// メンバ関数の定義

// コンストラクタ
Text::Text(wstring str, const Vector2& pos, wstring font, int fontSize, const Color& color)
	: str_(str)
	, pos_(pos)
	, anchor_(ANCHOR_LM)
	, font_(font)
	, fontSize_(fontSize)
	, color_(color)
	, isActive_(true)
{
}

/*==============================================================
// @brief		フォントの変更
// @param		スプライトフォントハンドル（wstring）
//				既存のスプライトフォントをリセットする必要があるため、別途処理を行います
// @return		なし
===============================================================*/
void Text::SetFont(const wstring font)
{
	font_ = font;

	// 新しいスプライトフォントを設定
	wstring fontName = FILE_PATH_FONT + font + EXT_SPRITEFONT;

	// リセット処理
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();
	dxtk.SetFont(font);
}