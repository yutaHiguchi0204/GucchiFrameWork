/* =====================================================================
//! @param		�uMapTip3D�v�w�b�_
//! @create		��� �T��
//! @date		17/11/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "MapTip.h"
#include <string>
#include <vector>
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		MapTip3D �N���X
	// @content		�R�c�p�}�b�v�`�b�v�N���X
	*/
	class MapTip3D : public MapTip
	{
	private:
		std::unique_ptr<Object>						dummyObject_;		// �e�p�_�~�[�I�u�W�F�N�g
		std::vector<std::vector<Object>>			object_;			// �I�u�W�F�N�g
		std::vector<std::shared_ptr<Object>>		masterObject_;		// �I�u�W�F�N�g�i�[�p

	public:
		/*
		// @method		�R���X�g���N�^�i�e�N�X�`���P����ϓ��ɋ�`�������A�ǂݍ��ށj
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		���f���t�@�C�����iwstring�j
		// @param		�f�[�^�̎�ސ��iint�j
		*/
		MapTip3D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector3& tipSize, std::wstring modelFileName[], int typeNum, TipData::TIP_TYPE type[]);

		// �f�X�g���N�^
		virtual ~MapTip3D() {}

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

		void SetTranslate(const DirectX::SimpleMath::Vector3& trans) { dummyObject_->SetTranslate(trans); }
	};
}