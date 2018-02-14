/* =====================================================================
//! @param		�uPrimitive�v�\�[�X
//! @create		��� �T��
//! @date		17/12/23
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Primitive.h"

// ���O���
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Primitive::Primitive()
	: pos_(Vector3::Zero)
	, isFill_(true)
{
}

// �R���X�g���N�^
Primitive2D::Primitive2D()
	: Primitive()
{
}

// �R���X�g���N�^
Primitive3D::Primitive3D()
	: Primitive()
{
}

/*==============================================================
// @brief		�L�[�̎擾
// @param		�Ȃ�
// @return		�S�ẴL�[�ivector<string>�j
===============================================================*/
vector<string> Primitive2D::GetKeys() const
{
	vector<string> keys;

	// �L�[���擾
	for (auto& vertex : vertices_)
	{
		keys.emplace_back(vertex.first);
	}

	return keys;
}