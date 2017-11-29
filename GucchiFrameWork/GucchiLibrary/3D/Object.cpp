/* =====================================================================
//! @param		�uObject�v�\�[�X
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Object.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
{
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Object::Update()
{
	// �s��̍X�V
	Asset3D::Update();

	// �q�������ꍇ�͎q���X�V����
	if (childObject_.size() != 0)
	{
		for (auto& child : childObject_)
		{
			child->Update();
		}
	}
}

/*==============================================================
// @brief		�e�q�֌W�\�z�i�e�ݒ�j
// @param		�e�I�u�W�F�N�g�iObject*�j
// @return		�Ȃ�
===============================================================*/
void Object::SetParent(Object* object)
{
	parentObject_ = object;
	object->childObject_.emplace_back(this);
}

/*==============================================================
// @brief		�e�q�֌W�\�z�i�q�ݒ�j
// @param		�q�I�u�W�F�N�g�iObject*�j
// @return		�Ȃ�
===============================================================*/
void Object::AddChild(Object* object)
{
	childObject_.emplace_back(object);
	object->parentObject_ = this;
}