/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Initialize()
{
	// デフォルトカメラを設定
	camera_ = std::make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	unique_ptr<Object> object = objectFactory_.CreateObjectFromFile(L"skyDome");
	unique_ptr<Object> teaPot = objectFactory_.CreateObjectFromFile(L"teaPot");

	// オブジェクトの登録
	objectRenderer_.RegisterObject(object.get());
	objectRenderer_.RegisterObject(teaPot.get());

	// 2Dテスト
	unique_ptr<Sprite> sprite = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite->SetPos(WINDOW_MIDDLE);
	spriteRenderer_.RegisterSprite(sprite.get());
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Update()
{
	// カメラの更新
	camera_->Update();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Draw()
{
	
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Finalize()
{
	
}