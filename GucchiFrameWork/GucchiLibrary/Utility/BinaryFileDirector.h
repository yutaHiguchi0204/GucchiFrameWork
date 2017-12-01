/* =====================================================================
//! @param		�uBinaryFileDirector�v�w�b�_�i�o�C�i���t�@�C���Ǘ��j
//! @create		��� �T��
//! @date		17/11/27
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <memory>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		BinaryFile �N���X
	// @content		�o�C�i���t�@�C��
	*/
	class BinaryFile
	{
	private:
		std::unique_ptr<char[]> data_;		// �o�C�i���t�@�C������擾�����f�[�^
		unsigned int size_;					// �f�[�^�T�C�Y

	public:
		BinaryFile();						// �f�t�H���g�R���X�g���N�^
		BinaryFile(BinaryFile&& _in);		// ���[�u�R���X�g���N�^
		virtual ~BinaryFile() {}

		/*
		// @method		ResetData
		// @content		�o�C�i���f�[�^�̃��Z�b�g
		*/
		void ResetData();

		/* �A�N�Z�b�T */

		void SetSize(unsigned int size)			{ size_ = size; }

		inline char* GetData() const			{ return data_.get(); }
		inline unsigned int GetSize() const		{ return size_; }
	};

	/*
	// @class		BinaryFileDirector �N���X
	// @content		�o�C�i���t�@�C���������N���X
	*/
	class BinaryFileDirector
	{
	public:
		/*
		// @method		LoadBinaryFile�istatic�j
		// @content		�o�C�i���t�@�C���̓ǂݍ��݁i�S�́j
		// @param		�t�@�C�����iwstring�j
		// @return		�o�C�i���t�@�C���iBinaryFile�j
		*/
		static BinaryFile LoadBinaryFile(const std::wstring fileName);

		/*
		// @method		LoadBinaryFile�istatic�j
		// @content		�o�C�i���t�@�C���̓ǂݍ��݁i�ꕔ���j
		// @param		�t�@�C�����iwstring�j
		// @return		�o�C�i���t�@�C���iBinaryFile�j
		*/
		static BinaryFile LoadBinaryFile(const std::wstring fileName, int part);

		/*
		// @method		SaveBinaryFile�istatic�j
		// @content		�o�C�i���t�@�C���̏�����
		// @param		�t�@�C�����iwstring�j
		// @param		�o�C�i���f�[�^�iBinaryFile�j
		*/
		static void SaveBinaryFile(const std::wstring fileName, const BinaryFile& data);
	};
}