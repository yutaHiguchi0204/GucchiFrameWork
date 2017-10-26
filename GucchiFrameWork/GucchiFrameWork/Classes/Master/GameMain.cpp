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
	// ライブラリインタフェースの初期化
	renderer_ = make_unique<SpriteRenderer>();

	// TODO: ゲーム関連の初期化

	// スプライト画像の読み込み
	test_ = factory_.CreateSpriteFromFile(L"cat", Vector2(100.0f));
	test_->Initialize(WINDOW_MIDDLE);
	test2_ = factory_.CreateSpriteFromFile(L"cat", Vector2(100.0f));
	test2_->Initialize(WINDOW_MIDDLE);
	test2_->SetAngle(XMConvertToRadians(180.0f));

	// 登録
	renderer_->RegisterSprite(test_.get());
	renderer_->RegisterSprite(test2_.get(), 0);
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Update()
{
	// TODO: ゲーム関連の更新

	StepTimer& timer = StepTimer::GetInstance();
	if (timer.GetFrameCount() > 120)
	{
		renderer_->SetOrder(test2_.get(), 1);
	}
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void GameMain::Render()
{
	// 登録されたスプライトの描画
	renderer_->Draw();

	// TODO: ゲーム関連の描画
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