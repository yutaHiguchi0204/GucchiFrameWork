/* =====================================================================
//! @param		�uMapTip2D�v�\�[�X
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip2D.h"
#include <cassert>
#include "../2D/SpriteRenderer.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^�i�e�N�X�`���P����ϓ��ɋ�`�������A�ǂݍ��ށj
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring textureName, int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No sprite type. Please configuration \"typeNum\".");
		assert(0);
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
		RECT rect = RECT { (int)spriteSize.x * i, 0, (int)spriteSize.x * i + (int)spriteSize.x, (int)spriteSize.y };

		// �X�v���C�g�����E�o�^
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName, spriteSize, &rect));
	}

	// �X�v���C�g�f�[�^�ɔ��f
	for (int i = 0; i < (int)data_.size(); i++)
	{
		sprite_.emplace_back();

		for (auto& data : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[data.GetData()].get());
		}
	}

	// �X�v���C�g�����_���[�ɓo�^
	for (int i = 0; i < (int)sprite_.size(); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

// �R���X�g���N�^�i�X�̃e�N�X�`����ǂݍ��ށj
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring textureName[], int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No sprite type. Please configuration \"typeNum\".");
		assert(0);
	}

	// �X�v���C�g�ݒ�
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// �X�v���C�g�����E�o�^
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName[i], spriteSize));
	}

	// �X�v���C�g�f�[�^�ɔ��f
	for (int i = 0; i < (int)data_.size(); i++)
	{
		sprite_.emplace_back();

		for (auto& data : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[data.GetData()].get());
		}
	}

	// �X�v���C�g�����_���[�ɓo�^
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	for (int i = 0; i < (int)sprite_.size(); i++)
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
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::SetActive(int noX, int noY, bool active)
{
	sprite_.at(noY).at(noX).SetActive(active);
}

/*==============================================================
// @brief		�}�b�v�`�b�v�f�[�^�̕ύX
// @param		�ς������f�[�^�̔ԍ�x�iint�j�A�ς������f�[�^�̔ԍ�y�iint�j�A�V�f�[�^�iint�j
// @return		�Ȃ�
===============================================================*/
void MapTip2D::ChangeTip(int noX, int noY, int newData)
{
	data_.at(noY).at(noX).SetData(newData);

	// �V�����X�v���C�g�f�[�^�ɏ���������
	sprite_.at(noY).at(noX) = *masterSprite_.at(data_.at(noY).at(noX).GetData()).get();
}