/* =====================================================================
//! @param		�uAction�v�\�[�X�i�ړ��֌W���C�u�����j
//! @create		��� �T��
//! @date		17/12/02
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Action.h"
#include "../Utility/Interpolater.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;

// �����o�֐��̒�`

/*==============================================================
// @brief		���`�ړ��i��Έړ��j
// @param		�X�v���C�g�iSprite*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�I�_�iVector2�j
// @return		��Ԓl�iVector2�j
===============================================================*/
DirectX::SimpleMath::Vector2 MoveTo::Action(Sprite* sprite, float time, const Vector2& pos)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector2>* state = sprite->GetInterpolateDirector()->stateV2_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"MoveTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̈ʒu�i�n�_�j
		Vector2 start = sprite->GetPos();

		// �I�_
		Vector2 end = pos;

		// ���`���
		state->Entry(L"MoveTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveTo");
}

/*==============================================================
// @brief		���`�ړ��i��Έړ��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�I�_�iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 MoveTo::Action(Object* object, float time, const Vector3& trans)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"MoveTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̈ʒu�i�n�_�j
		Vector3 start = object->GetTranslate();

		// �I�_
		Vector3 end = trans;

		// ���`���
		state->Entry(L"MoveTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveTo");
}

/*==============================================================
// @brief		���`�ړ��i���Έړ��j
// @param		�X�v���C�g�iSprite*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector2�j
// @return		��Ԓl�iVector2�j
===============================================================*/
DirectX::SimpleMath::Vector2 MoveBy::Action(Sprite* sprite, float time, const Vector2& distance)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector2>* state = sprite->GetInterpolateDirector()->stateV2_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"MoveBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̈ʒu�i�n�_�j
		Vector2 start = sprite->GetPos();

		// �I�_
		Vector2 end = Vector2(start.x + distance.x, start.y + distance.y);

		// ���`���
		state->Entry(L"MoveBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveBy");
}

/*==============================================================
// @brief		���`�ړ��i���Έړ��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 MoveBy::Action(Object* object, float time, const Vector3& distance)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"MoveBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̈ʒu�i�n�_�j
		Vector3 start = object->GetTranslate();

		// �I�_
		Vector3 end = Vector3(start.x + distance.x, start.y + distance.y, start.z + distance.z);

		// ���`���
		state->Entry(L"MoveBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveBy");
}

/*==============================================================
// @brief		�X�P�[���ω��i��Εω��j
// @param		�X�v���C�g�iSprite*�j�A�ω��ɂ����鎞�ԁifloat�j�A�X�P�[���l�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float ScaleTo::Action(Sprite* sprite, float time, float scale)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"ScaleTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		float start = sprite->GetScale();

		// �I�_
		float end = scale;

		// ���`���
		state->Entry(L"ScaleTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleTo");
}

/*==============================================================
// @brief		�X�P�[���ω��i��Εω��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ω��ɂ����鎞�ԁifloat�j�A�X�P�[���l�iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 ScaleTo::Action(Object* object, float time, const Vector3& scale)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"ScaleTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		Vector3 start = object->GetScale();

		// �I�_
		Vector3 end = scale;

		// ���`���
		state->Entry(L"ScaleTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleTo");
}

/*==============================================================
// @brief		�X�P�[���ω��i���Εω��j
// @param		�X�v���C�g�iSprite*�j�A�ω��ɂ����鎞�ԁifloat�j�A���݂̃X�P�[������̔{���ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float ScaleBy::Action(Sprite* sprite, float time, const float scale)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"ScaleBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		float start = sprite->GetScale();

		// �I�_
		float end = start * scale;

		// ���`���
		state->Entry(L"ScaleBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleBy");
}

/*==============================================================
// @brief		�X�P�[���ω��i���Εω��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ω��ɂ����鎞�ԁifloat�j�A���݂̃X�P�[������̔{���iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 ScaleBy::Action(Object* object, float time, const Vector3& scale)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"ScaleBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		Vector3 start = object->GetScale();

		// �I�_
		Vector3 end = start * scale;

		// ���`���
		state->Entry(L"ScaleBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleBy");
}

/*==============================================================
// @brief		��]�i��Ή�]�j
// @param		�X�v���C�g�iSprite*�j�A��]�ɂ����鎞�ԁifloat�j�A��]�p�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float RotateTo::Action(Sprite* sprite, float time, float angle)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"RotateTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̉�]�p
		float start = sprite->GetAngle();

		// �I�_
		float end = angle;

		// ���`���
		state->Entry(L"RotateTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateTo");
}

/*==============================================================
// @brief		��]�i��Ή�]�j
// @param		�I�u�W�F�N�g�iObject*�j�A��]�ɂ����鎞�ԁifloat�j�A��]�p�iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 RotateTo::Action(Object* object, float time, const Vector3& rot)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"RotateTo") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̉�]�p
		Vector3 start = object->GetRotate();

		// �I�_
		Vector3 end = rot;

		// ���`���
		state->Entry(L"RotateTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateTo");
}

/*==============================================================
// @brief		��]�i���Ή�]�j
// @param		�X�v���C�g�iSprite*�j�A��]�ɂ����鎞�ԁifloat�j�A���݂̊p�x����̉�]�p�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float RotateBy::Action(Sprite* sprite, float time, float angle)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"RotateBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		float start = sprite->GetAngle();

		// �I�_
		float end = start + angle;

		// ���`���
		state->Entry(L"RotateBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateBy");
}

/*==============================================================
// @brief		��]�i���Ή�]�j
// @param		�I�u�W�F�N�g�iObject*�j�A��]�ɂ����鎞�ԁifloat�j�A���݂̊p�x����̉�]�p�iVector3�j
// @return		��Ԓl�iVector3�j
===============================================================*/
DirectX::SimpleMath::Vector3 RotateBy::Action(Object* object, float time, const Vector3& rot)
{
	// ��ԃX�e�[�g�̏���
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// �J�n���ĂȂ��������ԊJ�n
	if (state->GetState(L"RotateBy") == INTERPOLATE_STATE::NONE)
	{
		// ���݂̃X�P�[��
		Vector3 start = object->GetRotate();

		// �I�_
		Vector3 end = start + rot;

		// ���`���
		state->Entry(L"RotateBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateBy");
}