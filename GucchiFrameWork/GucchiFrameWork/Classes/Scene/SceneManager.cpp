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

// コンストラクタ
SceneManager::SceneManager()
	: nowScene_(PLAY)
	, beforeFrameScene_(PLAY)
{
}

/*==============================================================
// @brief		シーンの変更
// @param		シーン（SCENE）
// @return		シーンインスタンス（unique_ptr<IScene>）
===============================================================*/
unique_ptr<IScene> SceneManager::ChangeScene(SCENE scene)
{
	// 前フレームと同じシーンだった場合は無視する
	//if (scene == beforeFrameScene_)
	//{
	//	return;
	//}

	switch (scene)
	{
	case PLAY:
		nowScene_ = PLAY;
		return std::move(make_unique<PlayScene>());
		break;

	default:
		OutputDebugString("This scene is not found.");
		assert(0);
		break;
	}

	// 警告無視用（ここに入ることはないです）
	return nullptr;
}

/*==============================================================
// @brief		シーン管理の更新
// @param		なし
// @return		なし
===============================================================*/
void SceneManager::Update()
{
	if (beforeFrameScene_ != nowScene_)
	{
		beforeFrameScene_ = nowScene_;
	}
}

/*==============================================================
// @brief		シーンチェック
// @param		なし
// @return		なし
===============================================================*/
bool SceneManager::CheckScene()
{
	// 前フレームと異なるシーンの場合は描画しない
	return nowScene_ == beforeFrameScene_ ? true : false;
}