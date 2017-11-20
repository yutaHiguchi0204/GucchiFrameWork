/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"

// ���O���
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
	// �f�t�H���g�J������ݒ�
	camera_ = std::make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	unique_ptr<Object> object = objectFactory_.CreateObjectFromFile(L"skyDome");
	unique_ptr<Object> teaPot = objectFactory_.CreateObjectFromFile(L"teaPot");

	// �I�u�W�F�N�g�̓o�^
	objectRenderer_.RegisterObject(object.get());
	objectRenderer_.RegisterObject(teaPot.get());

	// 2D�e�X�g
	unique_ptr<Sprite> sprite = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite->SetPos(WINDOW_MIDDLE);
	spriteRenderer_.RegisterSprite(sprite.get());
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Update()
{
	// �J�����̍X�V
	camera_->Update();
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Draw()
{
	
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void PlayScene::Finalize()
{
	
}