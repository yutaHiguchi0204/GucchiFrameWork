/* =====================================================================
//! @param		�uCSVFileManager�v�w�b�_�iCSV�t�@�C���Ǘ��j
//! @create		��� �T��
//! @date		17/11/29
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <memory>
#include <string>
#include <vector>

namespace GucchiLibrary
{
	/*
	// @class		CSVFileManager �N���X
	// @content		CSV�t�@�C���������N���X
	*/
	class CSVFileManager
	{
	public:
		static const std::wstring FILE_PATH_DATA;
		static const std::wstring EXT_CSV;

	public:
		/*
		// @method		LoadCSVFile�istatic�j
		// @content		CSV�t�@�C���ǂݍ���
		// @param		CSV�t�@�C�����iwstring�j
		// @return		�f�[�^�ivector<vector<int>>�j
		*/
		static std::vector<std::vector<int>> LoadCSVFile(const std::wstring csvFile);
	};
}