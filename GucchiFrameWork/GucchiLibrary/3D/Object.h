/* =====================================================================
//! @param		「Object」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Asset3D.h"
#include <Model.h>

namespace GucchiLibrary
{
	/*
	// @class		Object クラス
	// @content		3Dオブジェクト
	// @use			ObjectFactoryを使い生成する
	// @use			ObjectRendererに登録することで描画可能
	*/
	class Object : public Asset3D
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Quaternion = DirectX::SimpleMath::Quaternion;

	private:
		DirectX::Model*			model_;						// モデル

		Object*					parentObject_;				// 親オブジェクト
		std::vector<Object*>	childObject_;				// 子オブジェクト

	public:
		/*
		// @method		コンストラクタ
		// @param		平行移動（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		スケール（Vector3）　：　デフォルト（Vector3::One）
		// @param		回転角（Vector3）　：　デフォルト（Vector3::Zero）
		// @param		クォータニオン（Quaternion）　：　デフォルト（Quaternion::Identity）
		// @param		ブレンドモード（BLEND_MODE）　：　デフォルト（ALPHA）
		*/
		Object(const Vector3& trans = Vector3::Zero, const Vector3& scale = Vector3::One, const Vector3& rot = Vector3::Zero, const Quaternion& quat = Quaternion::Identity, BLEND_MODE mode = BLEND_MODE::ALPHA);

		// コピーコンストラクタ
		Object(const Object& object);
		
		// デストラクタ
		virtual ~Object() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update() override;

		/*
		// @method		SetParent
		// @content		親子関係構築（親設定）
		// @param		親オブジェクト（Object*）
		*/
		void SetParent(Object* object);

		/*
		// @method		AddChild
		// @content		親子関係構築（子設定）
		// @param		子オブジェクト（Object*）
		*/
		void AddChild(Object* object);

		/*
		// @method		GetBoundingBox
		// @content		オブジェクトのバウンディングボックスを取得
		// @return		バウンディングボックス（Vector3）
		*/
		Vector3 GetBoundingBox();

		/*
		// @method		GetBoundingSphere
		// @content		オブジェクトのバウンディングスフィアを取得
		// @return		バウンディングスフィア（float）
		*/
		float GetBoundingSphere();

		/* アクセッサ */

		void SetModel(DirectX::Model* model)			{ model_ = model; }

		inline DirectX::Model* GetModel() const			{ return model_; }
		inline Object* GetParent() const				{ return parentObject_; }
		inline std::vector<Object*> GetChildren() const { return childObject_; }

	public:
		// 代入オペレータ
		Object& operator=(const Object& object)
		{
			basicEffect_           = object.basicEffect_;
			inputLayout_           = object.inputLayout_;
			effectFactory_         = object.effectFactory_;
			camera_                = object.camera_;
			scale_                 = object.scale_;
			rot_                   = object.rot_;
			quat_                  = object.quat_;
			trans_                 = object.trans_;
			world_                 = object.world_;
			blendStateSubtractive_ = object.blendStateSubtractive_;
			blendMode_             = object.blendMode_;
			isUseQuaternion_       = object.isUseQuaternion_;
			model_                 = object.model_;
			parentObject_          = object.parentObject_;
			childObject_           = object.childObject_;

			return (*this);
		}

		// 比較用オペレータ
		bool operator==(const Object& object) const
		{
			return 
				scale_           == object.scale_				&& 
				rot_             == object.rot_					&& 
				quat_            == object.quat_				&& 
				trans_           == object.trans_				&& 
				world_           == object.world_				&& 
				blendMode_       == object.blendMode_			&& 
				isUseQuaternion_ == object.isUseQuaternion_		&& 
				model_           == object.model_				&& 
				parentObject_    == object.parentObject_;
		}
	};
}