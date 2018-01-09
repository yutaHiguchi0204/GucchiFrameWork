/* =====================================================================
//! @param		「CollisionManager」ソース
//! @create		樋口 裕太
//! @date		17/11/29
===================================================================== */

// ヘッダファイルのインクルード
#include "CollisionManager.h"
#include "../MapTip/MapTip.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		指定した場所のマップチップをチェック
// @param		マップデータ（vector<vector<int>>）、現在のチップX（int）、現在のチップY（int）、チェックする方向（COLLISION）
// @return		結果（bool）
===============================================================*/
bool CollisionManager::CheckCollisionMapTip(vector<vector<int>> data, int nowX, int nowY, COLLISION col)
{
	switch (col)
	{
		// 左
	case COLLISION::LEFT:
		// 画面端なら当たったこととする
		if (nowX - 1 < 0)
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY][nowX - 1] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// 右
	case COLLISION::RIGHT:
		// 画面端なら当たったこととする
		if (nowX + 1 >= (int)data[nowY].size())
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY][nowX + 1] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// 上
	case COLLISION::TOP:
		// 画面端なら当たったこととする
		if (nowY - 1 < 0)
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY - 1][nowX] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

		// 下
	case COLLISION::BOTTOM:
		// 画面端なら当たったこととする
		if (nowY + 1 >= (int)data.size())
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY + 1][nowX] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;
	}

	return false;
}