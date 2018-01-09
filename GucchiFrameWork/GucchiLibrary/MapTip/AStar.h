/* =====================================================================
//! @param		「AStar」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/28
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <list>
#include <SimpleMath.h>
#include <vector>
#include "MapTip2D.h"
#include "MapTip3D.h"

namespace GucchiLibrary
{
	/*
	// @class		Node クラス
	// @content		ノードクラス
	*/
	class Node
	{
	public:
		/*
		// @content		ノードの属性
		// @mode		NONE	：　特に何もなし
		// @mode		WALL	：　障害物判定
		// @mode		SWAMP	：　沼判定（地形コストが高い）
		// @mode		START	：　経路探索開始地点
		// @mode		GOAL	：　経路探索終了地点
		*/
		enum class ATTRIBUTE
		{
			NONE,
			WALL,
			SWAMP,
			START,
			GOAL
		};

		/*
		// @content		ノードの状態
		// @mode		FREE	：	調査していないノード
		// @mode		OPEN	：	オープンリスト
		// @mode		CLOSED	：	クローズドリスト
		*/
		enum class STATE
		{
			FREE,
			OPEN,
			CLOSED
		};

		/*
		// @struct		Point 構造体
		// @content		ポイント構造体（Vector2のintバージョン）
		*/
		struct Point
		{
			int posX;
			int posY;
		};

	private:
		int cost_;								// コスト
		int terrainCost_;						// 地形コスト
		int heuristic_;							// ヒューリスティック

		Node* parentNode_;						// 親ノード

		Point pos_;								// 座標

		ATTRIBUTE attribute_;					// ノードの属性
		STATE state_;							// チップの状態

	public:
		// コンストラクタ
		Node();

		// デストラクタ
		virtual ~Node() {}

		/* アクセッサ */

		void SetCost(int cost)					{ cost_ = cost; }
		void SetTerrainCost(int cost)			{ terrainCost_ = cost; }
		void SetHeuristic(int heuristic)		{ heuristic_ = heuristic; }
		void SetParentNode(Node* parent)		{ parentNode_ = parent; }
		void SetPos(const Point& pos)			{ pos_ = pos; }
		void SetPosX(int posX)					{ pos_.posX = posX; }
		void SetPosY(int posY)					{ pos_.posY = posY; }
		void SetAttribute(ATTRIBUTE attribute)	{ attribute_ = attribute; }
		void SetState(STATE state)				{ state_ = state; }

		inline int GetCost()					{ return cost_; }
		inline int GetTerrainCost()				{ return terrainCost_; }
		inline int GetHeuristic()				{ return heuristic_; }
		inline Node* GetParentNode()			{ return parentNode_; }
		inline const Point& GetPos() const		{ return pos_; }
		inline int GetPosX() const				{ return pos_.posX; }
		inline int GetPosY() const				{ return pos_.posY; }
		inline ATTRIBUTE GetAttribute() const	{ return attribute_; }
		inline STATE GetState() const			{ return state_; }
	};

	/*
	// @class		AStar クラス
	// @content		A* 経路探索 クラス
	*/
	class AStar
	{
	public:
		static const int NUM_ADJOIN = 8;									// 隣接タイル数

	private:
		static Node::Point offset_[NUM_ADJOIN];								// 隣接タイル数

		static std::vector<std::vector<Node*>> mapData_;					// マップデータ
		static std::list<Node*> openList_;									// オープンリスト
		static std::vector<Node*> shortestRoute_;							// 最短経路

		static Node::Point start_;											// 開始地点
		static Node::Point end_;											// 終了地点

		static DirectX::SimpleMath::Vector3 mapPos_;						// マップ自体の座標（デフォルトは０ですが、マップデータのダミーオブジェクトの位置を登録することができます）

		static std::vector<std::unique_ptr<Object>> routePlane_;			// 最短経路ナビゲーター

	public:
		/*
		// @method		Initialize（static）
		// @content		初期化処理
		// @param		マップデータ（vector<vector<int>>）
		*/
		static void Initialize(std::vector<std::vector<int>> map);

		/*
		// @method		Finalize（static）
		// @content		終了処理（メモリリーク対策のため、A* 経路探索アルゴリズムを用いた場合は必ず呼んでください）
		*/
		static void Finalize();

		/*
		// @method		Search（static）
		// @content		経路探索
		// @return		経路探索が完了したデータ（vector<vector<Node*>>）
		*/
		static std::vector<std::vector<Node*>> Search();

		/*
		// @method		GetShortestRoute（static）
		// @content		最短経路リストを取得
		// @return		最短経路リスト（vector<Node*>）
		*/
		static std::vector<Node*> GetShortestRoute();

		/*
		// @method		DrawResult（static）
		// @content		探索結果を四角形で表示
		*/
		static void DrawResult();

		/*
		// @method		SetNavigatorActive（static）
		// @content		最短経路ナビゲーターのアクティブ状態を変更
		// @param		アクティブ状態（bool）
		*/
		static void SetNavigatorActive(bool active);

		/*
		// @method		CheckAdjoin（static）
		// @content		隣接するタイル８つを調べる
		// @param		チェック中のノード（Node*）
		*/
		static void CheckAdjoin(Node* node);

		/*
		// @method		SetTerrainCost（static）
		// @content		地形コストの設定
		// @param		自身の位置x（int）
		// @param		自身の位置y（int）
		// @return		ヒューリスティック値（int）
		*/
		static int SetTerrainCost(int x, int y);

		/*
		// @method		SetHeuristic（static）
		// @content		ヒューリスティックの計算
		// @param		自身の位置x（int）
		// @param		自身の位置y（int）
		// @return		ヒューリスティック値（int）
		*/
		static int SetHeuristic(int x, int y);

		/*
		// @method		CheckMinScoreNode（static）
		// @content		オープンリストの中でスコアが最小のノードをチェック
		// @return		オープンリストの中でスコアが最小のノード（Node*）
		*/
		static Node* CheckMinScoreNode();

		/*
		// @method		GetCost（static）
		// @content		コストの計算
		// @param		コストを取得したいノード（Node*）
		// @return		コスト（int）
		*/
		static int GetCost(Node* node);

		/*
		// @method		GetScore（static）
		// @content		スコアの計算
		// @param		スコアを取得したいノード（Node*）
		// @return		スコア（int）
		*/
		static int GetScore(Node* node);

		/* アクセッサ */

		static Node* GetNode(Node::Point point)		{ return mapData_[point.posY][point.posX]; }
		static Node* GetNode(int posX, int posY)	{ return mapData_[posY][posX]; }

		static void SetMapPos(MapTip2D* map)		{ mapPos_ = DirectX::SimpleMath::Vector3(map->GetPos().x, map->GetPos().y, 0); }
		static void SetMapPos(MapTip3D* map)		{ mapPos_ = map->GetTranslate(); }
	};
}