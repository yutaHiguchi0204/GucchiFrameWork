/* =====================================================================
//! @param		�uBinaryFileManager�v�\�[�X�i�o�C�i���t�@�C���Ǘ��j
//! @create		��� �T��
//! @date		17/11/27
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "BinaryFileManager.h"
#include <cassert>
#include <fstream>
#include "../System/DebugSystem.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
BinaryFile::BinaryFile()
	: size_(0)
{
}

// ���[�u�R���X�g���N�^
BinaryFile::BinaryFile(BinaryFile&& _in)
{
	data_ = std::move(_in.data_);
	size_ = _in.size_;
}

/*==============================================================
// @brief		�o�C�i���f�[�^�̃��Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void BinaryFile::ResetData()
{
	data_.reset(new char[size_]);
}

/*==============================================================
// @brief		�o�C�i���t�@�C���̓ǂݍ��݁i�S�́j
// @param		�t�@�C�����iwstring�j
// @return		�o�C�i���t�@�C���iBinaryFile�j
===============================================================*/
BinaryFile BinaryFileManager::LoadBinaryFile(const wstring fileName)
{
	BinaryFile bin;

	// �t�@�C���ǂݍ��ݏ���
	ifstream ifs;

	// �t�@�C�����J��
	ifs.open(fileName.c_str(), ios::in | ios::binary);

	// �G���[����
	if (!ifs)
	{
		DebugSystem::DebugLog(L"BinaryFile opening failed.", true);
		assert(ifs);
	}

	// �t�@�C���T�C�Y���擾
	ifs.seekg(0, fstream::end);
	streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, fstream::beg);
	streamoff begPos = ifs.tellg();
	bin.SetSize(static_cast<unsigned int>(eofPos - begPos));

	// �������m��
	bin.ResetData();

	// �t�@�C���̐擪����o�b�t�@�փf�[�^���R�s�[
	ifs.read(bin.GetData(), bin.GetSize());

	// �t�@�C�������
	ifs.close();

	return move(bin);
}

/*==============================================================
// @brief		�o�C�i���t�@�C���̓ǂݍ��݁i�ꕔ���j
// @param		�t�@�C�����iwstring�j
// @return		�o�C�i���t�@�C���iBinaryFile�j
===============================================================*/
BinaryFile BinaryFileManager::LoadBinaryFile(const wstring fileName, int part)
{
	BinaryFile bin;

	// �t�@�C���ǂݍ��ݏ���
	ifstream ifs;

	// �t�@�C�����J��
	ifs.open(fileName.c_str(), ios::in | ios::binary);

	// �G���[����
	if (!ifs)
	{
		DebugSystem::DebugLog(L"BinaryFile opening failed.", true);
		assert(ifs);
	}

	// �t�@�C���T�C�Y���擾
	ifs.seekg(part * sizeof(unsigned int));
	bin.SetSize(sizeof(unsigned int));

	// �������m��
	bin.ResetData();

	// �t�@�C���̐擪����o�b�t�@�փf�[�^���R�s�[
	ifs.read(bin.GetData(), bin.GetSize());

	// �t�@�C�������
	ifs.close();

	return move(bin);
}

/*==============================================================
// @brief		�o�C�i���t�@�C���̏�����
// @param		�t�@�C�����iwstring�j�A�o�C�i���f�[�^�iBinaryFile�j
// @return		�Ȃ�
===============================================================*/
void BinaryFileManager::SaveBinaryFile(const wstring fileName, const BinaryFile& data)
{
	// �t�@�C���ǂݍ��ݏ���
	ifstream ifs;

	// �t�@�C�����J��
	ifs.open(fileName.c_str(), ios::out | ios::binary | ios::trunc);

	// �G���[����
	if (!ifs)
	{
		DebugSystem::DebugLog(L"BinaryFile opening failed.", true);
		assert(ifs);
	}
}