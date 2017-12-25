/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		����������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Initialize()
{
	// �S�V�[�����ʏ���������
	IScene::CommonInitialize();

	spr_ = spriteFactory_.CreateSpriteFromFile(L"cat", Vector2(100.0f, 100.0f));
	spr_->SetPos(WINDOW_MIDDLE);
	spriteRenderer_.RegisterSprite(spr_.get());

	t_ = make_unique<Text>(L"�Ă���", WINDOW_MIDDLE);
	t_->SetAnchor(ANCHOR_MM);
	textRenderer_.RegisterText(t_.get());

	square_ = make_unique<Primitive>();
	square_->Entry(Vector2(100.0f, 100.0f), Vector2(400.0f, 400.0f), Color(0, 0, 0));
	primitiveRenderer_.RegisterPrimitive(square_.get());
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Update()
{
	// �S�V�[�����ʍX�V����
	IScene::CommonUpdate();
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Draw()
{
	// �S�V�[�����ʕ`�揈��
	IScene::CommonDraw();
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Finalize()
{
	// �S�V�[�����ʏI������
	IScene::CommonFinalize();
}