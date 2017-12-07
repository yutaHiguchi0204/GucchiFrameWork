/* =====================================================================
//! @param		「InterpolateState」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/07
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <functional>
#include <map>
#include <string>
#include "Interpolater.h"

namespace GucchiLibrary
{
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
			T result =  func(start_[action], end_[action], runTime_[action], timer[action]);

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