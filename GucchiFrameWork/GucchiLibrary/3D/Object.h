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
		Object(const DirectX::SimpleMath::Vector3& trans = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One, const DirectX::SimpleMath::Vector3& rot = DirectX::SimpleMath::Vector3::Zero, const DirectX::SimpleMath::Quaternion& quat = DirectX::SimpleMath::Quaternion::Identity, Asset3D::BLEND_MODE mode = Asset3D::BLEND_MODE::ALPHA);

		// コピーコンストラクタ
		Object(const Object& object);

		// デストラクタ
		virtual ~Object() {}

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

		/* アクセッサ */

		void SetModel(DirectX::Model* model) { model_ = model; }

		inline DirectX::Model* GetModel() const { return model_; }
		inline Object* GetParent() const { return parentObject_; }
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
			isActive_              = object.isActive_;
			isUseQuaternion_       = object.isUseQuaternion_;
			model_                 = object.model_;
			parentObject_          = object.parentObject_;
			childObject_           = object.childObject_;

			return (*this);
		}

		// 比較用オペレータ
		bool operator==(const Object& object) const
		{
			if (scale_           == object.scale_				&&
				rot_             == object.rot_					&&
				quat_            == object.quat_				&&
				trans_           == object.trans_				&&
				world_           == object.world_				&&
				blendMode_       == object.blendMode_			&&
				isActive_        == object.isActive_			&&
				isUseQuaternion_ == object.isUseQuaternion_		&&
				model_           == object.model_				&&
				parentObject_    == object.parentObject_
				)
			{
				return true;
			}

			return false;
		}
	};
}