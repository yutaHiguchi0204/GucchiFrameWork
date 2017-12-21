/* =====================================================================
//! @param		「Interpolater」ヘッダ（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <CommonStates.h>
#include <d3d11_1.h>
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
	// @mode		NOW		：　補間中
	// @mode		FINISH	：　補間終了
	*/
	enum class INTERPOLATE_STATE : int
	{
		NONE,
		NOW,
		FINISH
	};

	/*
	// @content		使用する補間関数
	// @mode		LERP		：	線形補間
	// @mode		EASE_IN		：	二次補間（後が速い）
	// @mode		EASE_OUT	：	二次補間（先が速い）
	// @mode		EASE_INOUT	：	三次補間
	*/
	enum class INTERPOLATE_MODE : int
	{
		LERP,
		EASE_IN,
		EASE_OUT,
		EASE_INOUT
	};

	/*
	// @class		InterpolateState クラス（template）
	// @content		補間用ステート
	*/
	template <class T>
	class InterpolateState
	{
	private:
		std::map<std::wstring, float>									timer_;			// ローカルタイマー
		std::map<std::wstring, INTERPOLATE_STATE>						state_;			// 補間中かどうか

		std::map<std::wstring, T>										start_;			// 始点
		std::map<std::wstring, T>										end_;			// 終点
		std::map<std::wstring, float>									runTime_;		// 実行時間
		std::map<std::wstring, INTERPOLATE_MODE>						mode_;			// 補間モード

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
				timer.second++;
			}
		}

		/*
		// @method		Entry
		// @content		補間開始
		// @param		補間アクション名（wstring）
		// @param		始点（T）
		// @param		終点（T）
		// @param		実行時間（float）
		// @param		補間モード（INTERPOLATE_MODE）
		*/
		void Entry(std::wstring action, T start, T end, float runTime, INTERPOLATE_MODE mode)
		{
			timer_[action] = 0;
			state_[action] = INTERPOLATE_STATE::NONE;

			start_[action] = start;
			end_[action] = end;
			runTime_[action] = runTime;
			mode_[action] = mode;
		}

		/*
		// @method		GetResult
		// @content		補間結果の取得
		// @param		補間アクション名（wstring）
		// @param		始点（T）
		// @result		補間結果（T）
		*/
		T GetResult(std::wstring action)
		{
			if (state_[action] == INTERPOLATE_STATE::NONE)
			{
				state_[action] = INTERPOLATE_STATE::NOW;
			}

			// 結果を取得
			T result;
			switch (mode_[action])
			{
			case INTERPOLATE_MODE::LERP:		result = Interpolater::Lerp(start_[action], end_[action], runTime_[action], timer_[action]);		break;
			case INTERPOLATE_MODE::EASE_IN:		result = Interpolater::EaseIn(start_[action], end_[action], runTime_[action], timer_[action]);		break;
			case INTERPOLATE_MODE::EASE_OUT:	result = Interpolater::EaseOut(start_[action], end_[action], runTime_[action], timer_[action]);		break;
			case INTERPOLATE_MODE::EASE_INOUT:	result = Interpolater::EaseInOut(start_[action], end_[action], runTime_[action], timer_[action]);	break;
			}

			// 補間が終了していたらステートを終了に変える
			if (!Interpolater::IsLerp())
			{
				state_[action] = INTERPOLATE_STATE::FINISH;
			}

			return result;
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

	/*
	// @class		InterpolateDirector クラス
	// @content		全タイプの補間をするための倉庫
	*/
	class InterpolateDirector
	{
	public:
		std::unique_ptr<InterpolateState<float>>							stateF_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector2>>		stateV2_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector3>>		stateV3_;
		std::unique_ptr<InterpolateState<DirectX::SimpleMath::Vector4>>		stateV4_;

	public:
		// コンストラクタ
		InterpolateDirector();

		// デストラクタ
		virtual ~InterpolateDirector() {}

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();
	};
}