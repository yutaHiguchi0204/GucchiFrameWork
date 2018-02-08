/* =====================================================================
//! @param		「Text」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <string>
#include "../Common/Element.h"

namespace GucchiLibrary
{ 
	/*
	// @class		Text クラス
	// @content		テキストリソース
	// @use			TextRendererに登録することで描画可能
	*/
	class Text : public Element
	{
	public:
		static const float DEFAULT_FONT_SIZE;

	private:
		std::wstring	str_;			// テキスト
		Vector2			pos_;			// 位置
		Vector2			anchor_;		// アンカーポイント
		Color			color_;			// 色
		float			fontSize_;		// フォントサイズ
		std::wstring	font_;			// 使用フォント
		bool			isActive_;		// アクティブ状態

	public:
		/*
		// @method		コンストラクタ
		// @param		文字列（wstring）
		// @param		表示位置（Vector2）
		// @param		フォントの色（Color）　：　デフォルト（Color(1, 1, 1)）
		// @param		フォントサイズ（float）　：　デフォルト（DEFAULT_FONT_SIZE）
		// @param		フォント名（拡張子を除く）（wstring）　：　デフォルト（L"default_font"）
		*/
		Text(std::wstring str, const Vector2& pos, const Color& color = Color(1, 1, 1), float fontSize = DEFAULT_FONT_SIZE, std::wstring font = L"default_font");

		// デストラクタ
		virtual ~Text() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update() override { Element::Update(); }

		/*
		// @method		SetFont
		// @content		フォントの変更
		// @param		スプライトフォントハンドル（wstring）
		*/
		void SetFont(std::wstring font);

		/* アクセッサ */

		void SetString(std::wstring str)			{ str_ = str; }
		void SetPos(const Vector2& pos)				{ pos_ = pos; }
		void SetAnchor(const Vector2& anchor)		{ anchor_ = anchor; }
		void SetColor(const Color& color)			{ color_ = color; }
		void SetFontSize(float fontSize)			{ fontSize_ = fontSize; }
		void SetActive(bool active)					{ isActive_ = active; }

		inline std::wstring GetString() const		{ return str_; }
		inline const Vector2& GetPos() const		{ return pos_; }
		inline const Vector2& GetAnchor() const		{ return anchor_; }
		inline const Color& GetColor() const		{ return color_; }
		inline float GetFontSize() const			{ return fontSize_; }
		inline std::wstring GetFont() const			{ return font_; }
		inline bool GetActive() const				{ return isActive_; }
	};
}