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
	// �e�L�X�g�`��p�N���X
	class TextRenderer : public SingletonDirector<TextRenderer>
	{
	private:
		std::list<Text> textList_;

	private:
		friend class SingletonDirector<TextRenderer>;

		TextRenderer() {};

	public:
		void RegisterText(Text* text);						// �e�L�X�g�o�^
		void SetActive(Text* text, bool active);			// �A�N�e�B�u��Ԃ̕ύX

		void Draw();										// �e�L�X�g�`��
		void Reset();										// ���X�g���Z�b�g
	};
}