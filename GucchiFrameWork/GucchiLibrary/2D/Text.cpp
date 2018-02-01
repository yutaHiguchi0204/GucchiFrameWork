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
using namespace GucchiLibrary;
using namespace std;

// �ÓI�����o�̒�`
const float Text::DEFAULT_FONT_SIZE = 18.0f;		// �t�H���g�T�C�Y�̏����ݒ�i�t�H���g��V�K�ō쐬����ۂ́A�t�H���g�T�C�Y��"18"�ō���Ă��������j

// �����o�֐��̒�`

// �R���X�g���N�^
Text::Text(wstring str, const Vector2& pos, wstring font, int fontSize, const Color& color)
	: str_(str)
	, pos_(pos)
	, anchor_(ANCHOR_LM)
	, font_(font)
	, fontSize_(fontSize)
	, color_(color)
	, isActive_(true)
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