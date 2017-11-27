/* =====================================================================
//! @param		「Object」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Asset3D.h"

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
		Object* parentObject_;							// 親オブジェクト
		std::vector<Object*> childObject_;				// 子オブジェクト

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

		inline Object* GetParent() const { return parentObject_; }
		inline std::vector<Object*> GetChildren() const { return childObject_; }
	};
}