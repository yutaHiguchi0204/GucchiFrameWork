/* =====================================================================
//! @param		�uCollisionManager�v�\�[�X
//! @create		��� �T��
//! @date		17/11/29
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "CollisionManager.h"
#include "../MapTip/MapTip.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�w�肵���ꏊ�̃}�b�v�`�b�v���`�F�b�N
// @param		�}�b�v�f�[�^�ivector<vector<int>>�j�A���݂̃`�b�vX�iint�j�A���݂̃`�b�vY�iint�j�A�`�F�b�N��������iCOLLISION�j
// @return		���ʁibool�j
===============================================================*/
bool CollisionManager::CheckCollisionMapTip(vector<vector<int>> data, int nowX, int nowY, COLLISION col)
{
	switch (col)
	{
		// ��
	case COLLISION::LEFT:
		// ��ʒ[�Ȃ瓖���������ƂƂ���
		if (nowX - 1 < 0)
		{
			return true;
		}

		// ��Q�����ǂ����`�F�b�N
		if (data[nowY][nowX - 1] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// �E
	case COLLISION::RIGHT:
		// ��ʒ[�Ȃ瓖���������ƂƂ���
		if (nowX + 1 >= (int)data[nowY].size())
		{
			return true;
		}

		// ��Q�����ǂ����`�F�b�N
		if (data[nowY][nowX + 1] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// ��
	case COLLISION::TOP:
		// ��ʒ[�Ȃ瓖���������ƂƂ���
		if (nowY - 1 < 0)
		{
			return true;
		}

		// ��Q�����ǂ����`�F�b�N
		if (data[nowY - 1][nowX] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// ��
	case COLLISION::BOTTOM:
		// ��ʒ[�Ȃ瓖���������ƂƂ���
		if (nowY + 1 >= (int)data.size())
		{
			return true;
		}

		// ��Q�����ǂ����`�F�b�N
		if (data[nowY + 1][nowX] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;
	}

	return false;
}