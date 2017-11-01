/* =====================================================================
//! @param		�uGame�v�\�[�X
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Game.h"

// ���O���
using namespace DirectX;
using Microsoft::WRL::ComPtr;
using namespace GucchiLibrary;
using namespace std;

extern void ExitGame();

// �R���X�g���N�^
Game::Game(HINSTANCE hInstance, int nCmdShow)
	: Framework(hInstance, nCmdShow)
{
	// �Q�[�����C������
	main_ = make_unique<GameMain>();
}

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Game::Initialize()
{
	// �f�o�C�X�֘A�Ȃǂ̏������͂����ɋL�q

	// ���̑��Q�[�����֘A��GameMain�̏������ɏ����Ă��������i��{�I�ɂ����͂�����Ȃ��j
	main_->Initialize();
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Game::Finalize()
{
	// �f�o�C�X�֘A�Ȃǂ̏I�������͂����ɋL�q

	// �Q�[�����֘A�̏I��������GameMain�̏I�������ɏ����Ă��������i��{�I�ɂ����͂�����Ȃ��j
	main_->Finalize();
}

/*==============================================================
// @brief		�X�V����
// @param		���ԏ����iStepTimer�j
// @return		�Ȃ�
===============================================================*/
void Game::Update(const StepTimer& timer)
{
	// �f�o�C�X�֘A�Ȃǂ̍X�V�͂����ɋL�q

	// �Q�[�����֘A�̍X�V������GameMain�̍X�V�ɏ����Ă��������i��{�I�ɂ����͂�����Ȃ��j
	main_->Update();
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void Game::Render()
{
	// �f�o�C�X�֘A�Ȃǂ̕`��͂����ɋL�q

	// ���C�u�����C���^�t�F�[�X�ł̕`�揈��
	spriteRenderer_.Draw();				// �X�v���C�g
	textRenderer_.Draw();				// �e�L�X�g

    // �Q�[�����֘A�̕`�揈����GameMain�̕`��ɏ����Ă��������i��{�I�ɂ����͂�����Ȃ��j
	main_->Draw();
}