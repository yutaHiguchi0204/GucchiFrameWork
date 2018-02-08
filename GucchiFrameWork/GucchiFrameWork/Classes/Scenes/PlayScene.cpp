/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"
#include "InputTools/KeyboardUtil.h"

// 名前空間
using namespace DirectX;
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

	// TODO: このシーンの初期化処理
	test = objectFactory_.CreateObjectFromFile(L"bomb");
	objectRenderer_.RegisterObject(test.get());

	test->AddComponent<AABB>();

	textRenderer_.RegisterText(L"test", L"component: true", Vector2(0, 0));
	textRenderer_.SetAnchor(L"test", ANCHOR_LT);
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

	// TODO: このシーンの更新処理

	KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
	if (keyboard.GetTracker().IsKeyPressed(Keyboard::Keys::Space))
	{
		test->RemoveComponent<AABB>();
		textRenderer_.SetString(L"test", L"component: false");
	}
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

	// TODO: このシーンの描画処理
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

	// TODO: このシーンの終了処理
}