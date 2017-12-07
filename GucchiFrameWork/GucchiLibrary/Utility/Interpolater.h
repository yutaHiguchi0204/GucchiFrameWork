/* =====================================================================
//! @param		�uInterpolater�v�w�b�_�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <functional>
#include <map>
#include <SimpleMath.h>
#include <string>

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

	/*
	// @content		���
	// @mode		NONE	�F�@�������Ă��Ȃ����
	// @mode		LERP	�F�@��Ԓ�
	// @mode		OUT		�F�@��ԏI��
	*/
	enum class INTERPOLATE_STATE : int
	{
		NONE,
		NOW,
		FINISH
	};

	/*
	// @class		InterpolateState �N���X�itemplate�j
	// @content		��ԗp�X�e�[�g
	*/
	template <class T>
	class InterpolateState
	{
	private:
		std::map<std::wstring, float>				timer_;			// ���[�J���^�C�}�[
		std::map<std::wstring, INTERPOLATE_STATE>	state_;			// ��Ԓ����ǂ���

		std::map<std::wstring, T>					start_;			// �n�_
		std::map<std::wstring, T>					end_;			// �I�_
		std::map<std::wstring, float>				runTime_;		// ���s����

	public:
		// �R���X�g���N�^
		InterpolateState() {}

		// �f�X�g���N�^
		virtual ~InterpolateState()
		{
			timer_.clear();
			state_.clear();
		}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update()
		{
			// �^�C�}�[�v��
			for (auto& timer : timer_)
			{
				timer++;
			}
		}

		/*
		// @method		Entry
		// @content		��ԊJ�n
		// @param		��ԃA�N�V�������iwstring�j
		*/
		void Entry(std::wstring action, T start, T end, float runTime)
		{
			timer_[action] = 0;
			state_[action] = INTERPOLATE_STATE::NONE;

			start_[action] = start;
			end_[action] = end;
			runTime_[action] = runTime;
		}

		/*
		// @method		GetResult
		// @content		��Ԍ��ʂ̎擾
		// @param		��ԃA�N�V�������iwstring�j
		// @result		��Ԍ��ʁiT�j
		*/
		T GetResult(std::wstring action, std::function<T(T, T, float, float)> func)
		{
			if (state_[action] == INTERPOLATE_STATE::NONE)
			{
				state_[action] = INTERPOLATE_STATE::NOW;
			}

			// ���ʂ��擾
			T result = func(start_[action], end_[action], runTime_[action], timer[action]);

			// ��Ԃ��I�����Ă�����X�e�[�g���I���ɕς���
			if (!Interpolater::IsLerp())
			{
				state_[action] = INTERPOLATE_STATE::FINISH;
			}
		}

		/*
		// @method		IsInterpolate
		// @content		��Ԓ����ǂ���
		// @result		���ʁibool�j
		*/
		bool IsInterpolate()
		{
			for (auto& state : state_)
			{
				if (!state == INTERPOLATE_STATE::FINISH)
				{
					return false;
				}
			}

			return true;
		}

		/* �A�N�Z�b�T */

		inline const float				GetTimer(std::wstring action) { return timer_[action]; }
		inline const INTERPOLATE_STATE	GetState(std::wstring action) { return state_[action]; }
	};
}