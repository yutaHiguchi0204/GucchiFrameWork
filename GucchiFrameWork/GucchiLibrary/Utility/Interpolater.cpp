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

// �ÓI�����o�̒�`
float Interpolater::startTime_ = 0.0f;
float Interpolater::nowTime_ = 0.0f;
bool Interpolater::isNowLerp_ = false;

// �����o�֐��̒�`

/*==============================================================
// @brief		���`��ԁifloat�j
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::LinearLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::LinearLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::LinearLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::LinearLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseInLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseInLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseInLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseInLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseOutLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseOutLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector3�j�A�I���iVector3�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseOutLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector4�j�A�I���iVector4�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseOutLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�ifloat�j�A�I���ifloat�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�ifloat�j
===============================================================*/
float Interpolater::EaseInOutLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector2�j
===============================================================*/
Vector2 Interpolater::EaseInOutLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector3�j
===============================================================*/
Vector3 Interpolater::EaseInOutLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		�J�n�iVector2�j�A�I���iVector2�j�A�����鎞�ԁifloat�A�P�ʁF�b�j�A�I�u�W�F�N�g�ʂ̃^�C�}�[�ifloat*�j
// @return		��Ԓl�iVector4�j
===============================================================*/
Vector4 Interpolater::EaseInOutLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// ��Ԓ��łȂ��Ȃ玞�ԓ���������
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// ���ԍX�V
	nowTime_ = *objTimer - startTime_;

	// ��Ԋ������ǂ���
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}