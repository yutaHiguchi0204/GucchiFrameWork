/* =====================================================================
//! @param		�uInterpolater�v�\�[�X�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Interpolater.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
float Interpolater::startTime_ = 0.0f;
float Interpolater::nowTime_ = 0.0f;
bool Interpolater::isNowInterpolate_ = false;

// �����o�֐��̒�`

/*==============================================================
// @brief		���`��ԁifloat�j
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::Lerp(float start, float end, float time, float objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		���`��ԁiVector2�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::Lerp(Vector2 start, Vector2 end, float time, float objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		���`��ԁiVector3�j
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::Lerp(Vector3 start, Vector3 end, float time, float objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		���`��ԁiVector4�j
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::Lerp(Vector4 start, Vector4 end, float time, float objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�オ�����j�ifloat�j
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseIn(float start, float end, float time, float objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�オ�����j�iVector2�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseIn(Vector2 start, Vector2 end, float time, float objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�オ�����j�iVector3�j
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseIn(Vector3 start, Vector3 end, float time, float objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�オ�����j�iVector4�j
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseIn(Vector4 start, Vector4 end, float time, float objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�悪�����j�ifloat�j
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseOut(float start, float end, float time, float objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�悪�����j�iVector2�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseOut(Vector2 start, Vector2 end, float time, float objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�悪�����j�iVector3�j
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseOut(Vector3 start, Vector3 end, float time, float objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		�񎟕�ԁi�悪�����j�iVector4�j
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseOut(Vector4 start, Vector4 end, float time, float objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		�O����ԁifloat�j
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseInOut(float start, float end, float time, float objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		�O����ԁiVector2�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseInOut(Vector2 start, Vector2 end, float time, float objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		�O����ԁiVector3�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseInOut(Vector3 start, Vector3 end, float time, float objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		�O����ԁiVector4�j
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseInOut(Vector4 start, Vector4 end, float time, float objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowInterpolate_)
	{
		startTime_ = objTimer;
		data = start;
		isNowInterpolate_ = true;
	}

	// ���ԍX�V
	nowTime_ = objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowInterpolate_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		��Ԓ����ǂ���
// @param		�Ȃ�
// @return		���ʁibool�j
===============================================================*/
bool Interpolater::IsInterpolate()
{
	return isNowInterpolate_;
}

// �R���X�g���N�^
InterpolateDirector::InterpolateDirector()
{
	// ���̉�
	stateF_ = make_unique<InterpolateState<float>>();
	stateV2_ = make_unique<InterpolateState<Vector2>>();
	stateV3_ = make_unique<InterpolateState<Vector3>>();
	stateV4_ = make_unique<InterpolateState<Vector4>>();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void InterpolateDirector::Update()
{
	stateF_->Update();
	stateV2_->Update();
	stateV3_->Update();
	stateV4_->Update();
}