/* =====================================================================
//! @param		「DefaultCamera」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Camera.h"
#include "../InputTools/MouseUtil.h"

namespace GucchiLibrary
{
	/*
	// @class		DefaultCamera クラス
	// @content		カメラ
	// @use			グローバル座標系の描画に使用
	// @use			ホイール操作で画面の拡縮、ドラッグ操作でカメラの回転を行う
	*/
	class DefaultCamera : public Camera
	{
	protected:
		static const float DEFAULT_DISTANCE;

	protected:
		MouseUtil& mouse_ = MouseUtil::GetInstance();		// マウス情報

		DirectX::SimpleMath::Vector2 angle_;				// 回転角情報
		DirectX::SimpleMath::Vector2 tmpAngle_;				// 回転角保存用

		DirectX::SimpleMath::Vector2 dragStartPos_;			// マウスドラッグの開始地点
		DirectX::SimpleMath::Vector2 relScale_;				// 相対スケール

		int wheelValue_;									// 拡大率

	public:
		/*
		// @method		コンストラクタ
		// @param		画面の幅（int）
		// @param		画面の高さ（int）
		*/
		DefaultCamera(int width, int height);

		// デストラクタ
		virtual ~DefaultCamera() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update() override;

		/*
		// @method		Motion
		// @content		ドラッグによる回転モーション
		// @param		マウスの座標（Vector2）
		*/
		virtual void Motion(DirectX::SimpleMath::Vector2 mousePos);
	};
}