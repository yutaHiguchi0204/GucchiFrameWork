/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "GucchiLibrary.h"
#include <cassert>

// TODO: �ǉ������V�[�����C���N���[�h
#include "PlayScene.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�S�V�[�����ʂ̏���������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void IScene::CommonInitialize()
{
	// �J�����ݒ�
	camera_ = make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	// �V���̐���
	skyDome_ = objectFactory_.CreateObjectFromFile(L"skyDome");

	// �I�u�W�F�N�g�̓o�^
	objectRenderer_.RegisterObject(skyDome_.get());		// �V��
}

/*==============================================================
// @brief		�S�V�[�����ʂ̍X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void IScene::CommonUpdate()
{
	// �J�����̍X�V
	camera_->Update();
}

/*==============================================================
// @brief		�S�V�[�����ʂ̕`�揈��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void IScene::CommonDraw()
{

}

/*==============================================================
// @brief		�S�V�[�����ʂ̏I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void IScene::CommonFinalize()
{

}

/*==============================================================
// @brief		���C�u�����C���^�t�F�[�X�̃��Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void IScene::ResetDevice()
{
	// �S�Ẵ��C�u�����C���^�t�F�[�X�����Z�b�g
	objectRenderer_.Reset();
	spriteRenderer_.Reset();
	textRenderer_.Reset();
}

// �R���X�g���N�^
SceneManager::SceneManager()
{
	// �����V�[�����w��
	RegisterScene("PLAY", move(make_unique<PlayScene>()));
	nowScene_ = "PLAY";
	beforeScene_ = "PLAY";
}

/*==============================================================
// @brief		�V�[���̏�����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SceneManager::Initialize()
{
	sceneList_[nowScene_]->Initialize();
}

/*==============================================================
// @brief		�V�[���Ǘ��̍X�V
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SceneManager::Update()
{
	if (beforeScene_ != nowScene_)
	{
		beforeScene_ = nowScene_;
	}

	sceneList_[nowScene_]->Update();
}

/*==============================================================
// @brief		�V�[���̕`��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SceneManager::Draw()
{
	if (CheckScene())
	{
		sceneList_[nowScene_]->Draw();
	}
}

/*==============================================================
// @brief		�V�[���̏I������
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SceneManager::Finalize()
{
	// ���C�u�����C���^�t�F�[�X�̃��Z�b�g
	sceneList_[nowScene_]->ResetDevice();

	sceneList_[nowScene_]->Finalize();
	sceneList_[nowScene_].reset();
}

/*==============================================================
// @brief		�V�[���̓o�^
// @param		�V�[�����istring�j�A�V�[���C���X�^���X
// @return		�Ȃ�
===============================================================*/
void SceneManager::RegisterScene(string scene, unique_ptr<IScene> newScene)
{
	sceneList_[scene] = move(newScene);
}

/*==============================================================
// @brief		�V�[���̕ύX
// @param		�V�[�����istring�j
// @return		�Ȃ�
===============================================================*/
void SceneManager::ChangeScene(string scene)
{
	// �O�t���[���Ɠ����V�[���������ꍇ�͖�������
	if (scene == beforeScene_)
	{
		return;
	}

	// �o�^����Ă���V�[�����`�F�b�N
	if (sceneList_.count(scene) == 0)
	{
		OutputDebugString("This scene is not register. Please register this scene for \"RegisterScene()\"");
		assert(0);
	}

	// ���݂̃V�[���̏I���������s��
	Finalize();

	// �V�[���؂�ւ�
	nowScene_ = scene;

	// �V�����V�[���̏������������s��
	Initialize();
}

/*==============================================================
// @brief		�V�[���`�F�b�N
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
bool SceneManager::CheckScene()
{
	// �O�t���[���ƈقȂ�V�[���̏ꍇ�͕`�悵�Ȃ�
	return nowScene_ == beforeScene_ ? true : false;
}