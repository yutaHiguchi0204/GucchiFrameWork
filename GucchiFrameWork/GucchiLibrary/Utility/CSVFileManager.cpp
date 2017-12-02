/* =====================================================================
//! @param		「CSVFileManager」ソース（CSVファイル管理）
//! @create		樋口 裕太
//! @date		17/11/29
===================================================================== */

// ヘッダファイルのインクルード
#include "CSVFileManager.h"
#include <cassert>
#include <d3d11_1.h>
#include <fstream>
#include <sstream>

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const wstring CSVFileManager::FILE_PATH_DATA = L"Resources/Data/";
const wstring CSVFileManager::EXT_CSV = L".csv";

// メンバ関数の定義

/*==============================================================
// @brief		CSVファイル読み込み
// @param		CSVファイル名（wstring）
// @return		データ（vector<vector<int>>）
===============================================================*/
vector<vector<int>> CSVFileManager::LoadCSVFile(const wstring csvFile)
{
	// ファイル読み込み
	wstring fileName = FILE_PATH_DATA + csvFile + EXT_CSV;
	ifstream ifs(fileName);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"CSV file load failed.");
		assert(ifs);
	}

	// データをレコードごとに取得
	vector<vector<int>> data;
	string tmp;
	int i = 0;
	while (getline(ifs, tmp))
	{
		string token;
		istringstream stream(tmp);

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