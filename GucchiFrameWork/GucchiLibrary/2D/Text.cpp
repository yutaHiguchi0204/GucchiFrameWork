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
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Text::Text(wstring str, Vector2 pos, wstring font, int fontSize, Color color)
	: str_(str)
	, pos_(pos)
	, font_(font)
	, fontSize_(fontSize)
	, color_(color)
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