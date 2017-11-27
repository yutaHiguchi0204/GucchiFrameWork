/* =====================================================================
//! @param		�uText�v�w�b�_
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>

namespace GucchiLibrary
{ 
	/*
	// @class		Text �N���X
	// @content		�e�L�X�g���\�[�X
	// @use			TextRenderer�ɓo�^���邱�Ƃŕ`��\
	*/
	class Text
	{
	public:
		static const float DEFAULT_FONT_SIZE;

	private:
		std::wstring					str_;			// �e�L�X�g
		DirectX::SimpleMath::Vector2	pos_;			// �ʒu
		std::wstring					font_;			// �g�p�t�H���g
		int								fontSize_;		// �t�H���g�T�C�Y
		DirectX::SimpleMath::Color		color_;			// �F
		bool							isActive_;		// �A�N�e�B�u���

	public:
		/*
		// @method		�R���X�g���N�^
		// @param		������iwstring�j
		// @param		�\���ʒu�iVector2�j
		// @param		�t�H���g���i�g���q�������j�iwstring�j�@�F�@�f�t�H���g�iL"default_font"�j
		// @param		�t�H���g�T�C�Y�iint�j�@�F�@�f�t�H���g�iDEFAULT_FONT_SIZE�j
		// @param		�t�H���g�̐F�iColor�j�@�F�@�f�t�H���g�iColor(1, 1, 1)�j
		*/
		Text(std::wstring str, DirectX::SimpleMath::Vector2 pos, std::wstring font = L"default_font", int fontSize = DEFAULT_FONT_SIZE, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1, 1, 1));

		// �f�X�g���N�^
		virtual ~Text() {}

		/* �A�N�Z�b�T */

		void SetString(std::wstring str)					{ str_ = str; }
		void SetPos(DirectX::SimpleMath::Vector2 pos)		{ pos_ = pos; }
		void SetFont(std::wstring font);
		void SetFontSize(int fontSize)						{ fontSize_ = fontSize; }
		void SetColor(DirectX::SimpleMath::Color color)		{ color_ = color; }
		void SetActive(bool active)							{ isActive_ = active; }

		inline std::wstring GetString() const				{ return str_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const	{ return pos_; }
		inline std::wstring GetFont() const					{ return font_; }
		inline int GetFontSize() const						{ return fontSize_; }
		inline DirectX::SimpleMath::Color GetColor() const	{ return color_; }
		inline bool GetActive() const						{ return isActive_; }
	};
}