/* =====================================================================
//! @param		「StepTimer」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <windows.h>
#include <exception>
#include <stdint.h>

namespace GucchiLibrary
{
	// アニメーションとシミュレーションのタイミングヘルパー
	class StepTimer
	{
	public:
		// 10,000,000 Ticks/s
		static const uint64_t TicksPerSecond;

	public:
		static double TicksToSeconds(uint64_t ticks)	{ return static_cast<double>(ticks) / TicksPerSecond; }
		static uint64_t SecondsToTicks(double seconds)	{ return static_cast<uint64_t>(seconds * TicksPerSecond); }

	private:
		// QPCユニット
		LARGE_INTEGER	qpcFrequency_;
		LARGE_INTEGER	qpcLastTime_;
		uint64_t		qpcMaxDelta_;

		// ティック形式
		uint64_t		elapsedTicks_;
		uint64_t		totalTicks_;
		uint64_t		leftOverTicks_;

		// フレームレート追跡
		uint32_t		frameCount_;
		uint32_t		framesPerSecond_;
		uint32_t		framesThisSecond_;
		uint64_t		qpcSecondCounter_;

		// タイムステップモード構成
		bool			isFixedTimeStep_;
		uint64_t		targetElapsedTicks_;

	public:
		StepTimer();

		// Update情報から経過時間を取得
		inline uint64_t GetElapsedTicks() const				{ return elapsedTicks_; }
		inline double	GetElapsedSeconds() const			{ return TicksToSeconds(elapsedTicks_); }

		// プログラムの開始から現在までの合計時間を取得
		inline uint64_t GetTotalTicks() const				{ return totalTicks_; }
		inline double	GetTotalSeconds() const				{ return TicksToSeconds(totalTicks_); }

		// プログラムを開始してからの更新総数を取得
		inline uint32_t GetFrameCount() const				{ return frameCount_; }

		// 現在のフレームレートを取得
		inline uint32_t GetFramesPerSecond() const			{ return framesPerSecond_; }

		// 固定または可変タイムステップモードを使用するかどうかの設定
		void SetFixedTimeStep(bool isFixedTimestep)			{ isFixedTimeStep_ = isFixedTimestep; }

		// タイムステップモードで更新を呼び出す頻度を設定
		void SetTargetElapsedTicks(uint64_t targetElapsed)	{ targetElapsedTicks_ = targetElapsed; }
		void SetTargetElapsedSeconds(double targetElapsed)	{ targetElapsedTicks_ = SecondsToTicks(targetElapsed); }

		// 意図的なタイミングの不連続性（例えば、IOの動作を阻止する）の後、これをコールして、修正されたタイムステップ論理が一連の追いつきの更新呼び出しを試みるのを避ける
		void ResetElapsedTime();

		// タイマーの状態を更新し、指定されたUpdate関数を適切な回数呼び出す
		template<typename TUpdate>
		void Tick(const TUpdate& update)
		{
			// 時間照会
			LARGE_INTEGER currentTime;

			if (!QueryPerformanceCounter(&currentTime))
			{
				throw std::exception("QueryPerformanceCounter");
			}

			uint64_t timeDelta = currentTime.QuadPart - qpcLastTime_.QuadPart;

			qpcLastTime_ = currentTime;
			qpcSecondCounter_ += timeDelta;

			// デルタクランプ
			if (timeDelta > qpcMaxDelta_)
			{
				timeDelta = qpcMaxDelta_;
			}

			// QPC単位を正規のチック形式に変換
			timeDelta *= TicksPerSecond;
			timeDelta /= qpcFrequency_.QuadPart;

			uint32_t lastFrameCount = frameCount_;

			if (isFixedTimeStep_)
			{
				// 固定タイムステップ更新ロジック

				// アプリが目標経過時間（ミリ秒の1/4以内）に非常に近いところで実行されている場合、目標値に正確に一致するようにクロックをクランプするだけです。
				// これにより、時間の経過と共に小さくて無関係なエラーが蓄積されることを防ぎます。
				// このクランプがなければ、59.94 NTSCディスプレイでvsyncを有効にして実行されている60 fpsの固定アップデートを要求したゲームは、最終的にフレームを落とすほどの小さなエラーを蓄積します。
				// スムーズに動作させるために、小さな偏差をゼロに丸めるほうが良いです。

				if (abs(static_cast<int64_t>(timeDelta - targetElapsedTicks_)) < static_cast<int64_t>(TicksPerSecond) / 4000)
				{
					timeDelta = targetElapsedTicks_;
				}

				leftOverTicks_ += timeDelta;

				while (leftOverTicks_ >= targetElapsedTicks_)
				{
					elapsedTicks_ = targetElapsedTicks_;
					totalTicks_ += targetElapsedTicks_;
					leftOverTicks_ -= targetElapsedTicks_;
					frameCount_++;

					update();
				}
			}
			else
			{
				// 可変タイムステップ更新ロジック
				elapsedTicks_ = timeDelta;
				totalTicks_ += timeDelta;
				leftOverTicks_ = 0;
				frameCount_++;

				update();
			}

			// フレームレートの追跡
			if (frameCount_ != lastFrameCount)
			{
				framesThisSecond_++;
			}

			if (qpcSecondCounter_ >= static_cast<uint64_t>(qpcFrequency_.QuadPart))
			{
				framesPerSecond_ = framesThisSecond_;
				framesThisSecond_ = 0;
				qpcSecondCounter_ %= qpcFrequency_.QuadPart;
			}
		}
	};
}