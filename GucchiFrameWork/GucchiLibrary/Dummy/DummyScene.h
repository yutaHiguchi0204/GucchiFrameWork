/* =====================================================================
//! @param		「DummyScene」ヘッダ
//! @create		樋口 裕太
//! @date		17/mm/dd
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"

// クラスの定義
class DummyScene : public GucchiLibrary::IScene
{
private:
	// TODO: DummySceneのメンバ

	// ライブラリインタフェース（複数回使用する際はメンバとして持っといたほうがいいです）

public:
	DummyScene() {};
	virtual ~DummyScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};