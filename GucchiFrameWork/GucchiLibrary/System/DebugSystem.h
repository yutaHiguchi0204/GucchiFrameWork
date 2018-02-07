/* =====================================================================
//! @param		「DebugSystem」ヘッダ（Debugビルド時に行う処理）
//! @create		樋口 裕太
//! @date		18/02/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <sstream>
#include <string>
#include "../Common/DebugSwitch.h"

namespace GucchiLibrary
{
	/*
	// @class		DebugSystem クラス
	// @content		デバッグビルド用クラス
	*/
	class DebugSystem
	{
	public:
		/*
		// @method		DebugLog（static）
		// @content		ログ表示
		// @param		メッセージ（wchar_t*）
		*/
		static void DebugLog(wchar_t* message)
		{
#if defined(MODE_DEBUG)
			// ログメッセージ
			std::wstringstream log;

			log << L"\n";
			log << L"**************************************************\n";
			log << L"Error: " << message << L"\n";
			log << L"**************************************************\n";
			log << L"\n";

			OutputDebugStringW(log.str().c_str());
#endif
		}

		/*
		// @method		DebugLog（static）
		// @content		ログ表示
		// @param		メッセージ（wstring）
		*/
		static void DebugLog(std::wstring message)
		{
			DebugLog(message.c_str());
		}
	};
}