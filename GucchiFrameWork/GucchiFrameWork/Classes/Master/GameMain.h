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
	std::unique_ptr<GucchiLibrary::Sprite> test_;

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// 初期化処理
	void Update();				// 更新処理
	void Render();				// 描画処理
	void Finalize();			// 終了処理
};