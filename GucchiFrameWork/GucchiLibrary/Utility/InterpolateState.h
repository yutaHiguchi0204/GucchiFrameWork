/* =====================================================================
//! @param		�uInterpolateState�v�w�b�_
//! @create		��� �T��
//! @date		17/12/07
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <functional>
#include <map>
#include <string>
#include "Interpolater.h"

namespace GucchiLibrary
{
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
			T result =  func(start_[action], end_[action], runTime_[action], timer[action]);

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