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
Sprite::Sprite()
	: texture_(nullptr)
	, pos_(Vector2(0.0f, 0.0f))
	, scale_(1.0f)
	, angle_(0.0f)
	, isActive_(true)
{
}

/*==============================================================
// @brief		初期化処理
// @param		位置（Vector2）、拡大率（float）、回転角（float）
// @return		なし
===============================================================*/
void Sprite::Initialize(const Vector2& pos, float scale, float angle)
{
	pos_ = pos;
	scale_ = scale;
	angle_ = angle;
}