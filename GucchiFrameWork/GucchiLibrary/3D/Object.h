/* =====================================================================
//! @param		�uObject�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Asset3D.h"

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
		Object* parentObject_;							// �e�I�u�W�F�N�g

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

		// �f�X�g���N�^
		virtual ~Object() {};
	};
}