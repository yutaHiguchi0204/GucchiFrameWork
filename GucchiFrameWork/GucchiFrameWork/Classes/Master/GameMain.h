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
	std::unique_ptr<GucchiLibrary::Sprite> test_;

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// ����������
	void Update();				// �X�V����
	void Render();				// �`�揈��
	void Finalize();			// �I������
};