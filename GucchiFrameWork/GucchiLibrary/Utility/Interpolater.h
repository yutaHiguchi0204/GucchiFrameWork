/* =====================================================================
//! @param		「Interpolater」ヘッダ（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>

namespace GucchiLibrary
{
	/*
	// @class		Interpolater クラス
	// @content		補間ライブラリ
	*/
	class Interpolater
	{
	private:
		static float startTime_;
		static float nowTime_;
		static bool isNowLerp_;

	public:
		/* 線形補間 */

		/*
		// @method		LinearLerp（static）
		// @content		線形補間
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static float LinearLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		LinearLerp（static）
		// @content		線形補間
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector2 LinearLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);

		/*
		// @method		LinearLerp（static）
		// @content		線形補間
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector3 LinearLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		LinearLerp（static）
		// @content		線形補間
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector4 LinearLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* 二次補間（後が速い） */

		/*
		// @method		EaseInLerp（static）
		// @content		二次補間（後が速い）
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static float EaseInLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseInLerp（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector2 EaseInLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseInLerp（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector3 EaseInLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseInLerp（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector4 EaseInLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* 二次補間（先が速い） */

		/*
		// @method		EaseOutLerp（static）
		// @content		二次補間（先が速い）
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static float EaseOutLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseOutLerp（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector2 EaseOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseOutLerp（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector3 EaseOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseOutLerp（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector4 EaseOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);

		/* 三次補間 */

		/*
		// @method		EaseInOutLerp（static）
		// @content		三次補間
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static float EaseInOutLerp(float start, float end, float time, float* objTimer);

		/*
		// @method		EaseInOutLerp（static）
		// @content		三次補間
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector2 EaseInOutLerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float* objTimer);
		
		/*
		// @method		EaseInOutLerp（static）
		// @content		三次補間
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector3 EaseInOutLerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float* objTimer);
		
		/*
		// @method		EaseInOutLerp（static）
		// @content		三次補間
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float*）
		*/
		static DirectX::SimpleMath::Vector4 EaseInOutLerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float* objTimer);
	};
}