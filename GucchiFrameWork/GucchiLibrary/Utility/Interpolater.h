/* =====================================================================
//! @param		「Interpolater」ヘッダ（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <functional>
#include <map>
#include <SimpleMath.h>
#include <string>

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

	/*
	// @content		状態
	// @mode		NONE	：　何もしていない状態
	// @mode		LERP	：　補間中
	// @mode		OUT		：　補間終了
	*/
	enum class INTERPOLATE_STATE : int
	{
		NONE,
		NOW,
		FINISH
	};

	/*
	// @class		InterpolateState クラス（template）
	// @content		補間用ステート
	*/
	template <class T>
	class InterpolateState
	{
	private:
		std::map<std::wstring, float>				timer_;			// ローカルタイマー
		std::map<std::wstring, INTERPOLATE_STATE>	state_;			// 補間中かどうか

		std::map<std::wstring, T>					start_;			// 始点
		std::map<std::wstring, T>					end_;			// 終点
		std::map<std::wstring, float>				runTime_;		// 実行時間

	public:
		// コンストラクタ
		InterpolateState() {}

		// デストラクタ
		virtual ~InterpolateState()
		{
			timer_.clear();
			state_.clear();
		}

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update()
		{
			// タイマー計測
			for (auto& timer : timer_)
			{
				timer++;
			}
		}

		/*
		// @method		Entry
		// @content		補間開始
		// @param		補間アクション名（wstring）
		*/
		void Entry(std::wstring action, T start, T end, float runTime)
		{
			timer_[action] = 0;
			state_[action] = INTERPOLATE_STATE::NONE;

			start_[action] = start;
			end_[action] = end;
			runTime_[action] = runTime;
		}

		/*
		// @method		GetResult
		// @content		補間結果の取得
		// @param		補間アクション名（wstring）
		// @result		補間結果（T）
		*/
		T GetResult(std::wstring action, std::function<T(T, T, float, float)> func)
		{
			if (state_[action] == INTERPOLATE_STATE::NONE)
			{
				state_[action] = INTERPOLATE_STATE::NOW;
			}

			// 結果を取得
			T result = func(start_[action], end_[action], runTime_[action], timer[action]);

			// 補間が終了していたらステートを終了に変える
			if (!Interpolater::IsLerp())
			{
				state_[action] = INTERPOLATE_STATE::FINISH;
			}
		}

		/*
		// @method		IsInterpolate
		// @content		補間中かどうか
		// @result		結果（bool）
		*/
		bool IsInterpolate()
		{
			for (auto& state : state_)
			{
				if (!state == INTERPOLATE_STATE::FINISH)
				{
					return false;
				}
			}

			return true;
		}

		/* アクセッサ */

		inline const float				GetTimer(std::wstring action) { return timer_[action]; }
		inline const INTERPOLATE_STATE	GetState(std::wstring action) { return state_[action]; }
	};
}