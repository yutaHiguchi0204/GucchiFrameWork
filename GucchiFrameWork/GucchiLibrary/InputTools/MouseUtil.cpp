/* =====================================================================
//! @param		�uMouseUtil�v�\�[�X
//! @create		��� �T��
//! @date		17/11/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "MouseUtil.h"

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
void MouseUtil::Initialize()
{
	mouse_ = make_unique<Mouse>();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void MouseUtil::Update()
{
	// �X�e�[�g���̍X�V
	state_ = mouse_->GetState();
	tracker_.Update(state_);
}