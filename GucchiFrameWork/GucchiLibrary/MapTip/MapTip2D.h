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
		*/
		MapTip2D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector2& spriteSize, std::wstring textureName, int typeNum, TipData::TIP_TYPE type[]);

		/*
		// @method		�R���X�g���N�^�i�X�̃e�N�X�`����ǂݍ��ށj
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		�}�b�v�`�b�v�f�[�^�P�̃X�v���C�g�T�C�Y�iVector2�j
		// @param		�e�N�X�`���iwstring[]�j
		// @param		�f�[�^�̎�ސ��iint�j
		*/
		MapTip2D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector2& spriteSize, std::wstring textureName[], int typeNum, TipData::TIP_TYPE type[]);

		// �f�X�g���N�^
		virtual ~MapTip2D() {}

		/*
		// @method		ResetData
		// @content		�}�b�v�`�b�v�f�[�^���Z�b�g
		*/
		void ResetData() override;

		/*
		// @method		SetActive
		// @content		�A�N�e�B�u��Ԃ̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(int noX, int noY, bool active) override;

		/*
		// @method		ChangeTip�ipure�j
		// @content		�}�b�v�`�b�v�f�[�^�̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�V�f�[�^�iint�j
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/* �A�N�Z�b�T */

		void SetPos(const DirectX::SimpleMath::Vector2& pos) { dummySprite_->SetPos(pos); }
	};
}