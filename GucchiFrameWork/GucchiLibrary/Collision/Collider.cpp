/* =====================================================================
//! @param		「Collider」ソース
//! @create		樋口 裕太
//! @date		18/02/07
===================================================================== */

// ヘッダファイルのインクルード
#include "Collider.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace GucchiLibrary;

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