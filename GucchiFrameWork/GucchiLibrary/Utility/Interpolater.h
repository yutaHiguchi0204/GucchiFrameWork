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
#include "../Common/Constant.h"

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
	// @mode		SPHERE_LERP	�F	���ʐ��`���
	*/
	enum class INTERPOLATE_MODE : int
	{
		LERP,
		EASE_IN,
		EASE_OUT,
		EASE_INOUT,
		SPHERE_LERP
	};

	class Interpolater;

	/*
	// @class		InterpolateState �N���X�itemplate�j
	// @content		��ԗp�X�e�[�g
	*/
	template <class T>
	class InterpolateState
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	private:
		std::map<std::wstring, float>									timer_;			// ���[�J���^�C�}�[
		std::map<std::wstring, INTERPOLATE_STATE>						state_;			// ��Ԓ����ǂ���

		std::map<std::wstring, T>										start_;			// �n�_
		std::map<std::wstring, T>										end_;			// �I�_
		std::map<std::wstring, float>									runTime_;		// ���s����
		std::map<std::wstring, INTERPOLATE_MODE>						mode_;			// ��ԃ��[�h

		std::map<std::wstring, float>									startTime_;		// ��ԊJ�n���_�̎���
		std::map<std::wstring, float>									nowTime_;		// ��Ԓ��ł̎���

	public:
		// �R���X�g���N�^
		InterpolateState() = default;

		// �f�X�g���N�^
		virtual ~InterpolateState()
		{
			timer_.clear();
			state_.clear();
			start_.clear();
			end_.clear();
			runTime_.clear();
			mode_.clear();
			startTime_.clear();
			nowTime_.clear();
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
		// @result		��Ԍ��ʁiT�j
		*/
		T GetResult(const std::wstring& action)
		{
			if (state_[action] != INTERPOLATE_STATE::FINISH)
			{
				// ���ʂ��擾
				return Interpolate(mode_[action], start_[action], end_[action], runTime_[action], action, this);
			}

			return end_[action];
		}

		/*
		// @method		GetResult
		// @content		��Ԍ��ʂ̎擾�i���g�p��ԁj
		// @param		��ԃA�N�V�������iwstring�j
		// @result		��Ԍ��ʁiT�j
		*/
		Vector3 GetResult(const std::wstring& action, const Vector3& axis)
		{
			if (state_[action] != INTERPOLATE_STATE::FINISH)
			{
				// ���ʂ��擾
				return Interpolate(mode_[action], start_[action], end_[action], axis, runTime_[action], action, this);
			}

			return end_[action];
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
					return true;
				}
			}

			return false;
		}

		/*
		// @method		GetState
		// @content		��ԏ�Ԃ̎擾�i�A�N�V�������������NONE��Ԃ��j
		// @result		��ԏ�ԁiINTERPOLATE_STATE�j
		*/
		INTERPOLATE_STATE GetState(const std::wstring& action)
		{
			if (state_.count(action) == 0)
			{
				return INTERPOLATE_STATE::NONE;
			}

			return state_[action];
		}

		/*
		// @method		Reset
		// @content		���Z�b�g
		*/
		void Reset()
		{
			timer_.clear();
			state_.clear();
			start_.clear();
			end_.clear();
			runTime_.clear();
			mode_.clear();
		}

		/* �A�N�Z�b�T */

		void SetState(const std::wstring& action, INTERPOLATE_STATE state)	{ state_[action] = state; }

		inline float GetTimer(const std::wstring& action)					{ return timer_[action]; }

	private:
		/*
		// @method		Interpolate
		// @content		��Ԃł̋��ʏ���
		// @param		��ԃ��[�h�iINTERPOLATE_MODE�j
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<T>*�j
		// @result		��Ԓl�iT�j
		*/
		T Interpolate(INTERPOLATE_MODE mode, const T& start, const T& end, float time, const std::wstring& action, InterpolateState<T>* state)
		{
			// ��Ԓ��łȂ��Ȃ玞�ԓ���������
			if (state->GetState(action) == INTERPOLATE_STATE::NONE)
			{
				startTime_[action] = state->GetTimer(action);
				state->SetState(action, INTERPOLATE_STATE::NOW);
			}

			// ���ԍX�V
			nowTime_[action] = state->GetTimer(action) - startTime_[action];

			// ��Ԋ������ǂ���
			if (nowTime_[action] >= (time * FRAME_PER_SECOND))
			{
				state->SetState(action, INTERPOLATE_STATE::FINISH);
				return end;
			}

			float lerpTime = nowTime_[action] / (time * FRAME_PER_SECOND);

			// ��Ԉړ�
			return GetResultToInterpolateMode(mode, start, end, lerpTime);
		}

		/*
		// @method		Interpolate
		// @content		��Ԃł̋��ʏ���
		// @param		��ԃ��[�h�iINTERPOLATE_MODE�j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���iVector3�j	�F	�f�t�H���g�iVector3::Zero�j
		// @param		�}��ϐ��ifloat�j
		// @param		��ԃA�N�V�������iwstring�j
		// @param		��ԃX�e�[�g�iInterpolateState<Vector3>*�j
		// @result		��Ԓl�iVector3�j
		*/
		Vector3 Interpolate(INTERPOLATE_MODE mode, const Vector3& start, const Vector3& end, const Vector3& axis, float time, const std::wstring& action, InterpolateState<Vector3>* state)
		{
			// ��Ԓ��łȂ��Ȃ玞�ԓ���������
			if (state->GetState(action) == INTERPOLATE_STATE::NONE)
			{
				startTime_[action] = state->GetTimer(action);
				state->SetState(action, INTERPOLATE_STATE::NOW);
			}

			// ���ԍX�V
			nowTime_[action] = state->GetTimer(action) - startTime_[action];

			// ��Ԋ������ǂ���
			if (nowTime_[action] >= (time * FRAME_PER_SECOND))
			{
				state->SetState(action, INTERPOLATE_STATE::FINISH);
				return end;
			}

			float lerpTime = nowTime_[action] / (time * FRAME_PER_SECOND);

			// ��Ԉړ�
			return GetResultToInterpolateMode(mode, start, end, axis, lerpTime);
		}

		/*
		// @method		GetResultToInterpolateMode
		// @method		�w�肵�����[�h�����Ԓl���擾
		// @param		��ԃ��[�h�iINTERPOLATE_MODE�j
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iT�j
		*/
		T GetResultToInterpolateMode(INTERPOLATE_MODE mode, const T& start, const T& end, float time)
		{
			T result;

			switch (mode)
			{
			case INTERPOLATE_MODE::LERP:			// ���`���	
				result = Lerp(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_IN:			// �񎟕�ԁi�オ�����j
				result = EaseIn(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_OUT:		// �񎟕�ԁi�悪�����j
				result = EaseOut(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_INOUT:		// �O�����
				result = EaseInOut(start, end, time);
				break;

			default:
				break;
			}

			return result;
		}

		/*
		// @method		GetResultToInterpolateMode
		// @method		�w�肵�����[�h�����Ԓl���擾
		// @param		��ԃ��[�h�iINTERPOLATE_MODE�j
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		���iVector3�j	�F	�f�t�H���g�iVector3::Zero�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iVector3�j
		*/
		Vector3 GetResultToInterpolateMode(INTERPOLATE_MODE mode, const Vector3& start, const Vector3& end, const Vector3& axis, float time)
		{
			Vector3 result;

			switch (mode)
			{
			case INTERPOLATE_MODE::SPHERE_LERP:		// ���ʐ��`���
				result = SphereLerp(start, end, axis, time);

			default:
				break;
			}

			return result;
		}

		/*
		// @method		Lerp�istatic�j
		// @method		���`���
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iT�j
		*/
		static T Lerp(const T& start, const T& end, float t)
		{
			return start + (end - start) * t;
		}

		/*
		// @method		EaseIn�istatic�j
		// @method		�񎟕�ԁi�オ�����j
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iT�j
		*/
		static T EaseIn(const T& start, const T& end, float t)
		{
			return start + (end - start) * (t * t);
		}

		/*
		// @method		EaseOut�istatic�j
		// @method		�񎟕�ԁi�悪�����j
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iT�j
		*/
		static T EaseOut(const T& start, const T& end, float t)
		{
			return start + (end - start) * (t * (2.0f - t));
		}

		/*
		// @method		EaseInOut�istatic�j
		// @method		�O�����
		// @param		�n�_�iT�j
		// @param		�I�_�iT�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iT�j
		*/
		static T EaseInOut(const T& start, const T& end, float t)
		{
			return start + (end - start) * ((t * t) * (3.0f - t * 2.0f));
		}

		/*
		// @method		SphereLerp
		// @method		���ʐ��`���
		// @param		�n�_�iVector3�j
		// @param		�I�_�iVector3�j
		// @param		�}��ϐ��ifloat�j
		// @return		��Ԓl�iVector3�j
		*/
		static Vector3 SphereLerp(const Vector3& start, const Vector3& end, const Vector3& axis, float t)
		{
			// ������̃x�N�g�����擾
			Vector3 s = start - axis;
			Vector3 e = end - axis;
			s.Normalize();	e.Normalize();

			// �Q�x�N�g���Ԃ̉s�p�̊p�x�����߂�
			float angle = acosf(s.Dot(e));

			// sin�Ƃ����߂�
			float sinTh = sinf(angle);

			// ���`��ԌW�������߂�
			float sPos = sinf(angle * (1 - t));
			float ePos = sinf(angle * t);

			// �n�_����I�_�܂ł̐��`���
			Vector3 data = (sPos * s + ePos * e) / (sinTh == 0 ? 0.0000001f : sinTh);
			data.Normalize();

			// ���a�����߂�
			float rad = (start - axis).Length();

			return data * rad + axis;
		}
	};

	/*
	// @class		InterpolateDirector �N���X
	// @content		�S�^�C�v�̕�Ԃ����邽�߂̑q��
	*/
	class InterpolateDirector
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		std::unique_ptr<InterpolateState<float>>		stateF_;
		std::unique_ptr<InterpolateState<Vector2>>		stateV2_;
		std::unique_ptr<InterpolateState<Vector3>>		stateV3_;
		std::unique_ptr<InterpolateState<Vector4>>		stateV4_;

	public:
		// �R���X�g���N�^
		InterpolateDirector()
		{
			// ���̉�
			stateF_  = std::make_unique<InterpolateState<float>>();
			stateV2_ = std::make_unique<InterpolateState<Vector2>>();
			stateV3_ = std::make_unique<InterpolateState<Vector3>>();
			stateV4_ = std::make_unique<InterpolateState<Vector4>>();
		}

		// �f�X�g���N�^
		virtual ~InterpolateDirector() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update()
		{
			stateF_->Update();
			stateV2_->Update();
			stateV3_->Update();
			stateV4_->Update();
		}

		/*
		// @method		Reset
		// @content		�S�X�e�[�g�̃��Z�b�g
		*/
		void Reset()
		{
			stateF_->Reset();
			stateV2_->Reset();
			stateV3_->Reset();
			stateV4_->Reset();
		}
	};
}