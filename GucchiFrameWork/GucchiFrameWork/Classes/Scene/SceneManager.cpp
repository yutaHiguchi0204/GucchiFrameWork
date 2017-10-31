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

// �R���X�g���N�^
SceneManager::SceneManager()
	: nowScene_(PLAY)
	, beforeFrameScene_(PLAY)
{
}

/*==============================================================
// @brief		�V�[���̕ύX
// @param		�V�[���iSCENE�j
// @return		�V�[���C���X�^���X�iunique_ptr<IScene>�j
===============================================================*/
unique_ptr<IScene> SceneManager::ChangeScene(SCENE scene)
{
	// �O�t���[���Ɠ����V�[���������ꍇ�͖�������
	//if (scene == beforeFrameScene_)
	//{
	//	return;
	//}

	switch (scene)
	{
	case PLAY:
		nowScene_ = PLAY;
		return std::move(make_unique<PlayScene>());
		break;

	default:
		OutputDebugString("This scene is not found.");
		assert(0);
		break;
	}

	// �x�������p�i�����ɓ��邱�Ƃ͂Ȃ��ł��j
	return nullptr;
}

/*==============================================================
// @brief		�V�[���Ǘ��̍X�V
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void SceneManager::Update()
{
	if (beforeFrameScene_ != nowScene_)
	{
		beforeFrameScene_ = nowScene_;
	}
}

/*==============================================================
// @brief		�V�[���`�F�b�N
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
bool SceneManager::CheckScene()
{
	// �O�t���[���ƈقȂ�V�[���̏ꍇ�͕`�悵�Ȃ�
	return nowScene_ == beforeFrameScene_ ? true : false;
}