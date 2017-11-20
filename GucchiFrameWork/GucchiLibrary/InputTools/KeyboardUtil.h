/* =====================================================================
//! @param		「KeyboardUtil」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	// クラスの定義
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