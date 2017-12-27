/* =====================================================================
//! @param		�uKeyboardUtil�v�w�b�_
//! @create		��� �T��
//! @date		17/11/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <Keyboard.h>
#include <memory>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		KeyboardUtil �N���X�iSingleton�j
	// @content		�L�[�{�[�h
	*/
	class KeyboardUtil : public SingletonDirector<KeyboardUtil>
	{
	private:
		std::unique_ptr<DirectX::Keyboard> keyboard_;

		// �X�e�[�g
		DirectX::Keyboard::State state_;
		DirectX::Keyboard::KeyboardStateTracker tracker_;

	private:
		friend class SingletonDirector<KeyboardUtil>;

		KeyboardUtil() {}

	public:
		/*
		// @method		Initialize
		// @content		����������
		*/
		void Initialize();

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update();

		/* �A�N�Z�b�T */

		inline DirectX::Keyboard* GetKeyboard() const								{ return keyboard_.get(); }
		inline const DirectX::Keyboard::State& GetState() const						{ return state_; }
		inline const DirectX::Keyboard::KeyboardStateTracker& GetTracker() const	{ return tracker_; }
	};
}