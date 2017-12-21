/* =====================================================================
//! @param		�uAsset3D�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <Effects.h>
#include <Model.h>
#include "../Camera/Camera.h"
#include "../Utility/Interpolater.h"

namespace GucchiLibrary
{
	/*
	// @class		Asset3D �N���X
	// @content		3D���\�[�X
	// @use			�X�v���C�g�⃂�f���̃e�N�X�`���Ɏg�p
	// @use			TextureCache�ɂ���ĊǗ������
	*/
	class Asset3D
	{
	public:
		/*
		// @content		�u�����h���[�h
		// @mode		ALPHA		�F�@�A���t�@�u�����h
		// @mode		ADDITIVE	�F�@���Z�u�����h
		// @mode		SUBTRACTIVE	�F�@���Z�u�����h
		*/
		enum class BLEND_MODE : int
		{
			ALPHA,
			ADDITIVE,
			SUBTRACTIVE,

			MODE_NUM
		};

	protected:
		static ID3D11BlendState*					blendStateSubtract_;		// ���Z�`��p�u�����h�X�e�[�g

	protected:
		// �G�t�F�N�g
		std::shared_ptr<DirectX::BasicEffect>		basicEffect_;

		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	inputLayout_;

		// �G�t�F�N�g�t�@�N�g��
		std::shared_ptr<DirectX::EffectFactory>		effectFactory_;

		// �J����
		Camera* camera_;

	protected:
		DirectX::Model*								model_;						// ���f��

		DirectX::SimpleMath::Vector3				scale_;						// �X�P�[��
		union {
			DirectX::SimpleMath::Vector3			rot_;						// ��]�p
			DirectX::SimpleMath::Quaternion			quat_;						// �N�H�[�^�j�I��
		};
		DirectX::SimpleMath::Vector3				trans_;						// ���s�ړ�

		DirectX::SimpleMath::Matrix					world_;						// ���[���h�s��

		BLEND_MODE									blendMode_;					// �u�����h���[�h

		bool										isActive_;					// �A�N�e�B�u���
		bool										isUseQuaternion_;			// �N�H�[�^�j�I�����g�p���邩�ǂ���

		std::unique_ptr<InterpolateDirector>		interpolateDirector_;		// ��ԃX�e�[�g

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		���s�ړ��iVector3�j�@�F�@�f�t�H���g�iVector3::Zero�j
		// @param		�X�P�[���iVector3�j�@�F�@�f�t�H���g�iVector3::One�j
		// @param		��]�p�iVector3�j�@�F�@�f�t�H���g�iVector3::Zero�j
		// @param		�N�H�[�^�j�I���iQuaternion�j�@�F�@�f�t�H���g�iQuaternion::Identity�j
		// @param		�u�����h���[�h�iBLEND_MODE�j�@�F�@�f�t�H���g�iALPHA�j
		*/
		Asset3D(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);

		// �R�s�[�R���X�g���N�^
		Asset3D(const Asset3D& asset);

		// �f�X�g���N�^
		virtual ~Asset3D() {}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		virtual void Update();

		/*
		// @method		DrawApply
		// @content		�`��O�ݒ�
		*/
		void DrawApply();

		/* �A�N�Z�b�T */

		void SetCamera(Camera* camera)											{ camera_ = camera; }
		void SetModel(DirectX::Model* model)									{ model_ = model; }
		void SetScale(DirectX::SimpleMath::Vector3 scale)						{ scale_ = scale; }
		void SetRotate(DirectX::SimpleMath::Vector3 rot)						{ rot_ = rot; }
		void SetTranslate(DirectX::SimpleMath::Vector3 trans)					{ trans_ = trans; }
		void SetBlendMode(BLEND_MODE mode)										{ blendMode_ = mode; }
		void SetActive(bool active)												{ isActive_ = active; }
		void SetUseQuaternion(bool use)											{ isUseQuaternion_ = use; }

		inline DirectX::EffectFactory* GetEffectFactory() const					{ return effectFactory_.get(); }
		inline Camera* GetCamera() const										{ return camera_; }
		inline DirectX::Model* GetModel() const									{ return model_; }
		inline const DirectX::SimpleMath::Vector3& GetScale() const				{ return scale_; }
		inline const DirectX::SimpleMath::Vector3& GetRotate() const			{ return rot_; }
		inline const DirectX::SimpleMath::Quaternion& GetQuaternion() const		{ return quat_; }
		inline const DirectX::SimpleMath::Vector3& GetTranslate() const			{ return trans_; }
		inline const DirectX::SimpleMath::Matrix& GetWorld() const				{ return world_; }
		inline ID3D11BlendState* GetBlendStateSubtract() const					{ return blendStateSubtract_; }
		inline BLEND_MODE GetBlendMode() const									{ return blendMode_; }
		inline bool GetActive()	const											{ return isActive_; }
		inline bool GetUseQuaternion() const									{ return isUseQuaternion_; }
		inline InterpolateDirector* GetInterpolateDirector() const				{ return interpolateDirector_.get(); }

	public:
		// ����I�y���[�^
		Asset3D& operator=(const Asset3D& asset)
		{
			basicEffect_        = asset.basicEffect_;
			inputLayout_        = asset.inputLayout_;
			effectFactory_      = asset.effectFactory_;
			camera_             = asset.camera_;
			model_              = asset.model_;
			scale_              = asset.scale_;
			rot_                = asset.rot_;
			quat_               = asset.quat_;
			trans_              = asset.trans_;
			world_              = asset.world_;
			blendStateSubtract_ = asset.blendStateSubtract_;
			blendMode_          = asset.blendMode_;
			isActive_           = asset.isActive_;
			isUseQuaternion_    = asset.isUseQuaternion_;

			return (*this);
		}

		// ��r�p�I�y���[�^
		bool operator==(const Asset3D& asset) const
		{
			if (model_				== asset.model_				&&
				scale_				== asset.scale_				&&
				rot_				== asset.rot_				&&
				quat_				== asset.quat_				&&
				trans_				== asset.trans_				&&
				world_				== asset.world_				&&
				blendMode_			== asset.blendMode_			&&
				isActive_			== asset.isActive_			&&
				isUseQuaternion_	== asset.isUseQuaternion_
				)
			{
				return true;
			}

			return false;
		}
	};
}