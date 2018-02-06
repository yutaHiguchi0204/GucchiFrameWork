/* =====================================================================
//! @param		「CSVFileManager」ヘッダ（CSVファイル管理）
//! @create		樋口 裕太
//! @date		17/11/29
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <cassert>
#include <d3d11_1.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../Common/DebugSwitch.h"
#include "../System/DebugSystem.h"

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
		static std::vector<std::vector<int>> LoadCSVFile(const std::wstring csvFile)
		{
			// ファイル読み込み
			std::wstring fileName = FILE_PATH_DATA + csvFile + EXT_CSV;
			std::ifstream ifs(fileName);

			// エラー処理
			if (!ifs)
			{
				DebugSystem::DebugLog(L"CSV file load failed.");
				assert(ifs);
			}

			// データをレコードごとに取得
			std::vector<std::vector<int>> data;
			std::string tmp;
			int i = 0;
			while (getline(ifs, tmp))
			{
				std::string token;
				std::istringstream stream(tmp);

				// 行配列の生成
				data.emplace_back();

				// カンマ区切りでデータを取得
				while (getline(stream, token, ','))
				{
					// データを挿入
					data[i].emplace_back(stoi(token));
				}

				i++;
			}

			// ファイルを閉じる
			ifs.close();

			return data;
		}
	};

	// 静的メンバの定義
	__declspec(selectany) const std::wstring CSVFileManager::FILE_PATH_DATA(L"Resources/Data/");
	__declspec(selectany) const std::wstring CSVFileManager::EXT_CSV(L".csv");
}