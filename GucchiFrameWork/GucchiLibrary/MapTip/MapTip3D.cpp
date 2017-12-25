/* =====================================================================
//! @param		�uMapTip3D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip3D.h"
#include <cassert>
#include "../3D/ObjectRenderer.h"
#include "../Common/DebugSwitch.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
MapTip3D::MapTip3D(vector<vector<int>> data, const Vector3& tipSize, wstring* modelFileName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
#if MODE_DEBUG == 1
		OutputDebugString(L"No object type. Please configuration \"typeNum\".");
#endif
		assert(0);
	}

	// �_�~�[�I�u�W�F�N�g�ݒ�
	ObjectRenderer& renderer = ObjectRenderer::GetInstance();
	dummyObject_ = make_unique<Object>();
	renderer.RegisterObject(dummyObject_.get());

	// �I�u�W�F�N�g�ݒ�
	ObjectFactory& factory = ObjectFactory::GetInstance();
	int typeNo = 0;
	for (int i = 0; i < static_cast<int>(TipData::TIP_TYPE::TYPE_NUM); i++)
	{
		if (i == static_cast<int>(type[typeNo]))
		{
			// �I�u�W�F�N�g�����E�o�^
			masterObject_.emplace_back(factory.CreateObjectFromFile(modelFileName[typeNo]));
			typeNo++;
		}
		else
		{
			masterObject_.emplace_back(nullptr);
		}
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

/*==============================================================
// @brief		�w�肵���I�u�W�F�N�g�̕��s�ړ��ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A���s�ړ��iVector3�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::SetObjectTranslate(int noX, int noY, const Vector3& trans)
{
	object_.at(noY).at(noX).SetTranslate(trans);
}

/*==============================================================
// @brief		�w�肵���I�u�W�F�N�g�̃X�P�[���ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�X�P�[���iVector3�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::SetObjectScale(int noX, int noY, const Vector3& scale)
{
	object_.at(noY).at(noX).SetScale(scale);
}

/*==============================================================
// @brief		�w�肵���I�u�W�F�N�g�̉�]�p�ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A��]�p�iVector3�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::SetObjectRotate(int noX, int noY, const Vector3& rot)
{
	object_.at(noY).at(noX).SetRotate(rot);
}

/*==============================================================
// @brief		�w�肵���I�u�W�F�N�g�̃A�N�e�B�u��Ԃ̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::SetObjectActive(int noX, int noY, bool active)
{
	object_.at(noY).at(noX).SetActive(active);
}

/*==============================================================
// @brief		�}�b�v�`�b�v�Ƃ̐e�q�֌W�\�z
// @param		�q�ɂ������I�u�W�F�N�g�iObject*�j
// @return		�Ȃ�
===============================================================*/
void MapTip3D::AddChild(Object* object)
{
	dummyObject_->AddChild(object);
}