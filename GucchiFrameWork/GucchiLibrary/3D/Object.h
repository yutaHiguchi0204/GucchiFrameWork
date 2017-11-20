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
	// �N���X�̒�`
	class Object : public Asset3D
	{
	private:
		Object* parentObject_;							// �e�I�u�W�F�N�g

	public:
		Object(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, Asset3D::BLEND_MODE mode = Asset3D::BLEND_MODE::ALPHA);
		virtual ~Object() {};
	};
}