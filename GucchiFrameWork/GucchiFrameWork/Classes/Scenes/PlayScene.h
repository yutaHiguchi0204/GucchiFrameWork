/* =====================================================================
//! @param		�uPlayScene�v�w�b�_
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GucchiLibrary.h"

// �N���X�̒�`
class PlayScene : public GucchiLibrary::IScene
{
private:
	// TODO: PlayScene�̃����o

public:
	PlayScene() {};
	virtual ~PlayScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};