/* =====================================================================
//! @param		�uTextRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <map>
#include "../Common/SingletonDirector.h"
#include "Text.h"

namespace GucchiLibrary
{
	/*
	// @class		TextRenderer �N���X�iSingleton�j
	// @content		�e�L�X�g�Ǘ��p
	// @use			RegisterText�֐��ɂ���ēo�^���ꂽ�e�L�X�g��`�悷��
	// @use			�V�[���J�ڎ��Ȃǂ�Reset�֐����ĂԂ��Ƃœo�^�����e�L�X�g���������
	*/
	class TextRenderer : public SingletonDirector<TextRenderer>
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Color = DirectX::SimpleMath::Color;

	private:
		std::map<std::wstring, Text*> textList_;

	private:
		friend class SingletonDirector<TextRenderer>;

		TextRenderer() = default;

	public:
		/*
		// @method		RegisterText
		// @content		�e�L�X�g�̓o�^
		// @param		�e�L�X�g���iwstring�j
		// @param		������iwstring�j
		// @param		�\���ʒu�iVector2�j
		// @param		�t�H���g�̐F�iColor�j�@�F�@�f�t�H���g�iColor(1, 1, 1)�j
		// @param		�t�H���g�T�C�Y�ifloat�j�@�F�@�f�t�H���g�iDEFAULT_FONT_SIZE�j
		// @param		�t�H���g���i�g���q�������j�iwstring�j�@�F�@�f�t�H���g�iL"default_font"�j
		*/
		void RegisterText(const std::wstring& name, const std::wstring& str, const Vector2& pos, const Color& color = Color(1, 1, 1), float fontSize = Text::DEFAULT_FONT_SIZE, const std::wstring& font = Text::DEFAULT_FONT);

		/*
		// @method		RegisterText
		// @content		�e�L�X�g�̓o�^
		// @param		�e�L�X�g���iwstring�j
		// @param		�o�^����e�L�X�g�iText*�j
		*/
		void RegisterText(const std::wstring& name, Text* text);

		/*
		// @method		SetString
		// @content		������̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		������iwstring�j
		*/
		void SetString(const std::wstring& name, const std::wstring& str);

		/*
		// @method		SetPos
		// @content		�\���ʒu�̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�\���ʒu�iVector2�j
		*/
		void SetPos(const std::wstring& name, const Vector2& pos);

		/*
		// @method		SetAnchor
		// @content		�A���J�[�|�C���g�̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�A���J�[�|�C���g�iVector2�j
		*/
		void SetAnchor(const std::wstring& name, const Vector2& anchor);

		/*
		// @method		SetColor
		// @content		�F�̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�F�iColor�j
		*/
		void SetColor(const std::wstring& name, const Color& color);

		/*
		// @method		SetFontSize
		// @content		�T�C�Y�̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�t�H���g�T�C�Y�ifloat�j
		*/
		void SetFontSize(const std::wstring& name, float fontSize);

		/*
		// @method		SetFont
		// @content		�t�H���g�̎�ނ̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�t�H���g�iwstring�j
		*/
		void SetFont(const std::wstring& name, const std::wstring& font);

		/*
		// @method		SetActive
		// @content		�A�N�e�B�u��Ԃ̕ύX
		// @param		�e�L�X�g���iwstring�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(const std::wstring& name, bool active);

		/*
		// @method		Draw
		// @content		�A�N�e�B�u��Ԃ̃e�L�X�g��`��
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		�o�^���ꂽ�e�L�X�g�̃��X�g�����Z�b�g
		*/
		void Reset();
	};
}