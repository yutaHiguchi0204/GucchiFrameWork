/* =====================================================================
//! @param		�uSceneManager�v�\�[�X
//! @create		��� �T��
//! @date		17/10/30
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "PlayScene.h"

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
	test->SetTranslate(Vector3(0, -1.5f, 0));
	objectRenderer_.RegisterObject(test.get());

	test->AddComponent<SphereCollider>();

	textRenderer_.RegisterText(L"test", L"component: true", Vector2(0, 0));
	textRenderer_.RegisterText(L"test2", L"collider view: true", Vector2(0, 32));
	textRenderer_.SetAnchor(L"test", ANCHOR_LT);
	textRenderer_.SetAnchor(L"test2", ANCHOR_LT);
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
 		test->RemoveComponent<SphereCollider>();
		textRenderer_.SetString(L"test", L"component: false");
	}
	else if (keyboard.GetTracker().IsKeyPressed(Keyboard::Keys::V))
	{
		auto component = test->GetComponent<SphereCollider>();

		if (component)
		{
			bool active = component->GetPrimitiveActive();
			component->SetPrimitiveActive(!active);
			textRenderer_.SetString(L"test2", L"collider view: false");
		}
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