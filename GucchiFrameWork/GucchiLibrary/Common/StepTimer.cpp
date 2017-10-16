/* =====================================================================
//! @param		「StepTimer」ソース
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */

// ヘッダファイルのインクルード
#include "StepTimer.h"

// 名前空間
using namespace GucchiLibrary;

// 静的メンバの定義
const uint64_t StepTimer::TicksPerSecond = 10000000;

// コンストラクタ
StepTimer::StepTimer()
	: elapsedTicks_(0)
	, totalTicks_(0)
	, leftOverTicks_(0)
	, frameCount_(0)
	, framesPerSecond_(0)
	, framesThisSecond_(0)
	, qpcSecondCounter_(0)
	, isFixedTimeStep_(false)
	, targetElapsedTicks_(TicksPerSecond / 60)
{
	if (!QueryPerformanceFrequency(&qpcFrequency_))
	{
		throw std::exception("QueryPerformanceFrequency");
	}

	if (!QueryPerformanceCounter(&qpcLastTime_))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	// 最大デルタを1/10秒に初期化
	qpcMaxDelta_ = qpcFrequency_.QuadPart / 10;
}

// 経過時間リセット
void StepTimer::ResetElapsedTime()
{
	if (!QueryPerformanceCounter(&qpcLastTime_))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	leftOverTicks_ = 0;
	framesPerSecond_ = 0;
	framesThisSecond_ = 0;
	qpcSecondCounter_ = 0;
}