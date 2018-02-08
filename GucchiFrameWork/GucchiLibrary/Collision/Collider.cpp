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
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void Segment::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check segment.");
}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void Sphere::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check sphere.");
}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void Capsule::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check capsule.");
}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void Plane::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check plane.");
}

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void Triangle::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check triangle.");
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

/*==============================================================
// @brief		�X�V����
// @param		�v�f�iElement*�j
// @return		�Ȃ�
===============================================================*/
void OBB::Update(Element* element)
{
	DebugSystem::DebugLog(L"Check OBB.");
}