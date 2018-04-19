/* =====================================================================
//! @param		�uCollider�v�\�[�X
//! @create		��� �T��
//! @date		18/02/07
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Collider.h"
#include "../3D/Object.h"
#include "../System/DebugSystem.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Collider::Finalize()
{
	PrimitiveRenderer::GetInstance().DisposePrimitive(primitive_.get());
	primitive_.release();
	primitive_ = nullptr;
}

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
	/* �R�c�v�f�ł���ΕR�Â��\ */

	// �I�u�W�F�N�g
	
	// �G�~�b�^�[

	// �p�[�e�B�N��
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
	/* �R�c�v�f�ł���ΕR�Â��\ */

	// �I�u�W�F�N�g
	Object* object = dynamic_cast<Object*>(element);

	if (object)
	{
		// �����蔻��
		float diameter = object->GetBoundingSphere();

		// �v���~�e�B�u�쐬
		primitive_ = PrimitiveFactory::CreateSphere(diameter, 16, Color(0.3f, 1, 0.3f));
		PrimitiveRenderer::GetInstance().RegisterPrimitive(primitive_.get());
	}

	// �G�~�b�^�[

	// �p�[�e�B�N��
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
	/* �R�c�v�f�ł���ΕR�Â��\ */

	// �I�u�W�F�N�g
	Object* object = dynamic_cast<Object*>(element);

	if (object)
	{
		// �����蔻��
		Vector3 boundingBox = object->GetBoundingBox();

		// �v���~�e�B�u�쐬
		primitive_ = PrimitiveFactory::CreateBox(boundingBox, Color(0.3f, 1, 0.3f));
		//PrimitiveRenderer::GetInstance().RegisterPrimitive(primitive_.get());

		return;
	}

	// �G�~�b�^�[

	// �p�[�e�B�N��
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