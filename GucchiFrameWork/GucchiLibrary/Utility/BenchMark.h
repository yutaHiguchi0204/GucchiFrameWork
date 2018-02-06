/* =====================================================================
//! @param		�uBenchMark�v�w�b�_�i�x���`�}�[�N�e�X�g�p�j
//! @create		��� �T��
//! @date		18/02/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>

namespace GucchiLibrary
{
	/*
	// @class		BenchMark �N���X
	// @content		�x���`�}�[�N�e�X�g�N���X
	*/
	class BenchMark
	{
	private:
		static LARGE_INTEGER	frequency_;			// ������\�J�E���^�̎��g��
		static LARGE_INTEGER	begin_;				// �J�n����
		static LARGE_INTEGER	end_;				// �I������
		static bool				isTesting_;			// �e�X�g�����ǂ���

	public:
		/*
		// @method		Begin�istatic�j
		// @content		�v���J�n
		*/
		static void Begin();

		/*
		// @method		End�istatic�j
		// @content		�v���I��
		*/
		static void End();

		/*
		// @method		GetPerformanceTime�istatic�j
		// @content		�v�����Ԃ̎擾
		*/
		static double GetPerformanceTime();

		/*
		// @method		GetPerformanceTimeOfSecond�istatic�j
		// @content		�v�����Ԃ̎擾�i�b�j
		*/
		static double GetPerformanceTimeOfSecond();

		/*
		// @method		GetPerformanceTimeOfFrame�istatic�j
		// @content		�v�����Ԃ̎擾�i�t���[���j
		*/
		static double GetPerformanceTimeOfFrame();
	};
}