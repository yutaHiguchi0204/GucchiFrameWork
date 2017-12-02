/* =====================================================================
//! @param		�uCSVFileManager�v�\�[�X�iCSV�t�@�C���Ǘ��j
//! @create		��� �T��
//! @date		17/11/29
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "CSVFileManager.h"
#include <cassert>
#include <d3d11_1.h>
#include <fstream>
#include <sstream>

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const wstring CSVFileManager::FILE_PATH_DATA = L"Resources/Data/";
const wstring CSVFileManager::EXT_CSV = L".csv";

// �����o�֐��̒�`

/*==============================================================
// @brief		CSV�t�@�C���ǂݍ���
// @param		CSV�t�@�C�����iwstring�j
// @return		�f�[�^�ivector<vector<int>>�j
===============================================================*/
vector<vector<int>> CSVFileManager::LoadCSVFile(const wstring csvFile)
{
	// �t�@�C���ǂݍ���
	wstring fileName = FILE_PATH_DATA + csvFile + EXT_CSV;
	ifstream ifs(fileName);

	// �G���[����
	if (!ifs)
	{
		OutputDebugString(L"CSV file load failed.");
		assert(ifs);
	}

	// �f�[�^�����R�[�h���ƂɎ擾
	vector<vector<int>> data;
	string tmp;
	int i = 0;
	while (getline(ifs, tmp))
	{
		string token;
		istringstream stream(tmp);

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