/* =====================================================================
//! @param		�uText�v�w�b�_
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <string>
#include "../Common/Element.h"

namespace GucchiLibrary
{ 
	/*
	// @class		Text �N���X
	// @content		�e�L�X�g���\�[�X
	// @use			TextRenderer�ɓo�^���邱�Ƃŕ`��\
	*/
	class Text : public Element
	{
	public:
		static const float DEFAULT_FONT_SIZE;

	private:
		std::wstring	str_;			// �e�L�X�g
		Vector2			pos_;			// �ʒu
		Vector2			anchor_;		// �A���J�[�|�C���g
		Color			color_;			// �F
		float			fontSize_;		// �t�H���g�T�C�Y
		std::wstring	font_;			// �g�p�t�H���g
		bool			isActive_;		// �A�N�e�B�u���

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		������iwstring�j
		// @param		�\���ʒu�iVector2�j
		// @param		�t�H���g�̐F�iColor�j�@�F�@�f�t�H���g�iColor(1, 1, 1)�j
		// @param		�t�H���g�T�C�Y�ifloat�j�@�F�@�f�t�H���g�iDEFAULT_FONT_SIZE�j
		// @param		�t�H���g���i�g���q�������j�iwstring�j�@�F�@�f�t�H���g�iL"default_font"�j
		*/
		Text(std::wstring str, const Vector2& pos, const Color& color = Color(1, 1, 1), float fontSize = DEFAULT_FONT_SIZE, std::wstring font = L"default_font");

		// �f�X�g���N�^
		virtual ~Text() = default;

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update() override { Element::Update(); }

		/*
		// @method		SetFont
		// @content		�t�H���g�̕ύX
		// @param		�X�v���C�g�t�H���g�n���h���iwstring�j
		*/
		void SetFont(std::wstring font);

		/* �A�N�Z�b�T */

		void SetString(std::wstring str)			{ str_ = str; }
		void SetPos(const Vector2& pos)				{ pos_ = pos; }
		void SetAnchor(const Vector2& anchor)		{ anchor_ = anchor; }
		void SetColor(const Color& color)			{ color_ = color; }
		void SetFontSize(float fontSize)			{ fontSize_ = fontSize; }
		void SetActive(bool active)					{ isActive_ = active; }

		inline std::wstring GetString() const		{ return str_; }
		inline const Vector2& GetPos() const		{ return pos_; }
		inline const Vector2& GetAnchor() const		{ return anchor_; }
		inline const Color& GetColor() const		{ return color_; }
		inline float GetFontSize() const			{ return fontSize_; }
		inline std::wstring GetFont() const			{ return font_; }
		inline bool GetActive() const				{ return isActive_; }
	};
}