/* =====================================================================
//! @param		「Interpolater」ヘッダ（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <SimpleMath.h>
#include <string>
#include "../Common/Constant.h"

namespace GucchiLibrary
{
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
	// @mode		SPHERE_LERP	：	球面線形補間
	*/
	enum class INTERPOLATE_MODE : int
	{
		LERP,
		EASE_IN,
		EASE_OUT,
		EASE_INOUT,
		SPHERE_LERP
	};

	class Interpolater;

	/*
	// @class		InterpolateState クラス（template）
	// @content		補間用ステート
	*/
	template <class T>
	class InterpolateState
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	private:
		std::map<std::wstring, float>									timer_;			// ローカルタイマー
		std::map<std::wstring, INTERPOLATE_STATE>						state_;			// 補間中かどうか

		std::map<std::wstring, T>										start_;			// 始点
		std::map<std::wstring, T>										end_;			// 終点
		std::map<std::wstring, float>									runTime_;		// 実行時間
		std::map<std::wstring, INTERPOLATE_MODE>						mode_;			// 補間モード

		std::map<std::wstring, float>									startTime_;		// 補間開始時点の時間
		std::map<std::wstring, float>									nowTime_;		// 補間中での時間

	public:
		// コンストラクタ
		InterpolateState() = default;

		// デストラクタ
		virtual ~InterpolateState()
		{
			timer_.clear();
			state_.clear();
			start_.clear();
			end_.clear();
			runTime_.clear();
			mode_.clear();
			startTime_.clear();
			nowTime_.clear();
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
		// @result		補間結果（T）
		*/
		T GetResult(const std::wstring& action)
		{
			if (state_[action] != INTERPOLATE_STATE::FINISH)
			{
				// 結果を取得
				return Interpolate(mode_[action], start_[action], end_[action], runTime_[action], action, this);
			}

			return end_[action];
		}

		/*
		// @method		GetResult
		// @content		補間結果の取得（軸使用補間）
		// @param		補間アクション名（wstring）
		// @result		補間結果（T）
		*/
		Vector3 GetResult(const std::wstring& action, const Vector3& axis)
		{
			if (state_[action] != INTERPOLATE_STATE::FINISH)
			{
				// 結果を取得
				return Interpolate(mode_[action], start_[action], end_[action], axis, runTime_[action], action, this);
			}

			return end_[action];
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
				if (state.second != INTERPOLATE_STATE::FINISH)
				{
					return true;
				}
			}

			return false;
		}

		/*
		// @method		GetState
		// @content		補間状態の取得（アクションが無ければNONEを返す）
		// @result		補間状態（INTERPOLATE_STATE）
		*/
		INTERPOLATE_STATE GetState(const std::wstring& action)
		{
			if (state_.count(action) == 0)
			{
				return INTERPOLATE_STATE::NONE;
			}

			return state_[action];
		}

		/*
		// @method		Reset
		// @content		リセット
		*/
		void Reset()
		{
			timer_.clear();
			state_.clear();
			start_.clear();
			end_.clear();
			runTime_.clear();
			mode_.clear();
		}

		/* アクセッサ */

		void SetState(const std::wstring& action, INTERPOLATE_STATE state)	{ state_[action] = state; }

		inline float GetTimer(const std::wstring& action)					{ return timer_[action]; }

	private:
		/*
		// @method		Interpolate
		// @content		補間での共通処理
		// @param		補間モード（INTERPOLATE_MODE）
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @param		補間アクション名（wstring）
		// @param		補間ステート（InterpolateState<T>*）
		// @result		補間値（T）
		*/
		T Interpolate(INTERPOLATE_MODE mode, const T& start, const T& end, float time, const std::wstring& action, InterpolateState<T>* state)
		{
			// 補間中でないなら時間等を初期化
			if (state->GetState(action) == INTERPOLATE_STATE::NONE)
			{
				startTime_[action] = state->GetTimer(action);
				state->SetState(action, INTERPOLATE_STATE::NOW);
			}

			// 時間更新
			nowTime_[action] = state->GetTimer(action) - startTime_[action];

			// 補間完了かどうか
			if (nowTime_[action] >= (time * FRAME_PER_SECOND))
			{
				state->SetState(action, INTERPOLATE_STATE::FINISH);
				return end;
			}

			float lerpTime = nowTime_[action] / (time * FRAME_PER_SECOND);

			// 補間移動
			return GetResultToInterpolateMode(mode, start, end, lerpTime);
		}

		/*
		// @method		Interpolate
		// @content		補間での共通処理
		// @param		補間モード（INTERPOLATE_MODE）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		軸（Vector3）	：	デフォルト（Vector3::Zero）
		// @param		媒介変数（float）
		// @param		補間アクション名（wstring）
		// @param		補間ステート（InterpolateState<Vector3>*）
		// @result		補間値（Vector3）
		*/
		Vector3 Interpolate(INTERPOLATE_MODE mode, const Vector3& start, const Vector3& end, const Vector3& axis, float time, const std::wstring& action, InterpolateState<Vector3>* state)
		{
			// 補間中でないなら時間等を初期化
			if (state->GetState(action) == INTERPOLATE_STATE::NONE)
			{
				startTime_[action] = state->GetTimer(action);
				state->SetState(action, INTERPOLATE_STATE::NOW);
			}

			// 時間更新
			nowTime_[action] = state->GetTimer(action) - startTime_[action];

			// 補間完了かどうか
			if (nowTime_[action] >= (time * FRAME_PER_SECOND))
			{
				state->SetState(action, INTERPOLATE_STATE::FINISH);
				return end;
			}

			float lerpTime = nowTime_[action] / (time * FRAME_PER_SECOND);

			// 補間移動
			return GetResultToInterpolateMode(mode, start, end, axis, lerpTime);
		}

		/*
		// @method		GetResultToInterpolateMode
		// @method		指定したモードから補間値を取得
		// @param		補間モード（INTERPOLATE_MODE）
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @return		補間値（T）
		*/
		T GetResultToInterpolateMode(INTERPOLATE_MODE mode, const T& start, const T& end, float time)
		{
			T result;

			switch (mode)
			{
			case INTERPOLATE_MODE::LERP:			// 線形補間	
				result = Lerp(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_IN:			// 二次補間（後が速い）
				result = EaseIn(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_OUT:		// 二次補間（先が速い）
				result = EaseOut(start, end, time);
				break;

			case INTERPOLATE_MODE::EASE_INOUT:		// 三次補間
				result = EaseInOut(start, end, time);
				break;

			default:
				break;
			}

			return result;
		}

		/*
		// @method		GetResultToInterpolateMode
		// @method		指定したモードから補間値を取得
		// @param		補間モード（INTERPOLATE_MODE）
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		軸（Vector3）	：	デフォルト（Vector3::Zero）
		// @param		媒介変数（float）
		// @return		補間値（Vector3）
		*/
		Vector3 GetResultToInterpolateMode(INTERPOLATE_MODE mode, const Vector3& start, const Vector3& end, const Vector3& axis, float time)
		{
			Vector3 result;

			switch (mode)
			{
			case INTERPOLATE_MODE::SPHERE_LERP:		// 球面線形補間
				result = SphereLerp(start, end, axis, time);

			default:
				break;
			}

			return result;
		}

		/*
		// @method		Lerp（static）
		// @method		線形補間
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @return		補間値（T）
		*/
		static T Lerp(const T& start, const T& end, float t)
		{
			return start + (end - start) * t;
		}

		/*
		// @method		EaseIn（static）
		// @method		二次補間（後が速い）
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @return		補間値（T）
		*/
		static T EaseIn(const T& start, const T& end, float t)
		{
			return start + (end - start) * (t * t);
		}

		/*
		// @method		EaseOut（static）
		// @method		二次補間（先が速い）
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @return		補間値（T）
		*/
		static T EaseOut(const T& start, const T& end, float t)
		{
			return start + (end - start) * (t * (2.0f - t));
		}

		/*
		// @method		EaseInOut（static）
		// @method		三次補間
		// @param		始点（T）
		// @param		終点（T）
		// @param		媒介変数（float）
		// @return		補間値（T）
		*/
		static T EaseInOut(const T& start, const T& end, float t)
		{
			return start + (end - start) * ((t * t) * (3.0f - t * 2.0f));
		}

		/*
		// @method		SphereLerp
		// @method		球面線形補間
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		媒介変数（float）
		// @return		補間値（Vector3）
		*/
		static Vector3 SphereLerp(const Vector3& start, const Vector3& end, const Vector3& axis, float t)
		{
			// 軸からのベクトルを取得
			Vector3 s = start - axis;
			Vector3 e = end - axis;
			s.Normalize();	e.Normalize();

			// ２ベクトル間の鋭角の角度を求める
			float angle = acosf(s.Dot(e));

			// sinθを求める
			float sinTh = sinf(angle);

			// 線形補間係数を求める
			float sPos = sinf(angle * (1 - t));
			float ePos = sinf(angle * t);

			// 始点から終点までの線形補間
			Vector3 data = (sPos * s + ePos * e) / (sinTh == 0 ? 0.0000001f : sinTh);
			data.Normalize();

			// 半径を求める
			float rad = (start - axis).Length();

			return data * rad + axis;
		}
	};

	/*
	// @class		InterpolateDirector クラス
	// @content		全タイプの補間をするための倉庫
	*/
	class InterpolateDirector
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Vector4 = DirectX::SimpleMath::Vector4;

	public:
		std::unique_ptr<InterpolateState<float>>		stateF_;
		std::unique_ptr<InterpolateState<Vector2>>		stateV2_;
		std::unique_ptr<InterpolateState<Vector3>>		stateV3_;
		std::unique_ptr<InterpolateState<Vector4>>		stateV4_;

	public:
		// コンストラクタ
		InterpolateDirector()
		{
			// 実体化
			stateF_  = std::make_unique<InterpolateState<float>>();
			stateV2_ = std::make_unique<InterpolateState<Vector2>>();
			stateV3_ = std::make_unique<InterpolateState<Vector3>>();
			stateV4_ = std::make_unique<InterpolateState<Vector4>>();
		}

		// デストラクタ
		virtual ~InterpolateDirector() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update()
		{
			stateF_->Update();
			stateV2_->Update();
			stateV3_->Update();
			stateV4_->Update();
		}

		/*
		// @method		Reset
		// @content		全ステートのリセット
		*/
		void Reset()
		{
			stateF_->Reset();
			stateV2_->Reset();
			stateV3_->Reset();
			stateV4_->Reset();
		}
	};
}