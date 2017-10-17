/* =====================================================================
//! @param		「GameMain」ソース
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */

// ヘッダファイルのインクルード
#include "GameMain.h"

// 名前空間
using namespace GucchiLibrary;

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Initialize()
{
	// TODO: ゲーム関連の初期化
	SpriteFactory& factory = SpriteFactory::GetInstance();
	//test_ = factory.CreateSpriteFromFile(L"cat");

	// 登録
	SpriteRenderer& render = SpriteRenderer::GetInstance();
	//render.RegisterSprite(test_.get());
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Update()
{
	// TODO: ゲーム関連の更新
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Render()
{
	// TODO: ゲーム関連の描画
	SpriteRenderer& render = SpriteRenderer::GetInstance();
	//render.Draw();
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Finalize()
{
	// TODO: ゲーム関連の終了処理
}