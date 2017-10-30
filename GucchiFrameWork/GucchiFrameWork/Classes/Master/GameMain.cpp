/* =====================================================================
//! @param		�uGameMain�v�\�[�X
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "GameMain.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Initialize()
{
	// TODO: �Q�[���֘A�̏�����
	text_ = make_unique<Text>(L"Hello World!", WINDOW_MIDDLE);

	// �e�L�X�g�o�^
	textRenderer_.RegisterText(text_.get());
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

	// ���C�u�����C���^�t�F�[�X��p�����`��
	spriteRenderer_.Draw();				// �X�v���C�g
	textRenderer_.Draw();				// �e�L�X�g
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