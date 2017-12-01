/* =====================================================================
//! @param		�uMapTip�v�\�[�X
//! @create		��� �T��
//! @date		17/12/01
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
MapTip::MapTip(vector<vector<int>> data, int dataTypeNum, TipData::TIP_TYPE type[])
	: dataTypeNum_(dataTypeNum)
{
	// �����̕ۑ�
	for (int i = 0; i < dataTypeNum_; i++)
	{
		typeNum_.emplace_back(type[i]);
	}

	// �`�b�v�f�[�^�ɑ}��
	for (int i = 0; i < (int)data.size(); i++)
	{
		data_.emplace_back();

		int j = 0;
		for (auto& data : data[i])
		{
			data_[i].emplace_back();
			data_[i].at(j).SetData(data);
			data_[i].at(j).SetType(typeNum_.at(data));
			j++;
		}
	}
}