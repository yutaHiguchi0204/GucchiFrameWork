/* =====================================================================
//! @param		�uDummyScene�v�w�b�_
//! @create		��� �T��
//! @date		17/mm/dd
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "GucchiLibrary.h"

// �N���X�̒�`
class DummyScene : public GucchiLibrary::IScene
{
private:
	// TODO: DummyScene�̃����o

	// ���C�u�����C���^�t�F�[�X�i������g�p����ۂ̓����o�Ƃ��Ď����Ƃ����ق��������ł��j

public:
	DummyScene() {};
	virtual ~DummyScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};