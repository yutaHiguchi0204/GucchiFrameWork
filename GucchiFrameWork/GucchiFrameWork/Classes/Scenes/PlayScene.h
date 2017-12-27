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
	std::unique_ptr<GucchiLibrary::Sprite> spr_;
	std::unique_ptr<GucchiLibrary::Text> t_;

	std::unique_ptr<GucchiLibrary::Primitive> point_;
	std::unique_ptr<GucchiLibrary::Primitive> triangle_;

	std::unique_ptr<GucchiLibrary::Emitter> emitter_;

public:
	PlayScene() {}
	virtual ~PlayScene() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};