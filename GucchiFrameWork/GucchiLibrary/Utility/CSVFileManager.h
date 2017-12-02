/* =====================================================================
//! @param		「CSVFileManager」ヘッダ（CSVファイル管理）
//! @create		樋口 裕太
//! @date		17/11/29
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <memory>
#include <string>
#include <vector>

namespace GucchiLibrary
{
	/*
	// @class		CSVFileManager クラス
	// @content		CSVファイルを扱うクラス
	*/
	class CSVFileManager
	{
	public:
		static const std::wstring FILE_PATH_DATA;
		static const std::wstring EXT_CSV;

	public:
		/*
		// @method		LoadCSVFile（static）
		// @content		CSVファイル読み込み
		// @param		CSVファイル名（wstring）
		// @return		データ（vector<vector<int>>）
		*/
		static std::vector<std::vector<int>> LoadCSVFile(const std::wstring csvFile);
	};
}