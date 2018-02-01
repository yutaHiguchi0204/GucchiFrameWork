/* =====================================================================
//! @param		「Asset3D」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <Effects.h>
#include <memory>
#include <wrl/client.h>
#include "../Camera/Camera.h"
#include "../Utility/Interpolater.h"

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
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;
		using Quaternion = DirectX::SimpleMath::Quaternion;

	public:
		/*
		// @content		ブレンドモード
		// @mode		ALPHA		：　アルファブレンド
		// @mode		ADDITIVE	：　加算ブレンド
		// @mode		SUBTRACTIVE	：　減算ブレンド
		*/
		enum class BLEND_MODE : int
		{
			ALPHA,
			ADDITIVE,
			SUBTRACTIVE,

			MODE_NUM
		};

	protected:
		static ID3D11BlendState*					blendStateSubtractive_;		// 減算描画用ブレンドステート

	public:
		/*
		// @method		SetBlendState（static）
		// @content		ブレンドモード設定
		// @param		ブレンドモード（BLEND_MODE）
		*/
		static void SetBlendState(BLEND_MODE mode);

		/*
		// @method		SetSubtractive（static）
		// @content		減算描画設定
		// @return		減算描画用ブレンドステート（ID3D11BlendState*）
		*/
		static ID3D11BlendState* SetSubtractive();

		/* アクセッサ */

		static ID3D11BlendState* GetBlendStateSubtract() { return blendStateSubtractive_; }

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
		Vector3										scale_;						// スケール
		union {
			Vector3									rot_;						// 回転角
			Quaternion								quat_;						// クォータニオン
		};
		Vector3										trans_;						// 平行移動

		Matrix										world_;						// ワールド行列

		BLEND_MODE									blendMode_;					// ブレンドモード

		bool										isActive_;					// アクティブ状態
		bool										isUseQuaternion_;			// クォータニオンを使用するかどうか

		std::unique_ptr<InterpolateDirector>		interpolateDirector_;		// 補間ステート

	public:
		/*
		// @method		コンストラクタ
		// @param		平行移動（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		スケール（Vector3）　：　デフォルト（Vector3::One）
		// @param		回転角（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		クォータニオン（Quaternion）　：　デフォルト（Quaternion::Identity）
		// @param		ブレンドモード（BLEND_MODE）　：　デフォルト（ALPHA）
		*/
		Asset3D(const Vector3& trans = Vector3::Zero, const Vector3& scale = Vector3::One, const Vector3& rot = Vector3::Zero, const Quaternion& quat = Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);

		// コピーコンストラクタ
		Asset3D(const Asset3D& asset);

		// デストラクタ
		virtual ~Asset3D() = default;

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

		void SetCamera(Camera* camera)									{ camera_ = camera; }
		void SetScale(const Vector3& scale)								{ scale_ = scale; }
		void SetRotate(const Vector3& rot)								{ rot_ = rot; }
		void SetTranslate(const Vector3& trans)							{ trans_ = trans; }
		void SetBlendMode(BLEND_MODE mode)								{ blendMode_ = mode; }
		void SetActive(bool active)										{ isActive_ = active; }
		void SetUseQuaternion(bool use)									{ isUseQuaternion_ = use; }

		inline DirectX::EffectFactory* GetEffectFactory() const			{ return effectFactory_.get(); }
		inline Camera* GetCamera() const								{ return camera_; }
		inline const Vector3& GetScale() const							{ return scale_; }
		inline const Vector3& GetRotate() const							{ return rot_; }
		inline const Quaternion& GetQuaternion() const					{ return quat_; }
		inline const Vector3& GetTranslate() const						{ return trans_; }
		inline const Matrix& GetWorld() const							{ return world_; }
		inline BLEND_MODE GetBlendMode() const							{ return blendMode_; }
		inline bool GetActive()	const									{ return isActive_; }
		inline bool GetUseQuaternion() const							{ return isUseQuaternion_; }
		inline InterpolateDirector* GetInterpolateDirector() const		{ return interpolateDirector_.get(); }

	public:
		// 代入オペレータ
		Asset3D& operator=(const Asset3D& asset)
		{
			basicEffect_           = asset.basicEffect_;
			inputLayout_           = asset.inputLayout_;
			effectFactory_         = asset.effectFactory_;
			camera_                = asset.camera_;
			scale_                 = asset.scale_;
			rot_                   = asset.rot_;
			quat_                  = asset.quat_;
			trans_                 = asset.trans_;
			world_                 = asset.world_;
			blendStateSubtractive_ = asset.blendStateSubtractive_;
			blendMode_             = asset.blendMode_;
			isActive_              = asset.isActive_;
			isUseQuaternion_       = asset.isUseQuaternion_;

			return (*this);
		}

		// 比較用オペレータ
		bool operator==(const Asset3D& asset) const
		{
			return 
				scale_				== asset.scale_				&& 
				rot_				== asset.rot_				&& 
				quat_				== asset.quat_				&& 
				trans_				== asset.trans_				&& 
				world_				== asset.world_				&& 
				blendMode_			== asset.blendMode_			&& 
				isActive_			== asset.isActive_			&& 
				isUseQuaternion_	== asset.isUseQuaternion_;
		}
	};
}