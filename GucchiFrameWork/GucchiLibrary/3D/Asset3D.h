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
	/*
	// @class		Asset3D クラス
	// @content		3Dリソース
	// @use			スプライトやモデルのテクスチャに使用
	// @use			TextureCacheによって管理される
	*/
	class Asset3D
	{
	public:
		/*
		// @content		ブレンドモード
		// @mode		ALPHA　：　アルファブレンド
		// @mode		ADDITIVE　：　加算ブレンド
		// @mode		SUBTRACTIVE　：　減算ブレンド
		*/
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
		bool										isUseQuaternion_;			// クォータニオンを使用するかどうか

	public:
		/*
		// @method		コンストラクタ
		// @param		平行移動（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		スケール（Vector3）　：　デフォルト（Vector3::One）
		// @param		回転角（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		クォータニオン（Quaternion）　：　デフォルト（Quaternion::Identity）
		// @param		ブレンドモード（BLEND_MODE）　：　デフォルト（ALPHA）
		*/
		Asset3D(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);

		// デストラクタ
		virtual ~Asset3D() {}

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update();

		/*
		// @method		DrawApply
		// @content		描画前設定
		*/
		void DrawApply();

		/* アクセッサ */

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

	public:
		// 比較用オペレータ
		bool operator==(const Asset3D& asset) const
		{
			if (model_				== asset.GetModel()				&&
				scale_				== asset.GetScale()				&&
				rot_				== asset.GetRotate()			&&
				quat_				== asset.GetQuaternion()		&&
				trans_				== asset.GetTranslate()			&&
				world_				== asset.GetWorld()				&&
				blendMode_			== asset.GetBlendMode()			&&
				isActive_			== asset.GetActive()			&&
				isUseQuaternion_	== asset.GetUseQuaternion()
				)
			{
				return true;
			}

			return false;
		}
	};
}