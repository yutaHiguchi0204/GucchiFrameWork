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
	/*
	// @class		DefaultCamera �N���X
	// @content		�J����
	// @use			�O���[�o�����W�n�̕`��Ɏg�p
	// @use			�z�C�[������ŉ�ʂ̊g�k�A�h���b�O����ŃJ�����̉�]���s��
	*/
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
		/*
		// @method		�R���X�g���N�^
		// @param		��ʂ̕��iint�j
		// @param		��ʂ̍����iint�j
		*/
		DefaultCamera(int width, int height);

		// �f�X�g���N�^
		virtual ~DefaultCamera() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update() override;

		/*
		// @method		Motion
		// @content		�h���b�O�ɂ���]���[�V����
		// @param		�}�E�X�̍��W�iVector2�j
		*/
		virtual void Motion(DirectX::SimpleMath::Vector2 mousePos);
	};
}