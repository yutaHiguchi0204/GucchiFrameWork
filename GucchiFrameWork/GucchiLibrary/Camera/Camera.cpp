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
	
	// �r���{�[�h�s����v�Z
	CalcBillboard();
}

/*==============================================================
// @brief		�r���{�[�h�s��̌v�Z
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Camera::CalcBillboard()
{
	// ��������
	Vector3 eyeDir = view_.eyePos - view_.refPos;

	// Y��
	Vector3 axisY = Vector3::UnitY;

	// X��
	Vector3 axisX = axisY.Cross(eyeDir);
	axisX.Normalize();

	// Z��
	Vector3 axisZ = axisX.Cross(axisY);
	axisZ.Normalize();

	// Y������r���{�[�h�s��i�E��n�̈�Z�������]�j
	billboardConstrainY_ = Matrix::Identity;
	billboardConstrainY_.m[0][0] = axisX.x;
	billboardConstrainY_.m[0][1] = axisX.y;
	billboardConstrainY_.m[0][2] = axisX.z;
	billboardConstrainY_.m[1][0] = axisY.x;
	billboardConstrainY_.m[1][1] = axisY.y;
	billboardConstrainY_.m[1][2] = axisY.z;
	billboardConstrainY_.m[2][0] = -axisZ.x;
	billboardConstrainY_.m[2][1] = -axisZ.y;
	billboardConstrainY_.m[2][2] = -axisZ.z;

	axisY = eyeDir.Cross(axisX);
	axisY.Normalize();
	eyeDir.Normalize();

	// �r���{�[�h�s��i�E��n�̈�Z�������]�j
	billboard_ = Matrix::Identity;
	billboard_.m[0][0] = axisX.x;
	billboard_.m[0][1] = axisX.y;
	billboard_.m[0][2] = axisX.z;
	billboard_.m[1][0] = axisY.x;
	billboard_.m[1][1] = axisY.y;
	billboard_.m[1][2] = axisY.z;
	billboard_.m[2][0] = -eyeDir.x;
	billboard_.m[2][1] = -eyeDir.y;
	billboard_.m[2][2] = -eyeDir.z;
}