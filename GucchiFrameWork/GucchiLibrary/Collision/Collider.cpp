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
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Segment::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check segment.");
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Sphere::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check sphere.");
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Capsule::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check capsule.");
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Plane::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check plane.");
}

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void Triangle::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check triangle.");
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

/*==============================================================
// @brief		更新処理
// @param		要素（Element*）
// @return		なし
===============================================================*/
void OBB::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check OBB.");
}