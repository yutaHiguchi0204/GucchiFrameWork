/* =====================================================================
//! @param		「Text」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>

namespace GucchiLibrary
{ 
	/*
	// @class		Text クラス
	// @content		テキストリソース
	// @use			TextRendererに登録することで描画可能
	*/
	class Text
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Color = DirectX::SimpleMath::Color;

	public:
		static const float DEFAULT_FONT_SIZE;

	private:
		std::wstring	str_;			// テキスト
		Vector2			pos_;			// 位置
		Vector2			anchor_;		// アンカーポイント
		std::wstring	font_;			// 使用フォント
		int				fontSize_;		// フォントサイズ
		Color			color_;			// 色
		bool			isActive_;		// アクティブ状態

	public:
		/*
		// @method		コンストラクタ
		// @param		文字列（wstring）
		// @param		表示位置（Vector2）
		// @param		フォント名（拡張子を除く）（wstring）　：　デフォルト（L"default_font"）
		// @param		フォントサイズ（int）　：　デフォルト（DEFAULT_FONT_SIZE）
		// @param		フォントの色（Color）　：　デフォルト（Color(1, 1, 1)）
		*/
		Text(std::wstring str, const Vector2& pos, std::wstring font = L"default_font", int fontSize = DEFAULT_FONT_SIZE, const Color& color = Color(1, 1, 1));

		// デストラクタ
		virtual ~Text() = default;

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
		void SetFontSize(int fontSize)				{ fontSize_ = fontSize; }
		void SetColor(const Color& color)			{ color_ = color; }
		void SetActive(bool active)					{ isActive_ = active; }

		inline std::wstring GetString() const		{ return str_; }
		inline const Vector2& GetPos() const		{ return pos_; }
		inline const Vector2& GetAnchor() const		{ return anchor_; }
		inline std::wstring GetFont() const			{ return font_; }
		inline int GetFontSize() const				{ return fontSize_; }
		inline const Color& GetColor() const		{ return color_; }
		inline bool GetActive() const				{ return isActive_; }
	};
}