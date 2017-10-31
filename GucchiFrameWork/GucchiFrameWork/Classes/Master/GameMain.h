/* =====================================================================
//! @param		�uGameMain�v�w�b�_
//! @create		��� �T��
//! @date		17/10/12
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GucchiLibrary.h"

// �N���X�̒�`
class GameMain
{
private:
	// �V�[���Ǘ�
	std::unique_ptr<GucchiLibrary::IScene> scene_;

	// ���C�u�����C���^�t�F�[�X
	GucchiLibrary::SceneManager& sceneManager_ = GucchiLibrary::SceneManager::GetInstance();

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// ����������
	void Update();				// �X�V����
	void Draw();				// �`�揈��
	void Finalize();			// �I������
};