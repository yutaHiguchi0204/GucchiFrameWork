/* =====================================================================
//! @param		�uObject�v�\�[�X
//! @create		��� �T��
//! @date		17/11/15
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Object.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
{
}