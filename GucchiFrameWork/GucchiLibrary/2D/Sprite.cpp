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
Sprite::Sprite(const Vector2& size)
	: texture_(nullptr)
	, size_(size)
	, textureRect_(nullptr)
	, angle_(0.0f)
	, isActive_(true)
{
}

/*==============================================================
// @brief		�����������i�ʒu�ƃX�v���C�g�T�C�Y�̐ݒ�����邽�߂ɕK���Ă�ł��������j
// @param		�ʒu�iVector2�j�A�摜��`�iRECT*�j�A�g�嗦�ifloat�j�A��]�p�ifloat�j
// @return		�Ȃ�
===============================================================*/
void Sprite::Initialize(const Vector2& pos, RECT* rect, float scale, float angle)
{
	pos_ = pos;
	textureRect_ = rect;
	scale_ = scale;
	angle_ = angle;
}