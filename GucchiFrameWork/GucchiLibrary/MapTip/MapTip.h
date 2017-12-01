/* =====================================================================
//! @param		�uMapTipManager�v�w�b�_
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/SingletonDirector.h"
#include <vector>

namespace GucchiLibrary
{
	/*
	// @class		TipData �N���X
	// @content		�`�b�v�f�[�^�N���X
	*/
	class TipData
	{
	public:
		/*
		// @content		�`�b�v�̑���
		// @mode		NONE	�F�@���ɉ����Ȃ�
		// @mode		SOLID	�F�@�u���b�N
		// @mode		DAMAGE	�F�@�_���[�W�`�b�v
		*/
		enum class TIP_TYPE
		{
			NONE,
			SOLID,
			DAMAGE,

			TYPE_NUM
		};

	private:
		int			data_;		// �f�[�^
		TIP_TYPE	type_;		// �`�b�v����

	public:
		// �R���X�g���N�^
		TipData() {}

		// �f�X�g���N�^
		virtual ~TipData() {}

		/* �A�N�Z�b�T */

		void SetData(int data)		{ data_ = data; }
		void SetType(TIP_TYPE type) { type_ = type; }

		inline int GetData() const		{ return data_; }
		inline TIP_TYPE GetType() const { return type_; }
	};

	/*
	// @class		MapTip �N���X
	// @content		�}�b�v�`�b�v�N���X
	*/
	class MapTip
	{
	protected:
		std::vector<std::vector<TipData>>	data_;				// �f�[�^
		std::vector<TipData::TIP_TYPE>		typeNum_;			// �`�b�v�̑���
		int									dataTypeNum_;		// �f�[�^�̎�ސ�

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		�f�[�^�̎�ސ��iint�j
		// @param		�`�b�v�̑����iTIP_TYPE�j
		*/
		MapTip(std::vector<std::vector<int>> data, int dataTypeNum, TipData::TIP_TYPE type[]);

		// �f�X�g���N�^
		virtual ~MapTip() {}

		/*
		// @method		ResetData
		// @content		�}�b�v�`�b�v�f�[�^���Z�b�g
		*/
		virtual void ResetData() = 0;

		/*
		// @method		SetActive
		// @content		�A�N�e�B�u��Ԃ̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		virtual void SetActive(int noX, int noY, bool active) = 0;

		/*
		// @method		ChangeTip�ipure�j
		// @content		�}�b�v�`�b�v�f�[�^�̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�V�f�[�^�iint�j
		*/
		virtual void ChangeTip(int noX, int noY, int newData) = 0;
	};
}