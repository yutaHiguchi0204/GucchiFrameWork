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
	// クラスの定義
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
		DefaultCamera(int width, int height);
		virtual ~DefaultCamera() {};

		// 更新処理
		virtual void Update() override;

		// カメラ回転モーション
		virtual void Motion(DirectX::SimpleMath::Vector2 mousePos);
	};
}