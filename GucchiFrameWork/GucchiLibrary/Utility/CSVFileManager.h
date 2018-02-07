/* =====================================================================
//! @param		�uCSVFileManager�v�w�b�_�iCSV�t�@�C���Ǘ��j
//! @create		��� �T��
//! @date		17/11/29
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <cassert>
#include <d3d11_1.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../Common/DebugSwitch.h"
#include "../System/DebugSystem.h"

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
		static std::vector<std::vector<int>> LoadCSVFile(const std::wstring csvFile)
		{
			// �t�@�C���ǂݍ���
			std::wstring fileName = FILE_PATH_DATA + csvFile + EXT_CSV;
			std::ifstream ifs(fileName);

			// �G���[����
			if (!ifs)
			{
				DebugSystem::DebugLog(L"CSV file load failed.");
				assert(ifs);
			}

			// �f�[�^�����R�[�h���ƂɎ擾
			std::vector<std::vector<int>> data;
			std::string tmp;
			int i = 0;
			while (getline(ifs, tmp))
			{
				std::string token;
				std::istringstream stream(tmp);

				// �s�z��̐���
				data.emplace_back();

				// �J���}��؂�Ńf�[�^���擾
				while (getline(stream, token, ','))
				{
					// �f�[�^��}��
					data[i].emplace_back(stoi(token));
				}

				i++;
			}

			// �t�@�C�������
			ifs.close();

			return data;
		}
	};

	// �ÓI�����o�̒�`
	__declspec(selectany) const std::wstring CSVFileManager::FILE_PATH_DATA(L"Resources/Data/");
	__declspec(selectany) const std::wstring CSVFileManager::EXT_CSV(L".csv");
}