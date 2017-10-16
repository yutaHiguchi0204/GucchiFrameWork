/* =====================================================================
//! @param		�uStepTimer�v�\�[�X
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "StepTimer.h"

// ���O���
using namespace GucchiLibrary;

// �ÓI�����o�̒�`
const uint64_t StepTimer::TicksPerSecond = 10000000;

// �R���X�g���N�^
StepTimer::StepTimer()
	: elapsedTicks_(0)
	, totalTicks_(0)
	, leftOverTicks_(0)
	, frameCount_(0)
	, framesPerSecond_(0)
	, framesThisSecond_(0)
	, qpcSecondCounter_(0)
	, isFixedTimeStep_(false)
	, targetElapsedTicks_(TicksPerSecond / 60)
{
	if (!QueryPerformanceFrequency(&qpcFrequency_))
	{
		throw std::exception("QueryPerformanceFrequency");
	}

	if (!QueryPerformanceCounter(&qpcLastTime_))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	// �ő�f���^��1/10�b�ɏ�����
	qpcMaxDelta_ = qpcFrequency_.QuadPart / 10;
}

// �o�ߎ��ԃ��Z�b�g
void StepTimer::ResetElapsedTime()
{
	if (!QueryPerformanceCounter(&qpcLastTime_))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	leftOverTicks_ = 0;
	framesPerSecond_ = 0;
	framesThisSecond_ = 0;
	qpcSecondCounter_ = 0;
}