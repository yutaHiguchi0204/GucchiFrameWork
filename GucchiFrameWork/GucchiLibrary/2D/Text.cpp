/* =====================================================================
//! @param		�uText�v�\�[�X
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Text.h"
#include "GucchiLibrary.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

// �R���X�g���N�^
Text::Text(wstring str, Vector2 pos, wstring font, int fontSize, Color color)
	: str_(str)
	, pos_(pos)
	, font_(font)
	, fontSize_(fontSize)
	, color_(color)
{
}

/*==============================================================
// @brief		�t�H���g�̕ύX
// @param		�X�v���C�g�t�H���g�n���h���iwstring�j
//				�����̃X�v���C�g�t�H���g�����Z�b�g����K�v�����邽�߁A�ʓr�������s���܂�
// @return		�Ȃ�
===============================================================*/
void Text::SetFont(const wstring font)
{
	font_ = font;

	// �V�����X�v���C�g�t�H���g��ݒ�
	wstring fontName = FILE_PATH_FONT + font + EXT_SPRITEFONT;

	// ���Z�b�g����
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();
	dxtk.SetFont(font);
}