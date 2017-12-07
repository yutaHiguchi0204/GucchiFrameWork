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
		static bool isNowInterpolate_;

	public:
		/* ���`��� */

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static float Lerp(float start, float end, float time, float objTimer);

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector2 Lerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector3 Lerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector4 Lerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* �񎟕�ԁi�オ�����j */

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static float EaseIn(float start, float end, float time, float objTimer);

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector2 EaseIn(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector3 EaseIn(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector4 EaseIn(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* �񎟕�ԁi�悪�����j */

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static float EaseOut(float start, float end, float time, float objTimer);

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector2 EaseOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector3 EaseOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector4 EaseOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* �O����� */

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static float EaseInOut(float start, float end, float time, float objTimer);

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector2 EaseInOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		���[�J���^�C�}�[�ifloat�j
		*/
		static DirectX::SimpleMath::Vector4 EaseInOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/*
		// @method		IsInterpolate�istatic�j
		// @content		��Ԓ����ǂ���
		// @return		���ʁibool�j
		*/
		static bool IsInterpolate();
	};
}