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
	std::unique_ptr<GucchiLibrary::Text> text_;

private:
	// ���C�u�����C���^�t�F�[�X
	GucchiLibrary::SpriteRenderer&	spriteRenderer_		= GucchiLibrary::SpriteRenderer::GetInstance();		// �X�v���C�g�`��p�i�`�悵�����X�v���C�g�������_���[�ɓo�^���Ă��������j
	GucchiLibrary::SpriteFactory&	factory_			= GucchiLibrary::SpriteFactory::GetInstance();		// �X�v���C�g�����p�i�X�v���C�g�𐶐�����ۂɎg�p���Ă��������A�摜�̎g���܂킵�j
	GucchiLibrary::TextRenderer&	textRenderer_		= GucchiLibrary::TextRenderer::GetInstance();		// �e�L�X�g�`��p�i�`�悵���������������_���[�ɓo�^���Ă��������j
	GucchiLibrary::StepTimer&		timer_				= GucchiLibrary::StepTimer::GetInstance();			// �o�ߎ��ԓ��^�C�}�[�p

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// ����������
	void Update();				// �X�V����
	void Render();				// �`�揈��
	void Finalize();			// �I������
};