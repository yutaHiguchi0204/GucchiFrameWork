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
	case COLLISION::LEFT:		// 左
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

	case COLLISION::RIGHT:		// 右
		// 画面端なら当たったこととする
		if (nowX + 1 >= static_cast<int>(data[nowY].size()))
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY][nowX + 1] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

	case COLLISION::TOP:		// 上
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

	case COLLISION::BOTTOM:		// 下
		// 画面端なら当たったこととする
		if (nowY + 1 >= static_cast<int>(data.size()))
		{
			return true;
		}

		// 障害物かどうかチェック
		if (data[nowY + 1][nowX] == static_cast<int>(TipData::TIP_TYPE::SOLID))
		{
			return true;
		}

		break;

	default:
		break;
	}

	return false;
}