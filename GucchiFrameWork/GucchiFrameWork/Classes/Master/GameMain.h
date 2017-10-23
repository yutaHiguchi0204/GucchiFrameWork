/* =====================================================================
//! @param		�uGameMain�v�w�b�_
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GucchiLibrary.h"

// �N���X�̒�`
class GameMain
{
private:
	// TODO: �����ɐV�����ǉ�
	std::unique_ptr<GucchiLibrary::Sprite> test_;

private:
	// ���C�u�����C���^�t�F�[�X
	GucchiLibrary::SpriteFactory& factory_ = GucchiLibrary::SpriteFactory::GetInstance();			// �X�v���C�g�����p
	GucchiLibrary::SpriteRenderer& renderer_ = GucchiLibrary::SpriteRenderer::GetInstance();		// �X�v���C�g�`��p

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// ����������
	void Update();				// �X�V����
	void Render();				// �`�揈��
	void Finalize();			// �I������
};