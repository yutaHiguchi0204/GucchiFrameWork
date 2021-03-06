/* =====================================================================
//! @param		「Game」ソース
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */

// ヘッダファイルのインクルード
#include "Game.h"

// 名前空間
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;
using namespace std;

extern void ExitGame();

// コンストラクタ
Game::Game(HINSTANCE hInstance, int nCmdShow)
	: Framework(hInstance, nCmdShow)
{
	// ゲームメイン生成
	main_ = make_unique<GameMain>();
}

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void Game::Initialize()
{
	// デバイス関連などの初期化はここに記述
	particleRenderer_.Initialize();
	primitiveRenderer_.Initialize();

	// その他ゲーム内関連はGameMainの初期化に書いてください（基本的にここはいじらない）
	main_->Initialize();
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void Game::Finalize()
{
	// デバイス関連などの終了処理はここに記述

	// ゲーム内関連の終了処理はGameMainの終了処理に書いてください（基本的にここはいじらない）
	main_->Finalize();
}

/*==============================================================
// @brief		更新処理
// @param		時間処理（StepTimer）
// @return		なし
===============================================================*/
void Game::Update(const StepTimer& timer)
{
	// デバイス関連などの更新はここに記述
	objectRenderer_.Update();			// オブジェクト
	particleRenderer_.Update();			// パーティクル
	spriteRenderer_.Update();			// スプライト

	// ゲーム内関連の更新処理はGameMainの更新に書いてください（基本的にここはいじらない）
	main_->Update();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void Game::Render()
{
	// デバイス関連などの描画はここに記述

	// ライブラリインタフェースでの描画処理
	objectRenderer_.Draw();				// オブジェクト
	particleRenderer_.Draw();			// パーティクル
	primitiveRenderer_.Draw();			// プリミティブ
	spriteRenderer_.Draw();				// スプライト
	textRenderer_.Draw();				// テキスト

    // ゲーム内関連の描画処理はGameMainの描画に書いてください（基本的にここはいじらない）
	main_->Draw();
}