/* =====================================================================
//! @param		�uKeyboardUtil�v�\�[�X
//! @create		��� �T��
//! @date		17/11/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "KeyboardUtil.h"

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
void KeyboardUtil::Initialize()
{
	keyboard_ = make_unique<Keyboard>();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void KeyboardUtil::Update()
{
	// �X�e�[�g���̍X�V
	state_ = keyboard_->GetState();
	tracker_.Update(state_);
}