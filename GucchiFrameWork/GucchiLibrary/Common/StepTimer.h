/* =====================================================================
//! @param		�uStepTimer�v�w�b�_
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>
#include <exception>
#include <stdint.h>

namespace GucchiLibrary
{
	// �A�j���[�V�����ƃV�~�����[�V�����̃^�C�~���O�w���p�[
	class StepTimer
	{
	public:
		// 10,000,000 Ticks/s
		static const uint64_t TicksPerSecond;

	public:
		static double TicksToSeconds(uint64_t ticks)	{ return static_cast<double>(ticks) / TicksPerSecond; }
		static uint64_t SecondsToTicks(double seconds)	{ return static_cast<uint64_t>(seconds * TicksPerSecond); }

	private:
		// QPC���j�b�g
		LARGE_INTEGER	qpcFrequency_;
		LARGE_INTEGER	qpcLastTime_;
		uint64_t		qpcMaxDelta_;

		// �e�B�b�N�`��
		uint64_t		elapsedTicks_;
		uint64_t		totalTicks_;
		uint64_t		leftOverTicks_;

		// �t���[�����[�g�ǐ�
		uint32_t		frameCount_;
		uint32_t		framesPerSecond_;
		uint32_t		framesThisSecond_;
		uint64_t		qpcSecondCounter_;

		// �^�C���X�e�b�v���[�h�\��
		bool			isFixedTimeStep_;
		uint64_t		targetElapsedTicks_;

	public:
		StepTimer();

		// Update��񂩂�o�ߎ��Ԃ��擾
		inline uint64_t GetElapsedTicks() const				{ return elapsedTicks_; }
		inline double	GetElapsedSeconds() const			{ return TicksToSeconds(elapsedTicks_); }

		// �v���O�����̊J�n���猻�݂܂ł̍��v���Ԃ��擾
		inline uint64_t GetTotalTicks() const				{ return totalTicks_; }
		inline double	GetTotalSeconds() const				{ return TicksToSeconds(totalTicks_); }

		// �v���O�������J�n���Ă���̍X�V�������擾
		inline uint32_t GetFrameCount() const				{ return frameCount_; }

		// ���݂̃t���[�����[�g���擾
		inline uint32_t GetFramesPerSecond() const			{ return framesPerSecond_; }

		// �Œ�܂��͉σ^�C���X�e�b�v���[�h���g�p���邩�ǂ����̐ݒ�
		void SetFixedTimeStep(bool isFixedTimestep)			{ isFixedTimeStep_ = isFixedTimestep; }

		// �^�C���X�e�b�v���[�h�ōX�V���Ăяo���p�x��ݒ�
		void SetTargetElapsedTicks(uint64_t targetElapsed)	{ targetElapsedTicks_ = targetElapsed; }
		void SetTargetElapsedSeconds(double targetElapsed)	{ targetElapsedTicks_ = SecondsToTicks(targetElapsed); }

		// �Ӑ}�I�ȃ^�C�~���O�̕s�A�����i�Ⴆ�΁AIO�̓����j�~����j�̌�A������R�[�����āA�C�����ꂽ�^�C���X�e�b�v�_������A�̒ǂ����̍X�V�Ăяo�������݂�̂������
		void ResetElapsedTime();

		// �^�C�}�[�̏�Ԃ��X�V���A�w�肳�ꂽUpdate�֐���K�؂ȉ񐔌Ăяo��
		template<typename TUpdate>
		void Tick(const TUpdate& update)
		{
			// ���ԏƉ�
			LARGE_INTEGER currentTime;

			if (!QueryPerformanceCounter(&currentTime))
			{
				throw std::exception("QueryPerformanceCounter");
			}

			uint64_t timeDelta = currentTime.QuadPart - qpcLastTime_.QuadPart;

			qpcLastTime_ = currentTime;
			qpcSecondCounter_ += timeDelta;

			// �f���^�N�����v
			if (timeDelta > qpcMaxDelta_)
			{
				timeDelta = qpcMaxDelta_;
			}

			// QPC�P�ʂ𐳋K�̃`�b�N�`���ɕϊ�
			timeDelta *= TicksPerSecond;
			timeDelta /= qpcFrequency_.QuadPart;

			uint32_t lastFrameCount = frameCount_;

			if (isFixedTimeStep_)
			{
				// �Œ�^�C���X�e�b�v�X�V���W�b�N

				// �A�v�����ڕW�o�ߎ��ԁi�~���b��1/4�ȓ��j�ɔ��ɋ߂��Ƃ���Ŏ��s����Ă���ꍇ�A�ڕW�l�ɐ��m�Ɉ�v����悤�ɃN���b�N���N�����v���邾���ł��B
				// ����ɂ��A���Ԃ̌o�߂Ƌ��ɏ������Ė��֌W�ȃG���[���~�ς���邱�Ƃ�h���܂��B
				// ���̃N�����v���Ȃ���΁A59.94 NTSC�f�B�X�v���C��vsync��L���ɂ��Ď��s����Ă���60 fps�̌Œ�A�b�v�f�[�g��v�������Q�[���́A�ŏI�I�Ƀt���[���𗎂Ƃ��قǂ̏����ȃG���[��~�ς��܂��B
				// �X���[�Y�ɓ��삳���邽�߂ɁA�����ȕ΍����[���Ɋۂ߂�ق����ǂ��ł��B

				if (abs(static_cast<int64_t>(timeDelta - targetElapsedTicks_)) < static_cast<int64_t>(TicksPerSecond) / 4000)
				{
					timeDelta = targetElapsedTicks_;
				}

				leftOverTicks_ += timeDelta;

				while (leftOverTicks_ >= targetElapsedTicks_)
				{
					elapsedTicks_ = targetElapsedTicks_;
					totalTicks_ += targetElapsedTicks_;
					leftOverTicks_ -= targetElapsedTicks_;
					frameCount_++;

					update();
				}
			}
			else
			{
				// �σ^�C���X�e�b�v�X�V���W�b�N
				elapsedTicks_ = timeDelta;
				totalTicks_ += timeDelta;
				leftOverTicks_ = 0;
				frameCount_++;

				update();
			}

			// �t���[�����[�g�̒ǐ�
			if (frameCount_ != lastFrameCount)
			{
				framesThisSecond_++;
			}

			if (qpcSecondCounter_ >= static_cast<uint64_t>(qpcFrequency_.QuadPart))
			{
				framesPerSecond_ = framesThisSecond_;
				framesThisSecond_ = 0;
				qpcSecondCounter_ %= qpcFrequency_.QuadPart;
			}
		}
	};
}