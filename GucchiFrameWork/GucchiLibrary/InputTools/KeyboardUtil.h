/* =====================================================================
//! @param		�uKeyboardUtil�v�w�b�_
//! @create		��� �T��
//! @date		17/11/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class KeyboardUtil : public SingletonDirector<KeyboardUtil>
	{
	private:
		std::unique_ptr<DirectX::Keyboard> keyboard_;

	private:
		friend class SingletonDirector<KeyboardUtil>;

		KeyboardUtil() {}

	public:
		void Initialize();
		void Update();
	};
}