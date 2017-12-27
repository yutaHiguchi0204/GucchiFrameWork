/* =====================================================================
//! @param		�uGame�v�w�b�_
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Classes/Master/GameMain.h"

// �N���X�̒�`
class Game : public GucchiLibrary::Framework
{
private:
	std::unique_ptr<GameMain> main_;

	// ���C�u�����C���^�t�F�[�X
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