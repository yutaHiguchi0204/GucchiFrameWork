/* =====================================================================
//! @param		�uAction�v�\�[�X�i�ړ��֌W���C�u�����j
//! @create		��� �T��
//! @date		17/12/02
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Action.h"
#include "../Utility/Interpolater.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// �����o�֐��̒�`

/*==============================================================
// @brief		���`�ړ��i��Έړ��j
// @param		�X�v���C�g�iSprite*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector2�j
// @return		�Ȃ�
===============================================================*/
void MoveTo::Action(Sprite* sprite, float time, const Vector2& distance)
{
	// ���݂̈ʒu
	Vector2 pos = sprite->GetPos();

	// ���`��Ԃňړ����s��
	
}

/*==============================================================
// @brief		���`�ړ��i��Έړ��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector3�j
// @return		�Ȃ�
===============================================================*/
void MoveTo::Action(Object* object, float time, const Vector3& pos)
{

}

/*==============================================================
// @brief		���`�ړ��i���Έړ��j
// @param		�X�v���C�g�iSprite*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector2�j
// @return		�Ȃ�
===============================================================*/
void MoveBy::Action(Sprite* sprite, float time, const Vector2& distance)
{

}

/*==============================================================
// @brief		���`�ړ��i���Έړ��j
// @param		�I�u�W�F�N�g�iObject*�j�A�ړ��ɂ����鎞�ԁifloat�j�A�ړ������iVector3�j
// @return		�Ȃ�
===============================================================*/
void MoveBy::Action(Object* object, float time, const Vector3& distance)
{

}