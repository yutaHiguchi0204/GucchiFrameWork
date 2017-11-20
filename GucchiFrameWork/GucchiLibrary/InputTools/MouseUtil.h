/* =====================================================================
//! @param		�uMouseUtil�v�w�b�_
//! @create		��� �T��
//! @date		17/11/19
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Mouse.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// �N���X�̒�`
	class MouseUtil : public SingletonDirector<MouseUtil>
	{
	private:
		std::unique_ptr<DirectX::Mouse> mouse_;

		// �X�e�[�g
		DirectX::Mouse::State state_;
		DirectX::Mouse::ButtonStateTracker tracker_;

	private:
		friend class SingletonDirector<MouseUtil>;

		MouseUtil() {}

	public:
		void Initialize();
		void Update();

		// �A�N�Z�b�T
		inline DirectX::Mouse* GetMouse() const { return mouse_.get(); }
		inline const DirectX::Mouse::State& GetState() const { return state_; }
		inline const DirectX::Mouse::ButtonStateTracker& GetTracker() const { return tracker_; }
	};
}