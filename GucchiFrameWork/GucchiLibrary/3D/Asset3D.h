/* =====================================================================
//! @param		「Asset3D」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <Model.h>
#include <SimpleMath.h>
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	// クラスの定義
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
		// エフェクト
		std::shared_ptr<DirectX::BasicEffect>		basicEffect_;

		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	inputLayout_;

		// エフェクトファクトリ
		std::shared_ptr<DirectX::EffectFactory>		effectFactory_;

		// カメラ
		Camera* camera_;

	protected:
		DirectX::Model*								model_;						// モデル

		DirectX::SimpleMath::Vector3				scale_;						// スケール
		union {
			DirectX::SimpleMath::Vector3			rot_;						// 回転角
			DirectX::SimpleMath::Quaternion			quat_;						// クォータニオン
		};
		DirectX::SimpleMath::Vector3				trans_;						// 平行移動

		DirectX::SimpleMath::Matrix					world_;						// ワールド行列

		ID3D11BlendState*							blendStateSubtract_;		// 減算描画用ブレンドステート
		BLEND_MODE									blendMode_;					// ブレンドモード

		bool										isActive_;					// アクティブ状態

	public:
		Asset3D(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);
		virtual ~Asset3D() {};

		// 描画前の準備
		void DrawApply();

		// アクセッサ
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
		inline ID3D11BlendState* GetBlendStateSubtract() const					{ return blendStateSubtract_; }
		inline BLEND_MODE GetBlendMode() const									{ return blendMode_; }
		inline bool GetActive()	const											{ return isActive_; }

	public:
		// 比較用オペレータ
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