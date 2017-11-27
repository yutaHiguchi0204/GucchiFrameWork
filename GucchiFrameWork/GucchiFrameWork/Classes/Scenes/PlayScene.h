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