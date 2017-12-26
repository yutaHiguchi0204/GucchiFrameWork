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
	// 全シーン共通初期化処理
	IScene::CommonInitialize();

	spr_ = spriteFactory_.CreateSpriteFromFile(L"cat", Vector2(100.0f, 100.0f));
	spr_->SetPos(WINDOW_MIDDLE);
	spriteRenderer_.RegisterSprite(spr_.get());

	t_ = make_unique<Text>(L"てすと", WINDOW_MIDDLE);
	t_->SetAnchor(ANCHOR_MM);
	textRenderer_.RegisterText(t_.get());

	triangle_ = make_unique<Primitive>();
	triangle_->Entry(false, Vector2(400.0f, 100.0f), Vector2(200.0f, 400.0f), Vector2(600.0f, 400.0f), Color(0, 1, 1));
	primitiveRenderer_.RegisterPrimitive(triangle_.get());

	list<string> str = triangle_->GetKeys();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Update()
{
	// 全シーン共通更新処理
	IScene::CommonUpdate();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Draw()
{
	// 全シーン共通描画処理
	IScene::CommonDraw();
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Finalize()
{
	// 全シーン共通終了処理
	IScene::CommonFinalize();
}