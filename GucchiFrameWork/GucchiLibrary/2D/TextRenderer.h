/* =====================================================================
//! @param		「TextRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <map>
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
		using Color = DirectX::SimpleMath::Color;

	private:
		std::map<std::wstring, Text*> textList_;

	private:
		friend class SingletonDirector<TextRenderer>;

		TextRenderer() = default;

	public:
		/*
		// @method		RegisterText
		// @content		テキストの登録
		// @param		テキスト名（wstring）
		// @param		文字列（wstring）
		// @param		表示位置（Vector2）
		// @param		フォントの色（Color）　：　デフォルト（Color(1, 1, 1)）
		// @param		フォントサイズ（float）　：　デフォルト（DEFAULT_FONT_SIZE）
		// @param		フォント名（拡張子を除く）（wstring）　：　デフォルト（L"default_font"）
		*/
		void RegisterText(const std::wstring& name, const std::wstring& str, const Vector2& pos, const Color& color = Color(1, 1, 1), float fontSize = Text::DEFAULT_FONT_SIZE, const std::wstring& font = Text::DEFAULT_FONT);

		/*
		// @method		RegisterText
		// @content		テキストの登録
		// @param		テキスト名（wstring）
		// @param		登録するテキスト（Text*）
		*/
		void RegisterText(const std::wstring& name, Text* text);

		/*
		// @method		SetString
		// @content		文字列の変更
		// @param		テキスト名（wstring）
		// @param		文字列（wstring）
		*/
		void SetString(const std::wstring& name, const std::wstring& str);

		/*
		// @method		SetPos
		// @content		表示位置の変更
		// @param		テキスト名（wstring）
		// @param		表示位置（Vector2）
		*/
		void SetPos(const std::wstring& name, const Vector2& pos);

		/*
		// @method		SetAnchor
		// @content		アンカーポイントの変更
		// @param		テキスト名（wstring）
		// @param		アンカーポイント（Vector2）
		*/
		void SetAnchor(const std::wstring& name, const Vector2& anchor);

		/*
		// @method		SetColor
		// @content		色の変更
		// @param		テキスト名（wstring）
		// @param		色（Color）
		*/
		void SetColor(const std::wstring& name, const Color& color);

		/*
		// @method		SetFontSize
		// @content		サイズの変更
		// @param		テキスト名（wstring）
		// @param		フォントサイズ（float）
		*/
		void SetFontSize(const std::wstring& name, float fontSize);

		/*
		// @method		SetFont
		// @content		フォントの種類の変更
		// @param		テキスト名（wstring）
		// @param		フォント（wstring）
		*/
		void SetFont(const std::wstring& name, const std::wstring& font);

		/*
		// @method		SetActive
		// @content		アクティブ状態の変更
		// @param		テキスト名（wstring）
		// @param		アクティブ状態（bool）
		*/
		void SetActive(const std::wstring& name, bool active);

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