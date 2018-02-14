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
	std::unique_ptr<GucchiLibrary::Object> test;
	std::unique_ptr<GucchiLibrary::Primitive> pri;

public:
	PlayScene() = default;
	virtual ~PlayScene() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};