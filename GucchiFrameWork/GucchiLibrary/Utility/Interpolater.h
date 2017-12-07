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
		static bool isNowInterpolate_;

	public:
		/* 線形補間 */

		/*
		// @method		Lerp（static）
		// @content		線形補間
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static float Lerp(float start, float end, float time, float objTimer);

		/*
		// @method		Lerp（static）
		// @content		線形補間
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector2 Lerp(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);

		/*
		// @method		Lerp（static）
		// @content		線形補間
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector3 Lerp(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		Lerp（static）
		// @content		線形補間
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector4 Lerp(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* 二次補間（後が速い） */

		/*
		// @method		EaseIn（static）
		// @content		二次補間（後が速い）
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static float EaseIn(float start, float end, float time, float objTimer);

		/*
		// @method		EaseIn（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector2 EaseIn(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseIn（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector3 EaseIn(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseIn（static）
		// @content		二次補間（後が速い）
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector4 EaseIn(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* 二次補間（先が速い） */

		/*
		// @method		EaseOut（static）
		// @content		二次補間（先が速い）
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static float EaseOut(float start, float end, float time, float objTimer);

		/*
		// @method		EaseOut（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector2 EaseOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseOut（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector3 EaseOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseOut（static）
		// @content		二次補間（先が速い）
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector4 EaseOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/* 三次補間 */

		/*
		// @method		EaseInOut（static）
		// @content		三次補間
		// @param		始点（float）
		// @param		終点（float）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static float EaseInOut(float start, float end, float time, float objTimer);

		/*
		// @method		EaseInOut（static）
		// @content		三次補間
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector2 EaseInOut(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, float time, float objTimer);
		
		/*
		// @method		EaseInOut（static）
		// @content		三次補間
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end, float time, float objTimer);
		
		/*
		// @method		EaseInOut（static）
		// @content		三次補間
		// @param		始点（Vector4）
		// @param		終点（Vector4）
		// @param		実行時間（float）
		// @param		ローカルタイマー（float）
		*/
		static DirectX::SimpleMath::Vector4 EaseInOut(DirectX::SimpleMath::Vector4 start, DirectX::SimpleMath::Vector4 end, float time, float objTimer);

		/*
		// @method		IsInterpolate（static）
		// @content		補間中かどうか
		// @return		結果（bool）
		*/
		static bool IsInterpolate();
	};
}