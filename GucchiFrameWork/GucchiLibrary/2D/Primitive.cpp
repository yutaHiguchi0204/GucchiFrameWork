/* =====================================================================
//! @param		�uPrimitive�v�\�[�X
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Primitive.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Primitive::Primitive()
	: isFill_(true)
{
}

/*==============================================================
// @brief		�v���~�e�B�u�쐬�i���j
// @param		�n�_�iVector2�j�A�I�_�iVector2�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void Primitive::Entry(const Vector2& start, const Vector2& end, const Color& color)
{
	point_["start"] = start;
	point_["end"] = end;
	color_ = color;

	// �^�C�v����ɐݒ�
	type_ = PRIMITIVE_TYPE::LINE;
}

/*==============================================================
// @brief		�v���~�e�B�u�쐬�i�O�p�j
// @param		�h��Ԃ����ǂ����ibool�j�A�P�_�ځiVector2�j�A�Q�_�ځiVector2�j�A�R�_�ځiVector2�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& _p1, const Vector2& _p2, const Vector2& _p3, const Color& color)
{
	point_["p1"] = _p1;
	point_["p2"] = _p2;
	point_["p3"] = _p3;
	color_ = color;

	// �^�C�v���O�p�ɐݒ�
	type_ = PRIMITIVE_TYPE::TRIANGLE;

	// �h��Ԃ����ǂ���
	isFill_ = fillFlag;
}

/*==============================================================
// @brief		�v���~�e�B�u�쐬�i�l�p�j
// @param		�h��Ԃ����ǂ����ibool�j�A����̍��W�iVector2�j�A�E���̍��W�iVector2�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& topLeft, const Vector2& bottomRight, const Color& color)
{
	point_["topLeft"] = topLeft;
	point_["topRight"] = Vector2(bottomRight.x, topLeft.y);
	point_["bottomLeft"] = Vector2(topLeft.x, bottomRight.y);
	point_["bottomRight"] = bottomRight;
	color_ = color;

	// �^�C�v���l�p�ɐݒ�
	type_ = PRIMITIVE_TYPE::SQUARE;

	// �h��Ԃ����ǂ���
	isFill_ = fillFlag;
}

/*==============================================================
// @brief		�v���~�e�B�u�쐬�i�~�j
// @param		�h��Ԃ����ǂ����ibool�j�A���S���W�iVector2�j�A���a�ifloat�j�A�������iint�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& center, float radius, int div, const Color& color)
{
	// �|�C���g�̂P�ԖڂƂQ�Ԗڂ��f�[�^�ۑ��p�Ƃ���
	point_["center"] = center;
	point_["rad&div"].x = radius;
	point_["rad&div"].y = (float)div;

	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i);
		point_[key].x = center.x + cosf(XM_2PI / div * i) * radius;
		point_[key].y = center.y + sinf(XM_2PI / div * i) * radius;
	}

	color_ = color;

	// �^�C�v���l�p�ɐݒ�
	type_ = PRIMITIVE_TYPE::CIRCLE;

	// �h��Ԃ����ǂ���
	isFill_ = fillFlag;
}