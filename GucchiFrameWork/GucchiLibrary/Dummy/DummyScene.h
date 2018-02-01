/* =====================================================================
//! @param		�uDummyScene�v�w�b�_
//! @create		��� �T��
//! @date		yy/mm/dd
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
	// �R���X�g���N�^
	DummyScene() = default;

	// �f�X�g���N�^
	virtual ~DummyScene() = default;

	/*
	// @method		Initialize
	// @content		����������
	*/
	void Initialize() override;

	/*
	// @method		Update
	// @content		�X�V����
	*/
	void Update() override;

	/*
	// @method		Draw
	// @content		�`�揈��
	*/
	void Draw() override;

	/*
	// @method		Finalize
	// @content		�I������
	*/
	void Finalize() override;
};