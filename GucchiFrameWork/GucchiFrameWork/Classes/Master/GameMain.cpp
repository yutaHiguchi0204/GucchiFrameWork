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
	// �����V�[����ݒ�
	SceneManager& sceneManager = SceneManager::GetInstance();
	scene_ = sceneManager.ChangeScene(SceneManager::PLAY);

	// TODO: �Q�[���֘A�̏�����
	scene_->Initialize();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Update()
{
	// �V�[���Ǘ��̍X�V�i�O�t���[���X�V�j
	sceneManager_.Update();

	// TODO: �Q�[���֘A�̍X�V
	scene_->Update();
}

/*==============================================================
// @brief		�`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Draw()
{
	// TODO: �Q�[���֘A�̕`��
	if (sceneManager_.CheckScene())
	{
		scene_->Draw();
	}
}

/*==============================================================
// @brief		�I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void GameMain::Finalize()
{
	// TODO: �Q�[���֘A�̏I������
	scene_->Finalize();
}