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
using namespace std;

// メンバ関数の定義

// コンストラクタ
Sprite::Sprite(const Vector2& size, const Vector2& pos, RECT* rect, float scale, float angle)
	: texture_(nullptr)
	, pos_(pos)
	, size_(size)
	, textureRect_(nullptr)
	, anchor_(ANCHOR_MM)
	, scale_(scale)
	, angle_(angle)
	, isActive_(true)
	, parentSprite_(nullptr)
	, isAction_(false)
{
	// 補間ステートの準備
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

// コピーコンストラクタ
Sprite::Sprite(const Sprite& sprite)
{
	texture_             = sprite.texture_;
	pos_                 = sprite.pos_;
	size_                = sprite.size_;
	textureRect_         = sprite.textureRect_;
	anchor_              = sprite.anchor_;
	scale_               = sprite.scale_;
	angle_               = sprite.angle_;
	isActive_            = sprite.isActive_;
	parentSprite_        = sprite.parentSprite_;
	childSprite_         = sprite.childSprite_;
	isAction_            = sprite.isAction_;
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Sprite::Update()
{
	// 補間ステートの更新
	interpolateDirector_->Update();
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