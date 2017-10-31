/* =====================================================================
//! @param		「GameMain」ソース
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */

// ヘッダファイルのインクルード
#include "GameMain.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Initialize()
{
	// 初期シーンを設定
	SceneManager& sceneManager = SceneManager::GetInstance();
	scene_ = sceneManager.ChangeScene(SceneManager::PLAY);

	// TODO: ゲーム関連の初期化
	scene_->Initialize();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Update()
{
	// シーン管理の更新（前フレーム更新）
	sceneManager_.Update();

	// TODO: ゲーム関連の更新
	scene_->Update();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Draw()
{
	// TODO: ゲーム関連の描画
	if (sceneManager_.CheckScene())
	{
		scene_->Draw();
	}
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Finalize()
{
	// TODO: ゲーム関連の終了処理
	scene_->Finalize();
}