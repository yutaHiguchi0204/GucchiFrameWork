/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
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
	teaPot_ = objectFactory_.CreateObjectFromFile(L"teaPot");
	teaPot_->SetTranslate(Vector3(-1.f, 0.f, 0.f));
	teaPot2_ = objectFactory_.CreateObjectFromFile(L"teaPot");
	teaPot2_->SetTranslate(Vector3(-1.f, 0.f, 0.f));
	teaPot2_->SetParent(teaPot_.get());

	// オブジェクトの登録
	objectRenderer_.RegisterObject(object.get());
	objectRenderer_.RegisterObject(teaPot_.get());

	// 2Dテスト
	sprite_ = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite_->SetPos(WINDOW_MIDDLE);
	sprite2_ = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite2_->SetPos(Vector2(100.0f, 100.0f));
	sprite2_->SetParent(sprite_.get());
	spriteRenderer_.RegisterSprite(sprite_.get());
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