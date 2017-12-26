/* =====================================================================
//! @param		メモリリーク検出用
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/DebugSwitch.h"

// デバッグモードでなければ検出しない
#if defined(MODE_DEBUG)

	// ヘッダファイルのインクルード
	#include <crtdbg.h>

	// マクロ定義
	#define _CRTDBG_MAP_ALLOC
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

	namespace GucchiLibrary
	{
		/*
		// @method		SetUpMemoryLeakDetector（global）
		// @content		メモリリーク検出器のセットアップ
		*/
		inline void SetUpMemoryLeakDetector()
		{
			_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
		}
	}

#endif