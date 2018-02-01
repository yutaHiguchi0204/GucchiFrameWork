/* =====================================================================
//! @param		�uTextRenderer�v�w�b�_
//! @create		��� �T��
//! @date		17/10/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <list>
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

	private:
		std::list<Text*> textList_;

	private:
		friend class SingletonDirector<TextRenderer>;

		TextRenderer() = default;

	public:
		/*
		// @method		RegisterText
		// @content		�e�L�X�g�̓o�^
		// @param		�o�^����e�L�X�g�iText*�j
		*/
		void RegisterText(Text* text);

		/*
		// @method		SetActive
		// @content		�e�L�X�g�̃A�N�e�B�u��Ԃ̕ύX
		// @param		�e�L�X�g�iText*�j
		// @param		�A�N�e�B�u��ԁibool�j
		*/
		void SetActive(Text* text, bool active);

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