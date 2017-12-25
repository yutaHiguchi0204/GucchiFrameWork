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
// @brief		全シーン共通の初期化処理
// @param		なし
// @return		なし
===============================================================*/
void IScene::CommonInitialize()
{
	// カメラ設定
	camera_ = make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	// 天球の生成
	skyDome_ = objectFactory_.CreateObjectFromFile(L"skyDome");

	// オブジェクトの登録
	objectRenderer_.RegisterObject(skyDome_.get());		// 天球
}

/*==============================================================
// @brief		全シーン共通の更新処理
// @param		なし
// @return		なし
===============================================================*/
void IScene::CommonUpdate()
{
	// カメラの更新
	camera_->Update();
}

/*==============================================================
// @brief		全シーン共通の描画処理
// @param		なし
// @return		なし
===============================================================*/
void IScene::CommonDraw()
{

}

/*==============================================================
// @brief		全シーン共通の終了処理
// @param		なし
// @return		なし
===============================================================*/
void IScene::CommonFinalize()
{
	// サウンドの解放
	soundManager_.Dispose();
}

/*==============================================================
// @brief		ライブラリインタフェースのリセット
// @param		なし
// @return		なし
===============================================================*/
void IScene::ResetDevice()
{
	// 全てのライブラリインタフェースをリセット
	objectRenderer_.Reset();
	spriteRenderer_.Reset();
	primitiveRenderer_.Reset();
	textRenderer_.Reset();
}

// コンストラクタ
SceneManager::SceneManager()
{
	// 初期シーンを指定
	RegisterScene("PLAY", move(make_unique<PlayScene>()));
	nowScene_ = "PLAY";
	beforeScene_ = "PLAY";

	// サウンドの初期設定（TODO: サウンドを導入する際は、Initializeのコメントをはずしてファイルを設定してください）
	SoundManager& soundManager = SoundManager::GetInstance();
	//soundManager.Initialize("Acfファイル", "Acbファイル", "Awbファイル");
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
}

/*==============================================================
// @brief		シーンの登録
// @param		シーン名（string）、シーンインスタンス（unique_ptr<IScene>）
// @return		なし
===============================================================*/
void SceneManager::RegisterScene(string scene, unique_ptr<IScene> newScene)
{
	if (sceneList_.count(scene) == 0)
	{
		sceneList_[scene] = move(newScene);
	}
}

/*==============================================================
// @brief		シーンの変更
// @param		シーン名（string）、シーンインスタンス（unique_ptr<IScene>）
// @return		なし
===============================================================*/
void SceneManager::ChangeScene(string scene, unique_ptr<IScene> newScene)
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
	sceneList_[nowScene_] = move(newScene);

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