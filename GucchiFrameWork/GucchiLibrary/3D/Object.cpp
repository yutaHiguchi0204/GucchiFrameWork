/* =====================================================================
//! @param		「Object」ソース
//! @create		樋口 裕太
//! @date		17/11/15
===================================================================== */

// ヘッダファイルのインクルード
#include "Object.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
{
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Object::Update()
{
	// 行列の更新
	Asset3D::Update();

	// 子がいた場合は子も更新する
	if (childObject_.size() != 0)
	{
		for (auto& child : childObject_)
		{
			child->Update();
		}
	}
}

/*==============================================================
// @brief		親子関係構築（親設定）
// @param		親オブジェクト（Object*）
// @return		なし
===============================================================*/
void Object::SetParent(Object* object)
{
	parentObject_ = object;
	object->childObject_.emplace_back(this);
}

/*==============================================================
// @brief		親子関係構築（子設定）
// @param		子オブジェクト（Object*）
// @return		なし
===============================================================*/
void Object::AddChild(Object* object)
{
	childObject_.emplace_back(object);
	object->parentObject_ = this;
}