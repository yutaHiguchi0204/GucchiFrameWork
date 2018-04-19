/* =====================================================================
//! @param		「Collider」ソース
//! @create		樋口 裕太
//! @date		18/02/07
===================================================================== */

// ヘッダファイルのインクルード
#include "Collider.h"
#include "../3D/Object.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void Collider::Finalize()
{
	PrimitiveRenderer::GetInstance().DisposePrimitive(primitive_.get());
	primitive_.release();
	primitive_ = nullptr;
}

/*==============================================================
// @brief		初期化処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Collider::SetPrimitiveActive(bool active)
{
#if DRAW_COLLIDER == 1
	primitive_->SetActive(active);
#else
	DebugSystem::DebugLog(L"Change switch to \"DRAW_COLLIDER\"", true);
#endif
}

/*==============================================================
// @brief		初期化処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void SegmentCollider::Initialize(Element* element)
{
	/* ３Ｄ要素であれば紐づけ可能 */

	// オブジェクト
	
	// エミッター

	// パーティクル
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void SegmentCollider::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check segment.");
}

/*==============================================================
// @brief		初期化処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void SphereCollider::Initialize(Element* element)
{
	/* ３Ｄ要素であれば紐づけ可能 */

	// オブジェクト
	Object* object = dynamic_cast<Object*>(element);

	if (object)
	{
		// 当たり判定
		float diameter = object->GetBoundingSphere();

		// プリミティブ作成
		primitive_ = PrimitiveFactory::CreateSphere(diameter, 16, Color(0.3f, 1, 0.3f));
		PrimitiveRenderer::GetInstance().RegisterPrimitive(primitive_.get());
	}

	// エミッター

	// パーティクル
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void SphereCollider::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check sphere.");
}

///*==============================================================
//// @brief		更新処理
//// @param		要素（Element*）
//// @return		なし
//===============================================================*/
//void CapsuleCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check capsule.");
//}

///*==============================================================
//// @brief		更新処理
//// @param		要素（Element*）
//// @return		なし
//===============================================================*/
//void PlaneCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check plane.");
//}

///*==============================================================
//// @brief		更新処理
//// @param		要素（Element*）
//// @return		なし
//===============================================================*/
//void TriangleCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check triangle.");
//}

/*==============================================================
// @brief		初期化処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void AABB::Initialize(Element* element)
{
	/* ３Ｄ要素であれば紐づけ可能 */

	// オブジェクト
	Object* object = dynamic_cast<Object*>(element);

	if (object)
	{
		// 当たり判定
		Vector3 boundingBox = object->GetBoundingBox();

		// プリミティブ作成
		primitive_ = PrimitiveFactory::CreateBox(boundingBox, Color(0.3f, 1, 0.3f));
		//PrimitiveRenderer::GetInstance().RegisterPrimitive(primitive_.get());

		return;
	}

	// エミッター

	// パーティクル
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void AABB::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check AABB.");
}

///*==============================================================
//// @brief		更新処理
//// @param		要素（Element*）
//// @return		なし
//===============================================================*/
//void OBB::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check OBB.");
//}