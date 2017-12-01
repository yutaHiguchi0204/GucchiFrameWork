/* =====================================================================
//! @param		「MapTip」ソース
//! @create		樋口 裕太
//! @date		17/12/01
===================================================================== */

// ヘッダファイルのインクルード
#include "MapTip.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
MapTip::MapTip(vector<vector<int>> data, int dataTypeNum, TipData::TIP_TYPE type[])
	: dataTypeNum_(dataTypeNum)
{
	// 属性の保存
	for (int i = 0; i < dataTypeNum_; i++)
	{
		typeNum_.emplace_back(type[i]);
	}

	// チップデータに挿入
	for (int i = 0; i < (int)data.size(); i++)
	{
		data_.emplace_back();

		int j = 0;
		for (auto& data : data[i])
		{
			data_[i].emplace_back();
			data_[i].at(j).SetData(data);
			data_[i].at(j).SetType(typeNum_.at(data));
			j++;
		}
	}
}