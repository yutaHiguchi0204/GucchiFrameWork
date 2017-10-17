/* =====================================================================
//! @param		�uSprite�v�\�[�X
//! @create		��� �T��
//! @date		17/10/17
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Sprite.h"
#include <WICTextureLoader.h>
#include "../Common/Constant.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// �����o�֐��̒�`

// �R���X�g���N�^
Sprite::Sprite()
	: texture_(nullptr)
	, pos_(Vector2(0.0f, 0.0f))
	, scale_(1.0f)
	, angle_(0.0f)
	, isActive_(true)
{
}

/*==============================================================
// @brief		����������
// @param		�ʒu�iVector2�j�A�g�嗦�ifloat�j�A��]�p�ifloat�j
// @return		�Ȃ�
===============================================================*/
void Sprite::Initialize(const Vector2& pos, float scale, float angle)
{
	pos_ = pos;
	scale_ = scale;
	angle_ = angle;
}