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
	/*
	// @class		TextRenderer クラス（Singleton）
	// @content		テキスト管理用
	// @use			RegisterText関数によって登録されたテキストを描画する
	// @use			シーン遷移時などにReset関数を呼ぶことで登録したテキストを解放する
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
		// @content		テキストの登録
		// @param		登録するテキスト（Text*）
		*/
		void RegisterText(Text* text);

		/*
		// @method		SetActive
		// @content		テキストのアクティブ状態の変更
		// @param		テキスト（Text*）
		// @param		アクティブ状態（bool）
		*/
		void SetActive(Text* text, bool active);

		/*
		// @method		Draw
		// @content		アクティブ状態のテキストを描画
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		登録されたテキストのリストをリセット
		*/
		void Reset();
	};
}