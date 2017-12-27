/* =====================================================================
//! @param		「Game」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Classes/Master/GameMain.h"

// クラスの定義
class Game : public GucchiLibrary::Framework
{
private:
	std::unique_ptr<GameMain> main_;

	// ライブラリインタフェース
	GucchiLibrary::ObjectRenderer&		objectRenderer_		= GucchiLibrary::ObjectRenderer::GetInstance();
	GucchiLibrary::ParticleRenderer&	particleRenderer_	= GucchiLibrary::ParticleRenderer::GetInstance();
	GucchiLibrary::SpriteRenderer&		spriteRenderer_		= GucchiLibrary::SpriteRenderer::GetInstance();
	GucchiLibrary::PrimitiveRenderer&	primitiveRenderer_	= GucchiLibrary::PrimitiveRenderer::GetInstance();
	GucchiLibrary::TextRenderer&		textRenderer_		= GucchiLibrary::TextRenderer::GetInstance();

public:
    Game(HINSTANCE hInstance, int nCmdShow);

	void Initialize() override;
	void Finalize() override;

private:
    void Update(const GucchiLibrary::StepTimer& timer);
    void Render();
};