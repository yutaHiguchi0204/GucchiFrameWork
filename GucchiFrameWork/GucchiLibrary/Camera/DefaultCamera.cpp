/* =====================================================================
//! @param		�uDefaultCamera�v�\�[�X
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "DefaultCamera.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// �ÓI�����o�̒�`
const float DefaultCamera::DEFAULT_DISTANCE = 5.0f;

// �����o�֐��̒�`

// �R���X�g���N�^
DefaultCamera::DefaultCamera(int width, int height)
	: Camera(width, height)
	, angle_(Vector2::Zero)
	, tmpAngle_(Vector2::Zero)
	, dragStartPos_(Vector2::Zero)
	, wheelValue_(0)
{
	// ��ʃT�C�Y�ɑ΂��鑊�΃X�P�[����ݒ�
	relScale_ = Vector2(1.0f / width, 1.0f / height);
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void DefaultCamera::Update()
{
	// �e�N���X�̍X�V
	Camera::Update();

	/* �h���b�O�ŃJ�����𓮂��� */
	// �h���b�O�J�n
	if (mouse_.GetTracker().leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// �}�E�X�̍��W���擾
		dragStartPos_ = Vector2((float)mouse_.GetState().x, (float)mouse_.GetState().y);
	}
	// �h���b�O�I��
	else if (mouse_.GetTracker().leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// ���݂̉�]�p��ۑ�
		angle_ = tmpAngle_;
	}

	// �h���b�O���̓J�����ړ�
	if (mouse_.GetState().leftButton)
	{
		Motion(Vector2((float)mouse_.GetState().x, (float)mouse_.GetState().y));
	}

	// �}�E�X�̃t�H�C�[���l�ŃJ�����̃r���[�g�嗦���m��
	wheelValue_ = mouse_.GetState().scrollWheelValue;
	if (wheelValue_ > 0)
	{
		wheelValue_ = 0;
		mouse_.GetMouse()->ResetScrollWheelValue();
	}

	// �r���[�s��̎Z�o
	Matrix rotY = Matrix::CreateRotationY(tmpAngle_.y);
	Matrix rotX = Matrix::CreateRotationX(tmpAngle_.x);
	Matrix rot = rotY * rotX;

	// �r���[�A���O���̏�����
	view_.eyePos = Vector3(0.0f, 0.0f, 1.0f);
	view_.refPos = Vector3::Zero;
	view_.upVec = Vector3(0.0f, 1.0f, 0.0f);

	// �r���[�A���O���̍X�V
	view_.eyePos = Vector3::Transform(view_.eyePos, rot.Invert());
	view_.eyePos *= (DEFAULT_DISTANCE - wheelValue_ / 100);
	view_.upVec = Vector3::Transform(view_.upVec, rot.Invert());

	// �r���[�A���O���m��
	view_.viewMat = Matrix::CreateLookAt(view_.eyePos, view_.refPos, view_.upVec);
}

/*==============================================================
// @brief		�J������]���[�V����
// @param		�}�E�X�̍��W�iVector2�j
// @return		�Ȃ�
===============================================================*/
void DefaultCamera::Motion(Vector2 mousePos)
{
	// ���΍��W�̎擾
	Vector2 dragPos;
	dragPos.x = (mousePos.x - dragStartPos_.x) * relScale_.x;
	dragPos.y = (mousePos.y - dragStartPos_.y) * relScale_.y;

	// �h���b�O����Ă������]������
	if (dragPos.x != 0.0f || dragPos.y != 0.0f)
	{
		// ��]
		Vector2 angle = Vector2(dragPos.y * XM_PI, dragPos.x * XM_PI);

		// ��]�p�̕ۑ�
		tmpAngle_ = angle_ + angle;
	}
}