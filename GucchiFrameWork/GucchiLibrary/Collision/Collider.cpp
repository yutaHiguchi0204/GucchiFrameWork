/* =====================================================================
//! @param		�uCollider�v�\�[�X
//! @create		��� �T��
//! @date		18/02/07
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Collider.h"
#include "../System/DebugSystem.h"

// ���O���
using namespace GucchiLibrary;

/*==============================================================
// @brief		����������
// @param		�v�f�iElement*�j
// @return		�Ȃ�
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
// @brief		����������
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void SegmentCollider::Initialize(Element* element)
{
	
}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void SegmentCollider::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check segment.");
}

/*==============================================================
// @brief		����������
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void SphereCollider::Initialize(Element* element)
{

}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void SphereCollider::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check sphere.");
}

///*==============================================================
//// @brief		�X�V����
//// @param		�v�f�iElement*�j
//// @return		�Ȃ�
//===============================================================*/
//void CapsuleCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check capsule.");
//}

///*==============================================================
//// @brief		�X�V����
//// @param		�v�f�iElement*�j
//// @return		�Ȃ�
//===============================================================*/
//void PlaneCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check plane.");
//}

///*==============================================================
//// @brief		�X�V����
//// @param		�v�f�iElement*�j
//// @return		�Ȃ�
//===============================================================*/
//void TriangleCollider::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check triangle.");
//}

/*==============================================================
// @brief		����������
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void AABB::Initialize(Element* element)
{

}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void AABB::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check AABB.");
}

///*==============================================================
//// @brief		�X�V����
//// @param		�v�f�iElement*�j
//// @return		�Ȃ�
//===============================================================*/
//void OBB::Update(Element* element)
//{
//	DebugSystem::DebugLog(L"Check OBB.");
//}