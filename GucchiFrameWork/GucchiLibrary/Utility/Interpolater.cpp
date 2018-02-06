/* =====================================================================
//! @param		「Interpolater」ソース（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */

// ヘッダファイルのインクルード
#include "Interpolater.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
InterpolateDirector::InterpolateDirector()
{
	// 実体化
	stateF_ = make_unique<InterpolateState<float>>();
	stateV2_ = make_unique<InterpolateState<Vector2>>();
	stateV3_ = make_unique<InterpolateState<Vector3>>();
	stateV4_ = make_unique<InterpolateState<Vector4>>();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void InterpolateDirector::Update()
{
	stateF_->Update();
	stateV2_->Update();
	stateV3_->Update();
	stateV4_->Update();
}

/*==============================================================
// @brief		リセット
// @param		なし
// @return		なし
===============================================================*/
void InterpolateDirector::Reset()
{
	stateF_->Reset();
	stateV2_->Reset();
	stateV3_->Reset();
	stateV4_->Reset();
}