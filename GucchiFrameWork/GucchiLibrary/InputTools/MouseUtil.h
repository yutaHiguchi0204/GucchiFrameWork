/* =====================================================================
//! @param		「MouseUtil」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Mouse.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// クラスの定義
	class MouseUtil : public SingletonDirector<MouseUtil>
	{
	private:
		std::unique_ptr<DirectX::Mouse> mouse_;

		// ステート
		DirectX::Mouse::State state_;
		DirectX::Mouse::ButtonStateTracker tracker_;

	private:
		friend class SingletonDirector<MouseUtil>;

		MouseUtil() {}

	public:
		void Initialize();
		void Update();

		// アクセッサ
		inline DirectX::Mouse* GetMouse() const { return mouse_.get(); }
		inline const DirectX::Mouse::State& GetState() const { return state_; }
		inline const DirectX::Mouse::ButtonStateTracker& GetTracker() const { return tracker_; }
	};
}