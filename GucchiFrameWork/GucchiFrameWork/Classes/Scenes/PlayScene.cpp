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
	// �f�t�H���g�J������ݒ�
	camera_ = std::make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	unique_ptr<Object> object = objectFactory_.CreateObjectFromFile(L"skyDome");
	teaPot_ = objectFactory_.CreateObjectFromFile(L"teaPot");
	teaPot_->SetTranslate(Vector3(-1.f, 0.f, 0.f));
	teaPot2_ = objectFactory_.CreateObjectFromFile(L"teaPot");
	teaPot2_->SetTranslate(Vector3(-1.f, 0.f, 0.f));
	teaPot2_->SetParent(teaPot_.get());

	// �I�u�W�F�N�g�̓o�^
	objectRenderer_.RegisterObject(object.get());
	objectRenderer_.RegisterObject(teaPot_.get());

	// 2D�e�X�g
	sprite_ = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite_->SetPos(WINDOW_MIDDLE);
	sprite2_ = spriteFactory_.CreateSpriteFromFile(L"cat", DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	sprite2_->SetPos(Vector2(100.0f, 100.0f));
	sprite2_->SetParent(sprite_.get());
	spriteRenderer_.RegisterSprite(sprite_.get());
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