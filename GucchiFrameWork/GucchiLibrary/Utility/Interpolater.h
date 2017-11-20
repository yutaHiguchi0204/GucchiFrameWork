/* =====================================================================
//! @param		「Interpolater」ヘッダ（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	// クラスの定義
	class Interpolater : public SingletonDirector<Interpolater>
	{
	private:
		float startTime_;
		float nowTime_;
		bool isNowLerp_;

	private:
		friend class SingletonDirector<Interpolater>;

		Interpolater() {}

	public:
		// 線形補間
		float LinearLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 LinearLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 LinearLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 LinearLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// 二次補間（後が速い）
		float EaseInLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseInLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseInLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseInLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// 二次補間（先が速い）
		float EaseOutLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		// 三次補間
		float EaseInOutLerp(float start, float end, float time, float* objTimer);
		DirectX::SimpleMath::Vector2 EaseInOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector3 EaseInOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		DirectX::SimpleMath::Vector4 EaseInOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);
	};
}