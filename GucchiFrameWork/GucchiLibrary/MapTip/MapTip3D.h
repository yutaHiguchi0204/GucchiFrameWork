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
		using Vector3 = DirectX::SimpleMath::Vector3;

	private:
		std::unique_ptr<Object>						dummyObject_;		// �e�p�_�~�[�I�u�W�F�N�g
		std::vector<std::vector<Object>>			object_;			// �I�u�W�F�N�g
		std::vector<std::shared_ptr<Object>>		masterObject_;		// �I�u�W�F�N�g�i�[�p

	public:
		/*
		// @method		�R���X�g���N�^�i�e�N�X�`���P����ϓ��ɋ�`�������A�ǂݍ��ށj
		// @param		�f�[�^�ivector<vector<int>>�j
		// @param		�}�b�v�`�b�v�f�[�^�P�̃I�u�W�F�N�g�T�C�Y�iVector3�j
		// @param		���f���t�@�C�����iwstring[]�j
		// @param		�f�[�^�̎�ސ��iint�j
		// @param		�`�b�v�̑����iTIP_TYPE[]�j
		*/
		MapTip3D(std::vector<std::vector<int>> data, const Vector3& tipSize, std::wstring* modelFileName, int typeNum, TipData::TIP_TYPE* type);

		// �f�X�g���N�^
		virtual ~MapTip3D() = default;

		/*
		// @method		ResetData
		// @content		�}�b�v�`�b�v�f�[�^���Z�b�g
		*/
		void ResetData() override;

		/*
		// @method		SetActive
		// @content		�}�b�v�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(bool active) override;

		/*
		// @method		ChangeTip
		// @content		�}�b�v�`�b�v�f�[�^�̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�V�f�[�^�iint�j
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/*
		// @method		SetObjectTranslate
		// @content		�w�肵���I�u�W�F�N�g�̕��s�ړ��ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		���s�ړ��iVector3�j
		*/
		void SetObjectTranslate(int noX, int noY, const Vector3& trans);

		/*
		// @method		SetObjectScale
		// @content		�w�肵���I�u�W�F�N�g�̃X�P�[���ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�X�P�[���iVector3�j
		*/
		void SetObjectScale(int noX, int noY, const Vector3& scale);

		/*
		// @method		SetObjectRotate
		// @content		�w�肵���I�u�W�F�N�g�̉�]�p�ݒ�
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		��]�p�iVector3�j
		*/
		void SetObjectRotate(int noX, int noY, const Vector3& rot);

		/*
		// @method		SetObjectActive
		// @content		�w�肵���I�u�W�F�N�g�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�ς������f�[�^�̔ԍ�x�iint�j
		// @param		�ς������f�[�^�̔ԍ�y�iint�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetObjectActive(int noX, int noY, bool active);

		/*
		// @method		AddChild
		// @content		�}�b�v�`�b�v�Ƃ̐e�q�֌W�\�z
		// @param		�q�ɂ������I�u�W�F�N�g�iObject*�j
		*/
		void AddChild(Object* object);

		/* �A�N�Z�b�T */

		void SetTranslate(const Vector3& trans)											{ dummyObject_->SetTranslate(trans); }

		inline const Vector3& GetTranslate() const										{ return dummyObject_->GetTranslate(); }
		inline int GetObjectsRowNum() const												{ return static_cast<int>(object_.size()); }
		inline int GetObjectsColumnNum(int row) const									{ return static_cast<int>(object_[row].size()); }
		inline const Vector3& GetObjectTranslate(int noX, int noY) const				{ return object_[noY][noX].GetTranslate(); }
		inline const Vector3& GetObjectScale(int noX, int noY) const					{ return object_[noY][noX].GetScale(); }
		inline const Vector3& GetObjectRotate(int noX, int noY) const					{ return object_[noY][noX].GetRotate(); }
		inline InterpolateDirector* GetObjectInterpolateState(int noX, int noY) const	{ return object_[noY][noX].GetInterpolateDirector(); }
	};
}