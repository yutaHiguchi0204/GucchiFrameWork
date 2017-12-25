/* =====================================================================
//! @param		�uInterpolater�v�w�b�_�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <SimpleMath.h>
#include <string>

namespace GucchiLibrary
{
	/*
	// @content		���
	// @mode		NONE	�F�@�������Ă��Ȃ����
	// @mode		NOW		�F�@��Ԓ�
	// @mode		FINISH	�F�@��ԏI��
	*/
	enum class INTERPOLATE_STATE : int
	{
		NONE,
		NOW,
		FINISH
	};

	/*
	// @content		�g�p�����Ԋ֐�
	// @mode		LERP		�F	���`���
	// @mode		EASE_IN		�F	�񎟕�ԁi�オ�����j
	// @mode		EASE_OUT	�F	�񎟕�ԁi�悪�����j
	// @mode		EASE_INOUT	�F	�O�����
	*/
	enum class INTERPOLATE_MODE : int
	{
		LERP,
		EASE_IN,
		EASE_OUT,
		EASE_INOUT
	};

	/*
	// @class		InterpolateState �N���X�itemplate�j
	// @content		��ԗp�X�e�[�g
	*/
	template <class T>
	class InterpolateState
	{
	private:
		std::map<std::wstring, float>									timer_;			// ���[�J���^�C�}�[
		std::map<std::wstring, INTERPOLATE_STATE>						state_;			// ��Ԓ����ǂ���

		std::map<std::wstring, T>										start_;			// �n�_
		std::map<std::wstring, T>										end_;			// �I�_
		std::map<std::wstring, float>									runTime_;		// ���s����
		std::map<std::wstring, INTERPOLATE_MODE>						mode_;			// ��ԃ��[�h

	public:
		// �R���X�g���N�^
		InterpolateState() {}

		// �f�X�g���N�^
		virtual ~InterpolateState()
		{
			timer_.clear();
			state_.clear();
			start_.clear();
			end_.clear();
			runTime_.clear();
			mode_.clear();
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
				timer.second++;
			}
		}

		/*
		// @method		Entry
		// @content		��ԊJ�n
		// @param		��ԃA�N�V�������iwstring�j
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		���s���ԁifloat�j
		// @param		��ԃ��[�h�iINTERPOLATE_MODE�j
		*/
		void Entry(std::wstring action, T start, T end, float runTime, INTERPOLATE_MODE mode)
		{
			timer_[action] = 0;
			state_[action] = INTERPOLATE_STATE::NONE;

			start_[action] = start;
			end_[action] = end;
			runTime_[action] = runTime;
			mode_[action] = mode;
		}

		/*
		// @method		GetResult
		// @content		��Ԍ��ʂ̎擾
		// @param		��ԃA�N�V�������iwstring�j
		// @param		�n�_�iT�j
		// @result		��Ԍ��ʁiT�j
		*/
		T GetResult(std::wstring action)
		{
			T result;

			if (state_[action] != INTERPOLATE_STATE::FINISH)
			{
				// ���ʂ��擾
				switch (mode_[action])
				{
				case INTERPOLATE_MODE::LERP:		result = Interpolater::Lerp(start_[action], end_[action], runTime_[action], action, this);			break;
				case INTERPOLATE_MODE::EASE_IN:		result = Interpolater::EaseIn(start_[action], end_[action], runTime_[action], action, this);		break;
				case INTERPOLATE_MODE::EASE_OUT:	result = Interpolater::EaseOut(start_[action], end_[action], runTime_[action], action, this);		break;
				case INTERPOLATE_MODE::EASE_INOUT:	result = Interpolater::EaseInOut(start_[action], end_[action], runTime_[action], action, this);		break;
				}
			}
			else
			{
				result = end_[action];
			}

			return result;
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
				if (state.second != INTERPOLATE_STATE::FINISH)
				{
					return false;
				}
			}

			return true;
		}

		/*
		// @method		GetState
		// @content		��ԏ�Ԃ̎擾�i�A�N�V�������������NONE��Ԃ��j
		// @result		��ԏ�ԁiINTERPOLATE_STATE�j
		*/
		const INTERPOLATE_STATE GetState(std::wstring action)
		{
			if (state_.count(action) == 0)
			{
				return INTERPOLATE_STATE::NONE;
			}

			return state_[action];
		}

		/* �A�N�Z�b�T */

		void SetState(std::wstring action, INTERPOLATE_STATE state) { state_[action] = state; }

		inline const float GetTimer(std::wstring action) { return timer_[action]; }
	};

	/*
	// @class		Interpolater �N���X
	// @content		��ԃ��C�u����
	*/
	class Interpolater
	{
	private:
		static float startTime_;
		static float nowTime_;

	public:
		/* ���`��� */

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<float>*�j
		*/
		static float Lerp(float start, float end, float time, std::wstring action, InterpolateState<float>* state);

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector2>*�j
		*/
		static DirectX::SimpleMath::Vector2 Lerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector2>* state);

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector3>*�j
		*/
		static DirectX::SimpleMath::Vector3 Lerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector3>* state);

		/*
		// @method		Lerp�istatic�j
		// @content		���`���
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector4>*�j
		*/
		static DirectX::SimpleMath::Vector4 Lerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector4>* state);

		/* �񎟕�ԁi�オ�����j */

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<float>*�j
		*/
		static float EaseIn(float start, float end, float time, std::wstring action, InterpolateState<float>* state);

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector2>*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseIn(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector2>* state);

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector3>*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseIn(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector3>* state);

		/*
		// @method		EaseIn�istatic�j
		// @content		�񎟕�ԁi�オ�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector4>*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseIn(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector4>* state);

		/* �񎟕�ԁi�悪�����j */

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<float>*�j
		*/
		static float EaseOut(float start, float end, float time, std::wstring action, InterpolateState<float>* state);

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector2>*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector2>* state);

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector3>*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector3>* state);

		/*
		// @method		EaseOut�istatic�j
		// @content		�񎟕�ԁi�悪�����j
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector4>*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector4>* state);

		/* �O����� */

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�ifloat�j
		// @param		�I�_�ifloat�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<float>*�j
		*/
		static float EaseInOut(float start, float end, float time, std::wstring action, InterpolateState<float>* state);

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector2�j
		// @param		�I�_�iVector2�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector2>*�j
		*/
		static DirectX::SimpleMath::Vector2 EaseInOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector2>* state);

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector3>*�j
		*/
		static DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector3>* state);

		/*
		// @method		EaseInOut�istatic�j
		// @content		�O�����
		// @param		�n�_�iVector4�j
		// @param		�I�_�iVector4�j
		// @param		���s���ԁifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector4>*�j
		*/
		static DirectX::SimpleMath::Vector4 EaseInOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, std::wstring action, InterpolateState<DirectX::SimpleMath::Vector4>* state);
	};

	/*
	// @class		InterpolateDirector �N���X
	// @content		�S�^�C�v�̕�Ԃ����邽�߂̑q��
	*/
	class InterpolateDirector
	{
	public:
		std::unique_ptr<InterpolateState<float>>							stateF_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector2>>		stateV2_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector3>>		stateV3_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector4>>		stateV4_;

	public:
		// �R���X�g���N�^
		InterpolateDirector();

		// �f�X�g���N�^
		virtual ~InterpolateDirector() {}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update();
	};
}