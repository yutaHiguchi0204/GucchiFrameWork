/* =====================================================================
//! @param		「KeyboardUtil」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/19
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <Keyboard.h>
#include <memory>
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		KeyboardUtil クラス（Singleton）
	// @content		キーボード
	*/
	class KeyboardUtil : public SingletonDirector<KeyboardUtil>
	{
	private:
		std::unique_ptr<DirectX::Keyboard> keyboard_;

		// ステート
		DirectX::Keyboard::State state_;
		DirectX::Keyboard::KeyboardStateTracker tracker_;

	private:
		friend class SingletonDirector<KeyboardUtil>;

		KeyboardUtil() {}

	public:
		/*
		// @method		Initialize
		// @content		初期化処理
		*/
		void Initialize();

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();

		/* アクセッサ */

		inline DirectX::Keyboard* GetKeyboard() const								{ return keyboard_.get(); }
		inline const DirectX::Keyboard::State& GetState() const						{ return state_; }
		inline const DirectX::Keyboard::KeyboardStateTracker& GetTracker() const	{ return tracker_; }
	};
}