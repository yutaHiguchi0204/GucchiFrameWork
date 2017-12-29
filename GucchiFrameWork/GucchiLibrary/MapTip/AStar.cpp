/* =====================================================================
//! @param		「AStar」ソース
//! @create		樋口 裕太
//! @date		17/12/28
===================================================================== */

// ヘッダファイルのインクルード
#include "AStar.h"
#include <cassert>
#include <d3d11_1.h>
#include "../Common/DebugSwitch.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const int AStar::NUM_ADJOIN;					// 隣接タイル数
/*
// １２３
// ８　４
// ７６５
*/
Node::Point AStar::offset_[NUM_ADJOIN] = {		// オフセットリスト
	{ -1, -1 }, { 0, -1 }, { 1, -1 }, { 1,  0 }, { 1,  1 }, { 0,  1 }, { -1,  1 }, { -1,  0 }
};
vector<vector<Node*>> AStar::mapData_;			// マップデータ
list<Node*> AStar::openList_;					// オープンリスト
Node::Point AStar::start_;						// 経路探索開始地点
Node::Point AStar::end_;						// 経路探索終了地点

// メンバ関数の定義

// コンストラクタ
Node::Node()
	: cost_(0)
	, terrainCost_(0)
	, heuristic_(0)
	, parentNode_(nullptr)
	, pos_(Point{ 0, 0 })
	, attribute_(ATTRIBUTE::NONE)
	, state_(STATE::FREE)
{
}

/*==============================================================
// @brief		初期化処理
// @param		マップデータ（vector<vector<int>>）
// @return		なし
===============================================================*/
void AStar::Initialize(vector<vector<int>> map)
{
	start_	= { -1, -1 };
	end_	= { -1, -1 };

	// 各ノードの生成
	for (auto& mapRow : map)
	{
		mapData_.emplace_back();
		for (auto& mapTip : mapRow)
		{
			// 新ノード
			Node* node = new Node;

			int row = mapData_.size() - 1;
			mapData_[row].emplace_back(node);

			int column = mapData_[row].size() - 1;

			// 位置の保存
			mapData_[row][column]->SetPos(Node::Point{ column, row });

			// 属性の保存
			mapData_[row][column]->SetAttribute(static_cast<Node::ATTRIBUTE>(mapTip));

			// スタートとゴールの設定
			if (mapData_[row][column]->GetAttribute() == Node::ATTRIBUTE::START)
			{
				start_ = Node::Point{ column, row };
			}
			else if (mapData_[row][column]->GetAttribute() == Node::ATTRIBUTE::GOAL)
			{
				end_ = Node::Point{ column, row };
			}
		}
	}

	// コストとヒューリスティックの計算
	for (int i = 0; i < (int)mapData_.size(); i++)
	{
		for (int j = 0; j < (int)mapData_[i].size(); j++)
		{
			// 地形コストの設定
			int terrainCost = SetTerrainCost(j, i);
			mapData_[i][j]->SetTerrainCost(terrainCost);

			// ヒューリスティックの計算
			int heuristic = SetHeuristic(j, i);
			mapData_[i][j]->SetHeuristic(heuristic);
		}
	}

	// スタートもしくはゴールが設定されていなかったらエラー
	if (start_.posX == -1 || start_.posY == -1 || end_.posX == -1 || end_.posY == -1)
	{
#if defined(MODE_DEBUG)
		// マップデータエラー
		OutputDebugString(L"Map data error.");
#endif
		assert(false);
	}
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void AStar::Finalize()
{
	for (auto& mapRow : mapData_)
	{
		for (auto& mapTip : mapRow)
		{
			delete mapTip;
		}
	}
}

/*==============================================================
// @brief		経路探索
// @param		なし
// @return		経路探索が完了したデータ（vector<vector<Node*>>）
===============================================================*/
vector<vector<Node*>> AStar::Search()
{
	// ゴール地点のノードをオープンし、オープンリストに追加する
	mapData_[end_.posY][end_.posX]->SetState(Node::STATE::OPEN);
	openList_.emplace_back(mapData_[end_.posY][end_.posX]);

	// 現在のノード
	Node* checkNode = mapData_[end_.posY][end_.posX];

	// ゴールからスタートまでのA*経路探索
	// オープンリストが空でない
	while (!openList_.empty())
	{
		// オープンリストのうち、スコアが最小のノードを取得
		checkNode = CheckMinScoreNode();

		// 経路が完成したかどうか
		if (checkNode->GetAttribute() == Node::ATTRIBUTE::START)
		{
			checkNode->SetState(Node::STATE::CLOSED);
			return mapData_;
		}
		else
		{
			// 隣接タイルをチェック
			CheckAdjoin(checkNode);
		}
	}

	// ここにくることはない
	return mapData_;
}

/*==============================================================
// @brief		隣接するタイル８つを調べる
// @param		チェック中のノード（Node*）
// @return		なし
===============================================================*/
void AStar::CheckAdjoin(Node* node)
{
	// 現在のノードをクローズドリストに追加
	node->SetState(Node::STATE::CLOSED);

	// 現在のノードをオープンリストから削除
	for (auto itr = openList_.cbegin(); itr != openList_.cend();)
	{
		if (*itr == node)
		{
			openList_.erase(itr);
			break;
		}
		itr++;
	}

	// 隣接する８つのノードを調べる
	for (int i = 0; i < NUM_ADJOIN; i++)
	{
		// チェックする隣接タイル
		int x = node->GetPosX() + offset_[i].posX;
		int y = node->GetPosY() + offset_[i].posY;

		// マップ内かどうか
		if (x >= 0 && x < (int)mapData_[y].size() &&
			y >= 0 && y < (int)mapData_.size())
		{
			// すでにオープンリスト・クローズドリストに含まれているとき、
			// または障害物の場合は無視する
			if (mapData_[y][x]->GetState()		!= Node::STATE::OPEN		&&
				mapData_[y][x]->GetState()		!= Node::STATE::CLOSED		&&
				mapData_[y][x]->GetAttribute()	!= Node::ATTRIBUTE::WALL)
			{
				// 親ノードを設定
				mapData_[y][x]->SetParentNode(node);

				// コスト計算
				int cost = GetCost(mapData_[y][x]);
				mapData_[y][x]->SetCost(cost);

				// オープンリストに追加
				mapData_[y][x]->SetState(Node::STATE::OPEN);
				openList_.emplace_back(mapData_[y][x]);
			}
		}
	}
}

/*==============================================================
// @brief		地形コストの設定
// @param		自身の位置x（int）、自身の位置y（int）
// @return		地形コスト（int）
===============================================================*/
int AStar::SetTerrainCost(int x, int y)
{
	switch (mapData_[y][x]->GetAttribute())
	{
	case Node::ATTRIBUTE::NONE:		return 1;	break;		// 通常の道
	case Node::ATTRIBUTE::SWAMP:	return 3;	break;		// 沼
	default:						return 0;	break;
	}
}

/*==============================================================
// @brief		ヒューリスティックの計算
// @param		自身の位置x（int）、自身の位置y（int）
// @return		ヒューリスティック値（int）
===============================================================*/
int AStar::SetHeuristic(int x, int y)
{
	// X, Yの距離を求める
	int distanceX = abs(x - start_.posX) * 10;
	int distanceY = abs(y - start_.posY) * 10;

	// 距離が大きい方を返す
	return distanceX > distanceY ? distanceX : distanceY;
}

/*==============================================================
// @brief		オープンリストの中でスコアが最小のノードをチェック
// @param		なし
// @return		オープンリストの中でスコアが最小のノード（Node*）
===============================================================*/
Node* AStar::CheckMinScoreNode()
{
	// オープンリストにノードがなかったらnullを返す
	if (openList_.empty())
	{
		return nullptr;
	}

	Node* checkNode = nullptr;

	// 現在のノードにオープンリストのうちスコアが最小のノードを設定
	int scoreMin = 999;
	for (auto& node : openList_)
	{
		// スコア計算
		int score = GetScore(node);

		// スコアが最小のノードを設定
		if (score <= scoreMin)
		{
			scoreMin = score;
			checkNode = node;
		}
	}

	return checkNode;
}

/*==============================================================
// @brief		コストの計算
// @param		コストを取得したいノード（Node*）
// @return		コスト（int）
===============================================================*/
int AStar::GetCost(Node* node)
{
	int cost = 0;

	// 親ノードがあればさらに辿る
	if (node->GetParentNode())
	{
		// 上下左右
		if (abs(node->GetParentNode()->GetPosX() - node->GetPosX()) + abs(node->GetParentNode()->GetPosY() - node->GetPosY()) == 1)
		{
			cost += GetCost(node->GetParentNode()) + node->GetTerrainCost() * 10;
		}
		// 斜め
		else
		{
			cost += GetCost(node->GetParentNode()) + node->GetTerrainCost() * 15;
		}
	}

	return cost;
}

/*==============================================================
// @brief		スコアの計算
// @param		スコアを取得したいノード（Node*）
// @return		スコア（int）
===============================================================*/
int AStar::GetScore(Node* node)
{
	return node->GetCost() + node->GetHeuristic();
}