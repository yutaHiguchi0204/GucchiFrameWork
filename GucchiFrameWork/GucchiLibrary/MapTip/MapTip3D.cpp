/* =====================================================================
//! @param		�uMapTip3D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip3D.h"
#include <cassert>
#include "../3D/ObjectRenderer.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
MapTip3D::MapTip3D(vector<vector<int>> data, const Vector3& tipSize, wstring modelFileName[], int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No object type. Please configuration \"typeNum\".");
		assert(0);
	}

	// �_�~�[�I�u�W�F�N�g�ݒ�
	ObjectRenderer& renderer = ObjectRenderer::GetInstance();
	dummyObject_ = make_unique<Object>();
	renderer.RegisterObject(dummyObject_.get());

	// �I�u�W�F�N�g�ݒ�
	ObjectFactory& factory = ObjectFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// �I�u�W�F�N�g�����E�o�^
		masterObject_.emplace_back(factory.CreateObjectFromFile(modelFileName[i]));
	}

	// �I�u�W�F�N�g�f�[�^�ɔ��f
	for (int i = 0; i < (int)data_.size(); i++)
	{
		object_.emplace_back();

		for (auto& data : data_[i])
		{
			object_[i].emplace_back(*masterObject_[data.GetData()].get());
		}
	}

	// �I�u�W�F�N�g�̓o�^
	for (int i = 0; i < (int)object_.size(); i++)
	{
		int j = 0;
		for (auto& object : object_[i])
		{
			// �ʒu�̎w��
			object.SetTranslate(Vector3(tipSize.x * j, 0.f, tipSize.z * i));

			// �e�q�֌W�\�z
			object.SetParent(dummyObject_.get());

			j++;
		}
	}
}

/*==============================================================
// @brief		�R���e�i�f�[�^���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void MapTip3D::ResetData()
{
	object_.clear();
	for (auto& data : data_)
	{
		data.clear();
	}
	data_.clear();
	dummyObject_->SetTranslate(Vector3::Zero);
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::SetActive(int noX, int noY, bool active)
{
	object_.at(noY).at(noX).SetActive(active);
}

/*==============================================================
// @brief		�}�b�v�`�b�v�f�[�^�̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�V�f�[�^�iint�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::ChangeTip(int noX, int noY, int newData)
{
	data_.at(noY).at(noX).SetData(newData);

	// �V�����X�v���C�g�f�[�^�ɏ���������
	object_.at(noY).at(noX) = *masterObject_.at(data_.at(noY).at(noX).GetData()).get();
}