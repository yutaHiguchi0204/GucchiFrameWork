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

	// �X�v���C�g�摜�̓ǂݍ���
	test_ = factory_.CreateSpriteFromFile(L"cat");
	test_->Initialize(WINDOW_MIDDLE(test_->GetSize().x, test_->GetSize().y), Vector2(100.0f));

	// �o�^
	renderer_.RegisterSprite(test_.get());
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
	// �o�^���ꂽ�X�v���C�g�̕`��
	renderer_.Draw();

	// TODO: �Q�[���֘A�̕`��
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