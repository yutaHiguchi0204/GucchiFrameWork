/* =====================================================================
//! @param		�uMapTip2D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip2D.h"
#include <cassert>
#include "../2D/SpriteRenderer.h"
#include "../System/DebugSystem.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^�i�e�N�X�`���P����ϓ��ɋ�`�������A�ǂݍ��ށj
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, const wstring& textureName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
		DebugSystem::DebugLog(L"No sprite type. Please configuration \"typeNum\".", true);
		assert(false);
	}

	// �_�~�[�X�v���C�g�ݒ�
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	dummySprite_ = make_unique<Sprite>(Vector2::Zero);
	renderer.RegisterSprite(dummySprite_.get());

	// �X�v���C�g�ݒ�
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// �e�N�X�`���̋�`�ݒ�
		RECT rect = RECT { static_cast<int>(spriteSize.x) * i, 0, static_cast<int>(spriteSize.x) * i + static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y) };

		// �X�v���C�g�����E�o�^
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName, spriteSize, &rect));
	}

	// �X�v���C�g�f�[�^�ɔ��f
	for (int i = 0; i < static_cast<int>(data_.size()); i++)
	{
		sprite_.emplace_back();

		for (auto& tip : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[tip.GetData()].get());
		}
	}

	// �X�v���C�g�����_���[�ɓo�^
	for (int i = 0; i < static_cast<int>(sprite_.size()); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

// �R���X�g���N�^�i�X�̃e�N�X�`����ǂݍ��ށj
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring* textureName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
		DebugSystem::DebugLog(L"No sprite type. Please configuration \"typeNum\".", true);
		assert(false);
	}

	// �X�v���C�g�ݒ�
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// �X�v���C�g�����E�o�^
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName[i], spriteSize));
	}

	// �X�v���C�g�f�[�^�ɔ��f
	for (int i = 0; i < static_cast<int>(data_.size()); i++)
	{
		sprite_.emplace_back();

		for (auto& tip : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[tip.GetData()].get());
		}
	}

	// �X�v���C�g�����_���[�ɓo�^
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	for (int i = 0; i < static_cast<int>(sprite_.size()); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

/*==============================================================
// @brief		�R���e�i�f�[�^���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void MapTip2D::ResetData()
{
	sprite_.clear();
	for (auto& data : data_)
	{
		data.clear();
	}
	data_.clear();
	dummySprite_->SetPos(Vector2::Zero);
}

/*==============================================================
// @brief		�}�b�v�`�b�v�f�[�^�̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�V�f�[�^�iint�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::ChangeTip(int noX, int noY, int newData)
{
	data_[noY][noX].SetData(newData);

	// �V�����X�v���C�g�f�[�^�ɏ���������
	sprite_[noY][noX] = *masterSprite_[data_[noY][noX].GetData()].get();
}

/*==============================================================
// @brief		�}�b�v�̃A�N�e�B�u��Ԃ̕ύX
// @param		�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetActive(bool active)
{
	dummySprite_->SetActive(active);
}

/*==============================================================
// @brief		�w�肵���X�v���C�g�̈ʒu�ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�ʒu�iVector2�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetSpritePos(int noX, int noY, const Vector2& pos)
{
	sprite_[noY][noX].SetPos(pos);
}

/*==============================================================
// @brief		�w�肵���X�v���C�g�̃X�P�[���ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�X�P�[���ifloat�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetSpriteScale(int noX, int noY, float scale)
{
	sprite_[noY][noX].SetScale(scale);
}

/*==============================================================
// @brief		�w�肵���X�v���C�g�̉�]�p�ݒ�
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A��]�p�ifloat�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetSpriteAngle(int noX, int noY, float angle)
{
	sprite_[noY][noX].SetAngle(angle);
}

/*==============================================================
// @brief		�w�肵���X�v���C�g�̃A�N�e�B�u��Ԃ̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetSpriteActive(int noX, int noY, bool active)
{
	sprite_[noY][noX].SetActive(active);
}

/*==============================================================
// @brief		�}�b�v�`�b�v�Ƃ̐e�q�֌W�\�z
// @param		�q�ɂ������X�v���C�g�iSprite*�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::AddChild(Sprite* sprite)
{
	dummySprite_->AddChild(sprite);
}