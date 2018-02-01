/* =====================================================================
//! @param		�uObject�v�\�[�X
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Object.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
	, model_(nullptr)
	, parentObject_(nullptr)
{
}

// �R�s�[�R���X�g���N�^
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
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Object::Update()
{
	// �s��̍X�V
	Asset3D::Update();

	// �q�������ꍇ�͎q���X�V����
	if (static_cast<int>(childObject_.size()) != 0)
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