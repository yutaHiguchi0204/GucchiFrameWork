/* =====================================================================
//! @param		「GameMain」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"

// クラスの定義
class GameMain
{
private:
	// ライブラリインタフェース
	GucchiLibrary::SceneManager& sceneManager_ = GucchiLibrary::SceneManager::GetInstance();

public:
	GameMain() = default;
	virtual ~GameMain() = default;

	void Initialize();			// 初期化処理
	void Update();				// 更新処理
	void Draw();				// 描画処理
	void Finalize();			// 終了処理
};