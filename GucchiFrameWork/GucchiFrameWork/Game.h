/* =====================================================================
//! @param		「Game」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../GucchiLibrary/GucchiLibrary.h"
#include "../GucchiFrameWork/Classes/Master/GameMain.h"

// クラスの定義
class Game : public GucchiLibrary::Framework
{
private:
	std::unique_ptr<GameMain> main_;

public:
    Game(HINSTANCE hInstance, int nCmdShow);

	void Initialize() override;
	void Finalize() override;

private:
    void Update(const GucchiLibrary::StepTimer& timer);
    void Render();
};