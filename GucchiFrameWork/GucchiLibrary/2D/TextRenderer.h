/* =====================================================================
//! @param		「TextRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <list>
#include "../Common/SingletonDirector.h"
#include "Text.h"

namespace GucchiLibrary
{
	// テキスト描画用クラス
	class TextRenderer : public SingletonDirector<TextRenderer>
	{
	private:
		std::list<Text> textList_;

	private:
		friend class SingletonDirector<TextRenderer>;

		TextRenderer() {};

	public:
		void RegisterText(Text* text);						// テキスト登録
		void SetActive(Text* text, bool active);			// アクティブ状態の変更

		void Draw();										// テキスト描画
		void Reset();										// リストリセット
	};
}