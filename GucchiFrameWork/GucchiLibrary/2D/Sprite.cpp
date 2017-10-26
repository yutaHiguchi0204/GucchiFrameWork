/* =====================================================================
//! @param		「Sprite」ソース
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */

// ヘッダファイルのインクルード
#include "Sprite.h"
#include <WICTextureLoader.h>
#include "../Common/Constant.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// メンバ関数の定義

// コンストラクタ
Sprite::Sprite(const Vector2& size)
	: texture_(nullptr)
	, size_(size)
	, textureRect_(nullptr)
	, angle_(0.0f)
	, isActive_(true)
{
}

/*==============================================================
// @brief		初期化処理（位置とスプライトサイズの設定をするために必ず呼んでください）
// @param		位置（Vector2）、画像矩形（RECT*）、拡大率（float）、回転角（float）
// @return		なし
===============================================================*/
void Sprite::Initialize(const Vector2& pos, RECT* rect, float scale, float angle)
{
	pos_ = pos;
	textureRect_ = rect;
	scale_ = scale;
	angle_ = angle;
}