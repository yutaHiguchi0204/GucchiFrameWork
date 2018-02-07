/* =====================================================================
//! @param		「BenchMark」ヘッダ（ベンチマークテスト用）
//! @create		樋口 裕太
//! @date		18/02/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <windows.h>

namespace GucchiLibrary
{
	/*
	// @class		BenchMark クラス
	// @content		ベンチマークテストクラス
	*/
	class BenchMark
	{
	private:
		static LARGE_INTEGER	frequency_;			// 高分解能カウンタの周波数
		static LARGE_INTEGER	begin_;				// 開始時間
		static LARGE_INTEGER	end_;				// 終了時間
		static bool				isTesting_;			// テスト中かどうか

	public:
		/*
		// @method		Begin（static）
		// @content		計測開始
		*/
		static void Begin();

		/*
		// @method		End（static）
		// @content		計測終了
		*/
		static void End();

		/*
		// @method		GetPerformanceTime（static）
		// @content		計測時間の取得
		*/
		static double GetPerformanceTime();

		/*
		// @method		GetPerformanceTimeOfSecond（static）
		// @content		計測時間の取得（秒）
		*/
		static double GetPerformanceTimeOfSecond();

		/*
		// @method		GetPerformanceTimeOfFrame（static）
		// @content		計測時間の取得（フレーム）
		*/
		static double GetPerformanceTimeOfFrame();
	};
}