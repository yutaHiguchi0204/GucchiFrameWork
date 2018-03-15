/* =====================================================================
//! @param		「BenchMark」ソース
//! @create		樋口 裕太
//! @date		18/02/06
===================================================================== */

// ヘッダファイルのインクルード
#include "BenchMark.h"
#include "../Common/Constant.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace GucchiLibrary;

// 静的メンバの定義
LARGE_INTEGER	BenchMark::frequency_;
LARGE_INTEGER	BenchMark::begin_;
LARGE_INTEGER	BenchMark::end_;
bool			BenchMark::isTesting_ = false;

/*==============================================================
// @brief		計測開始
// @param		なし
// @return		なし
===============================================================*/
void BenchMark::Begin()
{
	// 周波数を取得
	if (!QueryPerformanceFrequency(&frequency_))
	{
		// 計測不能
		DebugSystem::DebugLog(L"Sorry, I can't count.", true);
		return;
	}

	// 現在の時間（開始時間）を取得
	if (!QueryPerformanceCounter(&begin_))
	{
		// 計測不能
		DebugSystem::DebugLog(L"Sorry, I can't count.", true);
		return;
	}

	// 計測開始
	isTesting_ = true;
}

/*==============================================================
// @brief		計測終了
// @param		なし
// @return		なし
===============================================================*/
void BenchMark::End()
{
	// 現在の時間（開始時間）を取得
	if (!QueryPerformanceCounter(&end_))
	{
		// 計測不能
		DebugSystem::DebugLog(L"Sorry, I can't count.", true);
		return;
	}

	// 計測終了
	isTesting_ = false;
}

/*==============================================================
// @brief		計測時間の取得
// @param		なし
// @return		計測時間（double）
===============================================================*/
double BenchMark::GetPerformanceTime()
{
	// 計測中
	if (isTesting_)
	{
		return 0.0;
	}

	// 分解能単位での計測時間
	LONGLONG time = end_.QuadPart - begin_.QuadPart;

	return static_cast<double>(time);
}

/*==============================================================
// @brief		計測時間の取得（秒）
// @param		なし
// @return		計測時間（double）
===============================================================*/
double BenchMark::GetPerformanceTimeOfSecond()
{
	// 計測時間
	double time = GetPerformanceTime();

	// 秒に変換
	return time / static_cast<double>(frequency_.QuadPart);
}

/*==============================================================
// @brief		計測時間の取得（フレーム）
// @param		なし
// @return		計測時間（double）
===============================================================*/
double BenchMark::GetPerformanceTimeOfFrame()
{
	// 計測時間
	double time = GetPerformanceTimeOfSecond();

	// 秒に変換
	return time * FRAME_PER_SECOND;
}