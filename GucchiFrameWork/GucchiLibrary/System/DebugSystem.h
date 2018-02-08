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
		// @param		エラーログかどうか（bool）	：	デフォルト（false）
		*/
		static void DebugLog(wchar_t* message, bool error = false)
		{
#if defined(MODE_DEBUG)
			// ログメッセージ
			std::wstringstream log;

			log << L"\n";
			log << L"**************************************************\n";
			if (error) log << L"Error!: ";
			log << message << L"\n";
			log << L"**************************************************\n";
			log << L"\n";

			OutputDebugStringW(log.str().c_str());
#endif
		}

		/*
		// @method		DebugLog（static）
		// @content		ログ表示
		// @param		メッセージ（wstring）
		// @param		エラーログかどうか（bool）	：	デフォルト（false）
		*/
		static void DebugLog(std::wstring message, bool error = false)
		{
			DebugLog(message.c_str(), error);
		}
	};
}