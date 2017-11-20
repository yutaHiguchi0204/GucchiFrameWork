/* =====================================================================
//! @param		�uAsset3D�v�w�b�_
//! @create		��� �T��
//! @date		17/11/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <Model.h>
#include <SimpleMath.h>
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class Asset3D
	{
	public:
		enum class BLEND_MODE : int
		{
			ALPHA,
			ADDITIVE,
			SUBTRACTIVE,

			MODE_NUM
		};

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

		ID3D11BlendState*							blendStateSubtract_;		// ���Z�`��p�u�����h�X�e�[�g
		BLEND_MODE									blendMode_;					// �u�����h���[�h

		bool										isActive_;					// �A�N�e�B�u���

	public:
		Asset3D(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);
		virtual ~Asset3D() {};

		// �`��O�̏���
		void DrawApply();

		// �A�N�Z�b�T
		void SetCamera(Camera* camera)											{ camera_ = camera; }
		void SetModel(DirectX::Model* model)									{ model_ = model; }
		void SetScale(DirectX::SimpleMath::Vector3 scale)						{ scale_ = scale; }
		void SetRotate(DirectX::SimpleMath::Vector3 rot)						{ rot_ = rot; }
		void SetTranslate(DirectX::SimpleMath::Vector3 trans)					{ trans_ = trans; }
		void SetBlendMode(BLEND_MODE mode)										{ blendMode_ = mode; }
		void SetActive(bool active)												{ isActive_ = active; }

		inline DirectX::EffectFactory* GetEffectFactory() const					{ return effectFactory_.get(); }
		inline Camera* GetCamera() const										{ return camera_; }
		inline DirectX::Model* GetModel() const									{ return model_; }
		inline const DirectX::SimpleMath::Vector3& GetScale() const				{ return scale_; }
		inline const DirectX::SimpleMath::Vector3& GetRotate() const			{ return rot_; }
		inline const DirectX::SimpleMath::Quaternion& GetQuaternion() const		{ return quat_; }
		inline const DirectX::SimpleMath::Vector3& GetTranslate() const			{ return trans_; }
		inline const DirectX::SimpleMath::Matrix& GetWorld() const				{ return world_; }
		inline BLEND_MODE GetBlendMode() const									{ return blendMode_; }
		inline bool GetActive()	const											{ return isActive_; }

	public:
		// ��r�p�I�y���[�^
		bool operator==(const Asset3D& asset) const
		{
			if (model_			== asset.GetModel()			&&
				scale_			== asset.GetScale()			&&
				rot_			== asset.GetRotate()		&&
				quat_			== asset.GetQuaternion()	&&
				trans_			== asset.GetTranslate()		&&
				world_			== asset.GetWorld()			&&
				blendMode_		== asset.GetBlendMode()		&&
				isActive_		== asset.GetActive()
				)
			{
				return true;
			}

			return false;
		}
	};
}