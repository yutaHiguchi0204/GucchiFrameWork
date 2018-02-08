/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"
#include "InputTools/KeyboardUtil.h"

// ���O���
using namespace DirectX;
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

	// TODO: ���̃V�[���̏���������
	test = objectFactory_.CreateObjectFromFile(L"bomb");
	objectRenderer_.RegisterObject(test.get());

	test->AddComponent<AABB>();

	textRenderer_.RegisterText(L"test", L"component: true", Vector2(0, 0));
	textRenderer_.SetAnchor(L"test", ANCHOR_LT);
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

	// TODO: ���̃V�[���̍X�V����

	KeyboardUtil& keyboard = KeyboardUtil::GetInstance();
	if (keyboard.GetTracker().IsKeyPressed(Keyboard::Keys::Space))
	{
		test->RemoveComponent<AABB>();
		textRenderer_.SetString(L"test", L"component: false");
	}
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

	// TODO: ���̃V�[���̕`�揈��
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

	// TODO: ���̃V�[���̏I������
}