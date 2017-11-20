/* =====================================================================
//! @param		�uDefaultCamera�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Camera.h"
#include "../InputTools/MouseUtil.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class DefaultCamera : public Camera
	{
	protected:
		static const float DEFAULT_DISTANCE;

	protected:
		MouseUtil& mouse_ = MouseUtil::GetInstance();		// �}�E�X���

		DirectX::SimpleMath::Vector2 angle_;				// ��]�p���
		DirectX::SimpleMath::Vector2 tmpAngle_;				// ��]�p�ۑ��p

		DirectX::SimpleMath::Vector2 dragStartPos_;			// �}�E�X�h���b�O�̊J�n�n�_
		DirectX::SimpleMath::Vector2 relScale_;				// ���΃X�P�[��

		int wheelValue_;									// �g�嗦

	public:
		DefaultCamera(int width, int height);
		virtual ~DefaultCamera() {};

		// �X�V����
		virtual void Update() override;

		// �J������]���[�V����
		virtual void Motion(DirectX::SimpleMath::Vector2 mousePos);
	};
}