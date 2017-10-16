/* =====================================================================
//! @param		�uGame�v�w�b�_
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../GucchiLibrary/GucchiLibrary.h"
#include "../GucchiFrameWork/Classes/Master/GameMain.h"

// �N���X�̒�`
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