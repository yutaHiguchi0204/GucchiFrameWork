/* =====================================================================
//! @param		�uTextRenderer�v�\�[�X
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TextRenderer.h"
#include <SpriteFont.h>
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// ���O���
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// �����o�֐��̒�`

/*==============================================================
// @brief		�e�L�X�g�̓o�^
// @param		�e�L�X�g���iwstring�j�A������iwstring�j�A�\���ʒu�iVector2�j�A�t�H���g�̐F�iColor�j�A�t�H���g�T�C�Y�ifloat�j�A�t�H���g���i�g���q�������j�iwstring�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::RegisterText(const std::wstring& name, const std::wstring& str, const Vector2& pos, const Color& color, float fontSize, const std::wstring& font)
{
	Text* text = new Text(str, pos);
	
	// �����ݒ�
	text->SetColor(color);
	text->SetFontSize(fontSize);
	text->SetFont(font);

	textList_[name] = text;
}

/*==============================================================
// @brief		�e�L�X�g�̓o�^
// @param		�e�L�X�g���iwstring�j�A�e�L�X�g�iText*�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::RegisterText(const std::wstring& name, Text* text)
{
	if (textList_.count(name))
	{
		textList_[name] = text;
	}
}

/*==============================================================
// @brief		������̕ύX
// @param		�e�L�X�g���iwstring�j�A������iwstring�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetString(const std::wstring& name, const std::wstring& str)
{
	if (textList_.count(name))
	{
		textList_[name]->SetString(str);
	}
}

/*==============================================================
// @brief		�\���ʒu�̕ύX
// @param		�e�L�X�g���iwstring�j�A�\���ʒu�iVector2�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetPos(const std::wstring& name, const Vector2& pos)
{
	if (textList_.count(name))
	{
		textList_[name]->SetPos(pos);
	}
}

/*==============================================================
// @brief		�A���J�[�|�C���g�̕ύX
// @param		�e�L�X�g���iwstring�j�A�A���J�[�|�C���g�iVector2�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetAnchor(const std::wstring& name, const Vector2& anchor)
{
	if (textList_.count(name))
	{
		textList_[name]->SetAnchor(anchor);
	}
}

/*==============================================================
// @brief		�F�̕ύX
// @param		�e�L�X�g���iwstring�j�A�F�iColor�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetColor(const std::wstring& name, const Color& color)
{
	if (textList_.count(name))
	{
		textList_[name]->SetColor(color);
	}
}

/*==============================================================
// @brief		�T�C�Y�̕ύX
// @param		�e�L�X�g���iwstring�j�A�t�H���g�T�C�Y�ifloat�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetFontSize(const std::wstring& name, float fontSize)
{
	if (textList_.count(name))
	{
		textList_[name]->SetFontSize(fontSize);
	}
}

/*==============================================================
// @brief		�t�H���g�̎�ނ̕ύX
// @param		�e�L�X�g���iwstring�j�A�t�H���g�iwstring�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetFont(const std::wstring& name, const std::wstring& font)
{
	if (textList_.count(name))
	{
		textList_[name]->SetFont(font);
	}
}

/*==============================================================
// @brief		�A�N�e�B�u��Ԃ̕ύX
// @param		�e�L�X�g���iwstring�j�A�A�N�e�B�u��ԁibool�j
// @return		�Ȃ�
===============================================================*/
void TextRenderer::SetActive(const std::wstring& name, bool active)
{
	if (textList_.count(name))
	{
		textList_[name]->SetActive(active);
	}
}

/*==============================================================
// @brief		�e�L�X�g�`��
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void TextRenderer::Draw()
{
	DeviceResources& deviceResource = DeviceResources::GetInstance();
	DirectXToolKidResources& dxtk = DirectXToolKidResources::GetInstance();

	// �o�b�`�����J�n
	dxtk.GetSpriteBatch()->Begin(SpriteSortMode::SpriteSortMode_Deferred, deviceResource.GetCommonStates()->NonPremultiplied());

	// �`�揈��
	for (auto text : textList_)
	{
		// �A�N�e�B�u��Ԃ̃X�v���C�g�̂ݕ\��
		if (text.second->GetActive())
		{
			// �A���J�[�|�C���g�̐ݒ�
			Vector2 origin = dxtk.GetSpriteFont()->MeasureString(text.second->GetString().c_str());
			origin *= text.second->GetAnchor();

			// �`��
			dxtk.GetSpriteFont()->DrawString(dxtk.GetSpriteBatch(), text.second->GetString().c_str(), text.second->GetPos(), text.second->GetColor(), 0.f, origin, text.second->GetFontSize() / Text::DEFAULT_FONT_SIZE);
		}
	}

	// �o�b�`�����I��
	dxtk.GetSpriteBatch()->End();
}

/*==============================================================
// @brief		���X�g���Z�b�g
// @param		�Ȃ�
// @return		�Ȃ�
===============================================================*/
void TextRenderer::Reset()
{
	for (auto& text : textList_)
	{
		delete text.second;
	}

	textList_.clear();
}