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
Sprite::Sprite(const Vector2& size, const Vector2& pos, RECT* rect, float scale, float angle)
	: texture_(nullptr)
	, size_(size)
	, pos_(pos)
	, textureRect_(nullptr)
	, scale_(scale)
	, angle_(angle)
	, isActive_(true)
{
}