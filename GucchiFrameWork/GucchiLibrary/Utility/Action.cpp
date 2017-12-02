/* =====================================================================
//! @param		「Action」ソース（移動関係ライブラリ）
//! @create		樋口 裕太
//! @date		17/12/02
===================================================================== */

// ヘッダファイルのインクルード
#include "Action.h"
#include "../Utility/Interpolater.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// メンバ関数の定義

/*==============================================================
// @brief		線形移動（絶対移動）
// @param		スプライト（Sprite*）、移動にかける時間（float）、移動距離（Vector2）
// @return		なし
===============================================================*/
void MoveTo::Action(Sprite* sprite, float time, const Vector2& distance)
{
	// 現在の位置
	Vector2 pos = sprite->GetPos();

	// 線形補間で移動を行う
	
}

/*==============================================================
// @brief		線形移動（絶対移動）
// @param		オブジェクト（Object*）、移動にかける時間（float）、移動距離（Vector3）
// @return		なし
===============================================================*/
void MoveTo::Action(Object* object, float time, const Vector3& pos)
{

}

/*==============================================================
// @brief		線形移動（相対移動）
// @param		スプライト（Sprite*）、移動にかける時間（float）、移動距離（Vector2）
// @return		なし
===============================================================*/
void MoveBy::Action(Sprite* sprite, float time, const Vector2& distance)
{

}

/*==============================================================
// @brief		線形移動（相対移動）
// @param		オブジェクト（Object*）、移動にかける時間（float）、移動距離（Vector3）
// @return		なし
===============================================================*/
void MoveBy::Action(Object* object, float time, const Vector3& distance)
{

}