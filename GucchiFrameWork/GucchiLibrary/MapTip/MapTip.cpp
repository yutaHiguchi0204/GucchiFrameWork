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
MapTip::MapTip(vector<vector<int>> data, int dataTypeNum)
	: dataTypeNum_(dataTypeNum)
{
	// �`�b�v�f�[�^�ɑ}��
	for (int i = 0; i < (int)data.size(); i++)
	{
		data_.emplace_back();

		int j = 0;
		for (auto& data : data[i])
		{
			data_[i].emplace_back();
			data_[i].at(j).SetData(data);
			data_[i].at(j).SetType(static_cast<TipData::TIP_TYPE>(data));
			j++;
		}
	}
}