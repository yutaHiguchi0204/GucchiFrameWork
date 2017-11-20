/* =====================================================================
//! @param		�uCamera�v�\�[�X
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Camera.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// �����o�֐��̒�`

// �R���X�g���N�^
Camera::Camera(int width, int height)
{
	// �r���[�̐ݒ�
	view_.viewMat	= Matrix::Identity;
	view_.eyePos	= Vector3(0.0f, 6.0f, 10.0f);
	view_.refPos	= Vector3(0.0f, 2.0f, 0.0f);
	view_.upVec		= Vector3(0.0f, 1.0f, 0.0f);

	// �v���W�F�N�V�����̐ݒ�
	proj_.projMat	= Matrix::Identity;
	proj_.fov		= XMConvertToRadians(60.0f);
	proj_.aspect	= (float)width / height;
	proj_.nearClip	= 0.1f;
	proj_.farClip	= 1000.0f;
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Camera::Update()
{
	// �r���[�s��̌v�Z
	view_.viewMat = Matrix::CreateLookAt(view_.eyePos, view_.refPos, view_.upVec);

	// �v���W�F�N�V�����s��̌v�Z
	proj_.projMat = Matrix::CreatePerspectiveFieldOfView(proj_.fov, proj_.aspect, proj_.nearClip, proj_.farClip);
}