/* =====================================================================
//! @param		�uObject�v�\�[�X
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Object.h"
#include <algorithm>

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

/*==============================================================
// @brief		�I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X���擾
// @param		�Ȃ�
// @return		�o�E���f�B���O�{�b�N�X�iVector3�j
===============================================================*/
Object::Vector3 Object::GetBoundingBox()
{
	// ���b�V�����擾
	ModelMesh::Collection& meshes = model_->meshes;

	// ���W��ۑ�
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

	// x, y, z���ꂼ��̍ŏ��l�ƍő�l���Z�o
	Vector3 min = Vector3(*min_element(x.cbegin(), x.cend()), *min_element(y.cbegin(), y.cend()), *min_element(z.cbegin(), z.cend()));
	Vector3 max = Vector3(*max_element(x.cbegin(), x.cend()), *max_element(y.cbegin(), y.cend()), *max_element(z.cbegin(), z.cend()));

	return max - min;
}

/*==============================================================
// @brief		�I�u�W�F�N�g�̃o�E���f�B���O�X�t�B�A���擾
// @param		�Ȃ�
// @return		�o�E���f�B���O�X�t�B�A�ifloat�j
===============================================================*/
float Object::GetBoundingSphere()
{
	// �o�E���f�B���O�{�b�N�X���擾
	Vector3 boundingBox = GetBoundingBox();

	// �o�E���f�B���O�{�b�N�X�̍ő�l���擾�i���ꂪ�o�E���f�B���O�X�t�B�A�̒��a�ƂȂ�j
	return max(max(boundingBox.x, boundingBox.y), boundingBox.z);
}