/* =====================================================================
//! @param		�uBenchMark�v�\�[�X
//! @create		��� �T��
//! @date		18/02/06
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "BenchMark.h"
#include <d3d11_1.h>
#include "../Common/Constant.h"
#include "../Common/DebugSwitch.h"

// ���O���
using namespace GucchiLibrary;

// �ÓI�����o�̒�`
LARGE_INTEGER	BenchMark::frequency_;
LARGE_INTEGER	BenchMark::begin_;
LARGE_INTEGER	BenchMark::end_;
bool			BenchMark::isTesting_ = false;

/*==============================================================
// @brief		�v���J�n
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void BenchMark::Begin()
{
	// ���g�����擾
	if (!QueryPerformanceFrequency(&frequency_))
	{
#if defined(MODE_DEBUG)
		OutputDebugString(L"Error: Sorry, I can't count.");
#endif

		// �v���s�\
		return;
	}

	// ���݂̎��ԁi�J�n���ԁj���擾
	if (!QueryPerformanceCounter(&begin_))
	{
#if defined(MODE_DEBUG)
		OutputDebugString(L"Error: Sorry, I can't count.");
#endif

		// �v���s�\
		return;
	}

	// �v���J�n
	isTesting_ = true;
}

/*==============================================================
// @brief		�v���I��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void BenchMark::End()
{
	// ���݂̎��ԁi�J�n���ԁj���擾
	if (!QueryPerformanceCounter(&end_))
	{
#if defined(MODE_DEBUG)
		OutputDebugString(L"Error: Sorry, I can't count.");
#endif

		// �v���s�\
		return;
	}

	// �v���I��
	isTesting_ = false;
}

/*==============================================================
// @brief		�v�����Ԃ̎擾
// @param		�Ȃ�
// @return		�v�����ԁidouble�j
===============================================================*/
double BenchMark::GetPerformanceTime()
{
	// �v����
	if (isTesting_)
	{
		return 0.0;
	}

	// ����\�P�ʂł̌v������
	LONGLONG time = end_.QuadPart - begin_.QuadPart;

	return static_cast<double>(time);
}

/*==============================================================
// @brief		�v�����Ԃ̎擾�i�b�j
// @param		�Ȃ�
// @return		�v�����ԁidouble�j
===============================================================*/
double BenchMark::GetPerformanceTimeOfSecond()
{
	// �v������
	double time = GetPerformanceTime();

	// �b�ɕϊ�
	return time / static_cast<double>(frequency_.QuadPart);
}

/*==============================================================
// @brief		�v�����Ԃ̎擾�i�t���[���j
// @param		�Ȃ�
// @return		�v�����ԁidouble�j
===============================================================*/
double BenchMark::GetPerformanceTimeOfFrame()
{
	// �v������
	double time = GetPerformanceTimeOfSecond();

	// �b�ɕϊ�
	return time * FRAME_PER_SECOND;
}