/* =====================================================================
//! @param		「Object」ソース
//! @create		樋口 裕太
//! @date		17/11/15
===================================================================== */

// ヘッダファイルのインクルード
#include "Object.h"
#include <algorithm>

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
	, model_(nullptr)
	, parentObject_(nullptr)
{
}

// コピーコンストラクタ
Object::Object(const Object& object)
{
	basicEffect_           = object.basicEffect_;
	inputLayout_           = object.inputLayout_;
	effectFactory_         = object.effectFactory_;
	camera_                = object.camera_;
	scale_                 = object.scale_;
	rot_                   = object.rot_;
	quat_                  = object.quat_;
	trans_                 = object.trans_;
	world_                 = object.world_;
	blendStateSubtractive_ = object.blendStateSubtractive_;
	blendMode_             = object.blendMode_;
	isActive_              = object.isActive_;
	isUseQuaternion_       = object.isUseQuaternion_;
	model_                 = object.model_;
	parentObject_          = object.parentObject_;
	childObject_           = object.childObject_;
	model_                 = object.model_;
	parentObject_          = object.parentObject_;
	childObject_           = object.childObject_;
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
	if (static_cast<int>(childObject_.size()) != 0)
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

/*==============================================================
// @brief		オブジェクトのバウンディングボックスを取得
// @param		なし
// @return		バウンディングボックス（Vector3）
===============================================================*/
Object::Vector3 Object::GetBoundingBox()
{
	// メッシュを取得
	ModelMesh::Collection& meshes = model_->meshes;

	// 座標を保存
	vector<float> x, y, z;
	for (auto& mesh : meshes)
	{
		x.emplace_back(mesh->boundingBox.Center.x - mesh->boundingBox.Extents.x);
		x.emplace_back(mesh->boundingBox.Center.x + mesh->boundingBox.Extents.x);
		y.emplace_back(mesh->boundingBox.Center.y - mesh->boundingBox.Extents.y);
		y.emplace_back(mesh->boundingBox.Center.y + mesh->boundingBox.Extents.y);
		z.emplace_back(mesh->boundingBox.Center.z - mesh->boundingBox.Extents.z);
		z.emplace_back(mesh->boundingBox.Center.z + mesh->boundingBox.Extents.z);
	}

	// x, y, zそれぞれの最小値と最大値を算出
	Vector3 min = Vector3(*min_element(x.cbegin(), x.cend()), *min_element(y.cbegin(), y.cend()), *min_element(z.cbegin(), z.cend()));
	Vector3 max = Vector3(*max_element(x.cbegin(), x.cend()), *max_element(y.cbegin(), y.cend()), *max_element(z.cbegin(), z.cend()));

	return max - min;
}

/*==============================================================
// @brief		オブジェクトのバウンディングスフィアを取得
// @param		なし
// @return		バウンディングスフィア（float）
===============================================================*/
float Object::GetBoundingSphere()
{
	// バウンディングボックスを取得
	Vector3 boundingBox = GetBoundingBox();

	// バウンディングボックスの最大値を取得（これがバウンディングスフィアの直径となる）
	return max(max(boundingBox.x, boundingBox.y), boundingBox.z);
}