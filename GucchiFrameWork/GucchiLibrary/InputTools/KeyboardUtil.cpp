/* =====================================================================
//! @param		「KeyboardUtil」ソース
//! @create		樋口 裕太
//! @date		17/11/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "KeyboardUtil.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void KeyboardUtil::Initialize()
{
	keyboard_ = make_unique<Keyboard>();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void KeyboardUtil::Update()
{
	// ステート情報の更新
	state_ = keyboard_->GetState();
	tracker_.Update(state_);
}