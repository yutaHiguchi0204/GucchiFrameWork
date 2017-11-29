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
Sprite::Sprite(const Vector2& size, const Vector2& pos, RECT* rect, float scale, float angle)
	: texture_(nullptr)
	, size_(size)
	, pos_(pos)
	, textureRect_(nullptr)
	, scale_(scale)
	, angle_(angle)
	, isActive_(true)
	, parentSprite_(nullptr)
{
}

/*==============================================================
// @brief		親子関係構築（親設定）
// @param		親スプライト（Sprite*）
// @return		なし
===============================================================*/
void Sprite::SetParent(Sprite* sprite)
{
	parentSprite_ = sprite;
	sprite->childSprite_.emplace_back(this);
}

/*==============================================================
// @brief		親子関係構築（子設定）
// @param		子スプライト（Sprite*）
// @return		なし
===============================================================*/
void Sprite::AddChild(Sprite* sprite)
{
	childSprite_.emplace_back(sprite);
	sprite->parentSprite_ = this;
}