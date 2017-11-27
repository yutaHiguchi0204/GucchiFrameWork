/* =====================================================================
//! @param		「MouseUtil」ソース
//! @create		樋口 裕太
//! @date		17/11/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "MouseUtil.h"

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
void MouseUtil::Initialize()
{
	mouse_ = make_unique<Mouse>();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void MouseUtil::Update()
{
	// ステート情報の更新
	state_ = mouse_->GetState();
	tracker_.Update(state_);
}