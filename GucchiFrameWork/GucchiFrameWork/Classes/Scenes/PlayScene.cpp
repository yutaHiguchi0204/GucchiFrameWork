/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

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
	test->SetTranslate(Vector3(0, -1.5f, 0));
	objectRenderer_.RegisterObject(test.get());

	test->AddComponent<SphereCollider>();

	textRenderer_.RegisterText(L"test", L"component: true", Vector2(0, 0));
	textRenderer_.RegisterText(L"test2", L"collider view: true", Vector2(0, 32));
	textRenderer_.SetAnchor(L"test", ANCHOR_LT);
	textRenderer_.SetAnchor(L"test2", ANCHOR_LT);
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
 		test->RemoveComponent<SphereCollider>();
		textRenderer_.SetString(L"test", L"component: false");
	}
	else if (keyboard.GetTracker().IsKeyPressed(Keyboard::Keys::V))
	{
		auto component = test->GetComponent<SphereCollider>();

		if (component)
		{
			bool active = component->GetPrimitiveActive();
			component->SetPrimitiveActive(!active);
			textRenderer_.SetString(L"test2", L"collider view: false");
		}
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