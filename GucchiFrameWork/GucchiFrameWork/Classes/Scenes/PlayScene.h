/* =====================================================================
//! @param		「PlayScene」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"

// クラスの定義
class PlayScene : public GucchiLibrary::IScene
{
private:
	// TODO: PlaySceneのメンバ
	std::unique_ptr<GucchiLibrary::Object> teaPot_;
	std::unique_ptr<GucchiLibrary::Object> teaPot2_;

	std::unique_ptr<GucchiLibrary::Sprite> sprite_;
	std::unique_ptr<GucchiLibrary::Sprite> sprite2_;

public:
	PlayScene() {}
	virtual ~PlayScene() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};