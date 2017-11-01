/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"
#include <cassert>

// TODO: 追加したシーンをインクルード
#include "PlayScene.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		ライブラリインタフェースのリセット
// @param		なし
// @return		なし
===============================================================*/
void IScene::ResetDevice()
{
	// 全てのライブラリインタフェースをリセット
	SpriteRenderer& spriteRenderer	= SpriteRenderer::GetInstance();	spriteRenderer.Reset();
	TextRenderer&	textRenderer	= TextRenderer::GetInstance();		textRenderer.Reset();
}

// コンストラクタ
SceneManager::SceneManager()
{
	// 初期シーンを指定
	RegisterScene("PLAY", move(make_unique<PlayScene>()));
	nowScene_ = "PLAY";
	beforeScene_ = "PLAY";
}

/*==============================================================
// @brief		シーンの初期化
// @param		なし
// @return		なし
===============================================================*/
void SceneManager::Initialize()
{
	sceneList_[nowScene_]->Initialize();
}

/*==============================================================
// @brief		シーン管理の更新
// @param		なし
// @return		なし
===============================================================*/
void SceneManager::Update()
{
	if (beforeScene_ != nowScene_)
	{
		beforeScene_ = nowScene_;
	}

	sceneList_[nowScene_]->Update();
}

/*==============================================================
// @brief		シーンの描画
// @param		なし
// @return		なし
===============================================================*/
void SceneManager::Draw()
{
	if (CheckScene())
	{
		sceneList_[nowScene_]->Draw();
	}
}

/*==============================================================
// @brief		シーンの終了処理
// @param		なし
// @return		なし
===============================================================*/
void SceneManager::Finalize()
{
	// ライブラリインタフェースのリセット
	sceneList_[nowScene_]->ResetDevice();

	sceneList_[nowScene_]->Finalize();
	sceneList_[nowScene_].reset();
}

/*==============================================================
// @brief		シーンの登録
// @param		シーン名（string）、シーンインスタンス
// @return		なし
===============================================================*/
void SceneManager::RegisterScene(string scene, unique_ptr<IScene> newScene)
{
	sceneList_[scene] = move(newScene);
}

/*==============================================================
// @brief		シーンの変更
// @param		シーン名（string）
// @return		なし
===============================================================*/
void SceneManager::ChangeScene(string scene)
{
	// 前フレームと同じシーンだった場合は無視する
	if (scene == beforeScene_)
	{
		return;
	}

	// 登録されているシーンかチェック
	if (sceneList_.count(scene) == 0)
	{
		OutputDebugString("This scene is not register. Please register this scene for \"RegisterScene()\"");
		assert(0);
	}

	// 現在のシーンの終了処理を行う
	Finalize();

	// シーン切り替え
	nowScene_ = scene;

	// 新しいシーンの初期化処理を行う
	Initialize();
}

/*==============================================================
// @brief		シーンチェック
// @param		なし
// @return		なし
===============================================================*/
bool SceneManager::CheckScene()
{
	// 前フレームと異なるシーンの場合は描画しない
	return nowScene_ == beforeScene_ ? true : false;
}