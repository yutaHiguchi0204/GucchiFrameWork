/* =====================================================================
//! @param		�uInterpolater�v�w�b�_�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	/*
	// @class		Interpolater �N���X
	// @content		��ԃ��C�u����
	*/
	class Interpolater
	{
	private:
		static float startTime_;
		static float nowTime_;
		static bool isNowLerp_;

	public:
		/* ���`��� */

		/*
		// @method		LinearLerp�istatic�j
		// @content		���`���
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static float LinearLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		LinearLerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector2 LinearLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);

		/*
		// @method		LinearLerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector3 LinearLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		LinearLerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector4 LinearLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* �񎟕�ԁi�オ�����j */

		/*
		// @method		EaseInLerp�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static float EaseInLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseInLerp�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseInLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseInLerp�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseInLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseInLerp�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseInLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* �񎟕�ԁi�悪�����j */

		/*
		// @method		EaseOutLerp�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static float EaseOutLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseOutLerp�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseOutLerp�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseOutLerp�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* �O����� */

		/*
		// @method		EaseInOutLerp�istatic�j
		// @content		�O�����
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static float EaseInOutLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseInOutLerp�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseInOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseInOutLerp�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseInOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseInOutLerp�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseInOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);
	};
}