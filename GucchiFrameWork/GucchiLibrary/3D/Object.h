/* =====================================================================
//! @param		�uObject�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Asset3D.h"
#include <Model.h>

namespace GucchiLibrary
{
	/*
	// @class		Object �N���X
	// @content		3D�I�u�W�F�N�g
	// @use			ObjectFactory���g����������
	// @use			ObjectRenderer�ɓo�^���邱�Ƃŕ`��\
	*/
	class Object : public Asset3D
	{
	private:
		DirectX::Model*			model_;						// ���f��

		Object*					parentObject_;				// �e�I�u�W�F�N�g
		std::vector<Object*>	childObject_;				// �q�I�u�W�F�N�g

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		���s�ړ��iVector3�j�@�F�@�f�t�H���g�iVector3::Zero�j
		// @param		�X�P�[���iVector3�j�@�F�@�f�t�H���g�iVector3::One�j
		// @param		��]�p�iVector3�j�@�F�@�f�t�H���g�iVector3::Zero�j
		// @param		�N�H�[�^�j�I���iQuaternion�j�@�F�@�f�t�H���g�iQuaternion::Identity�j
		// @param		�u�����h���[�h�iBLEND_MODE�j�@�F�@�f�t�H���g�iALPHA�j
		*/
		Object(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, Asset3D::BLEND_MODE mode = Asset3D::BLEND_MODE::ALPHA);

		// �R�s�[�R���X�g���N�^
		Object(const Object& object);

		// �f�X�g���N�^
		virtual ~Object() {}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update() override;

		/*
		// @method		SetParent
		// @content		�e�q�֌W�\�z�i�e�ݒ�j
		// @param		�e�I�u�W�F�N�g�iObject*�j
		*/
		void SetParent(Object* object);

		/*
		// @method		AddChild
		// @content		�e�q�֌W�\�z�i�q�ݒ�j
		// @param		�q�I�u�W�F�N�g�iObject*�j
		*/
		void AddChild(Object* object);

		/* �A�N�Z�b�T */

		void SetModel(DirectX::Model* model) { model_ = model; }

		inline DirectX::Model* GetModel() const { return model_; }
		inline Object* GetParent() const { return parentObject_; }
		inline std::vector<Object*> GetChildren() const { return childObject_; }

	public:
		// ����I�y���[�^
		Object& operator=(const Object& object)
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

			return (*this);
		}

		// ��r�p�I�y���[�^
		bool operator==(const Object& object) const
		{
			if (scale_           == object.scale_				&&
				rot_             == object.rot_					&&
				quat_            == object.quat_				&&
				trans_           == object.trans_				&&
				world_           == object.world_				&&
				blendMode_       == object.blendMode_			&&
				isActive_        == object.isActive_			&&
				isUseQuaternion_ == object.isUseQuaternion_		&&
				model_           == object.model_				&&
				parentObject_    == object.parentObject_
				)
			{
				return true;
			}

			return false;
		}
	};
}