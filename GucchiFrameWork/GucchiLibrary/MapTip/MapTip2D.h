/* =====================================================================
//! @param		�uMapTip2D�v�w�b�_
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip.h"
#include "../2D/Sprite.h"

namespace GucchiLibrary
{
	/*
	// @class		MapTip2D �N���X
	// @content		�Q�c�p�}�b�v�`�b�v�N���X
	*/
	class MapTip2D : public MapTip
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;

	private:
		std::unique_ptr<Sprite>						dummySprite_;		// �e�p�_�~�[�X�v���C�g
		std::vector<std::vector<Sprite>>			sprite_;			// �X�v���C�g�f�[�^
		std::vector<std::shared_ptr<Sprite>>		masterSprite_;		// �X�v���C�g�i�[�p

	public:
		/*
		// @method		�R���X�g���N�^�i�e�N�X�`���P����ϓ��ɋ�`�������A�ǂݍ��ށj
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		�}�b�v�`�b�v�f�[�^�P�̃X�v���C�g�T�C�Y�iVector2�j
		// @param		�e�N�X�`�����i�����̋ϓ��Ƀe�N�X�`��������U���Ă���̂ɂ��Ă��������j�iwstring�j
		// @param		�f�[�^�̎�ސ��iint�j
		// @param		�`�b�v�̑����iTIP_TYPE[]�j
		*/
		MapTip2D(std::vector<std::vector<int>> data, const Vector2& spriteSize, std::wstring textureName, int typeNum, TipData::TIP_TYPE* type);

		/*
		// @method		�R���X�g���N�^�i�X�̃e�N�X�`����ǂݍ��ށj
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		�}�b�v�`�b�v�f�[�^�P�̃X�v���C�g�T�C�Y�iVector2�j
		// @param		�e�N�X�`���iwstring[]�j
		// @param		�f�[�^�̎�ސ��iint�j
		// @param		�`�b�v�̑����iTIP_TYPE[]�j
		*/
		MapTip2D(std::vector<std::vector<int>> data, const Vector2& spriteSize, std::wstring* textureName, int typeNum, TipData::TIP_TYPE* type);

		// �f�X�g���N�^
		virtual ~MapTip2D() = default;

		/*
		// @method		ResetData
		// @content		�}�b�v�`�b�v�f�[�^���Z�b�g
		*/
		void ResetData() override;

		/*
		// @method		ChangeTip�ipure�j
		// @content		�}�b�v�`�b�v�f�[�^�̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�V�f�[�^�iint�j
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/*
		// @method		SetSpritePos
		// @content		�w�肵���X�v���C�g�̈ʒu�ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�ʒu�iVector2�j
		*/
		void SetSpritePos(int noX, int noY, const Vector2& pos);

		/*
		// @method		SetSpriteScale
		// @content		�w�肵���X�v���C�g�̃X�P�[���ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�X�P�[���ifloat�j
		*/
		void SetSpriteScale(int noX, int noY, float scale);

		/*
		// @method		SetSpriteAngle
		// @content		�w�肵���X�v���C�g�̉�]�p�ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		��]�p�ifloat�j
		*/
		void SetSpriteAngle(int noX, int noY, float angle);

		/*
		// @method		SetSpriteActive
		// @content		�w�肵���X�v���C�g�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetSpriteActive(int noX, int noY, bool active);

		/*
		// @method		AddChild
		// @content		�}�b�v�`�b�v�Ƃ̐e�q�֌W�\�z
		// @param		�q�ɂ������X�v���C�g�iSprite*�j
		*/
		void AddChild(Sprite* sprite);

		/* �A�N�Z�b�T */

		void SetPos(const Vector2& pos)														{ dummySprite_->SetPos(pos); }

		inline const Vector2& GetPos() const												{ return dummySprite_->GetPos(); }
		inline int GetSpritesRowNum() const													{ return static_cast<int>(sprite_.size()); }
		inline int GetSpritesColumnNum(int row) const										{ return static_cast<int>(sprite_[row].size()); }
		inline const Vector2& GetSpritePos(int noX, int noY) const							{ return sprite_[noY][noX].GetPos(); }
		inline float GetSpriteScale(int noX, int noY) const									{ return sprite_[noY][noX].GetScale(); }
		inline float GetSpriteAngle(int noX, int noY) const									{ return sprite_[noY][noX].GetAngle(); }
		inline InterpolateDirector* GetSpriteInterpolateDirector(int noX, int noY) const	{ return sprite_[noY][noX].GetInterpolateDirector(); }
	};
}