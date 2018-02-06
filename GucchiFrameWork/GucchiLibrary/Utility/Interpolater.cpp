/* =====================================================================
//! @param		�uInterpolater�v�\�[�X�i��ԃ��C�u�����j
//! @create		��� �T��
//! @date		17/11/09
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Interpolater.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
InterpolateDirector::InterpolateDirector()
{
	// ���̉�
	stateF_ = make_unique<InterpolateState<float>>();
	stateV2_ = make_unique<InterpolateState<Vector2>>();
	stateV3_ = make_unique<InterpolateState<Vector3>>();
	stateV4_ = make_unique<InterpolateState<Vector4>>();
}

/*==============================================================
// @brief		�X�V����
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void InterpolateDirector::Update()
{
	stateF_->Update();
	stateV2_->Update();
	stateV3_->Update();
	stateV4_->Update();
}

/*==============================================================
// @brief		���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void InterpolateDirector::Reset()
{
	stateF_->Reset();
	stateV2_->Reset();
	stateV3_->Reset();
	stateV4_->Reset();
}