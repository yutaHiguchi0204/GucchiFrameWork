/* =====================================================================
//! @param		�uGameMain�v�\�[�X
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameMain.h"

// ���O���
using namespace GucchiLibrary;

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Initialize()
{
	// TODO: �Q�[���֘A�̏�����
	SpriteFactory& factory = SpriteFactory::GetInstance();
	//test_ = factory.CreateSpriteFromFile(L"cat");

	// �o�^
	SpriteRenderer& render = SpriteRenderer::GetInstance();
	//render.RegisterSprite(test_.get());
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Update()
{
	// TODO: �Q�[���֘A�̍X�V
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Render()
{
	// TODO: �Q�[���֘A�̕`��
	SpriteRenderer& render = SpriteRenderer::GetInstance();
	//render.Draw();
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Finalize()
{
	// TODO: �Q�[���֘A�̏I������
}