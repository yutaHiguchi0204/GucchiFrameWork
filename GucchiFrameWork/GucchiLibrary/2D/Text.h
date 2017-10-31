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
	// クラスの定義
	class Text
	{
	private:
		std::wstring					str_;			// テキスト
		DirectX::SimpleMath::Vector2	pos_;			// 位置
		std::wstring					font_;			// 使用フォント
		int								fontSize_;		// フォントサイズ
		DirectX::SimpleMath::Color		color_;			// 色
		bool							isActive_;		// アクティブ状態

	public:
		Text(std::wstring str, DirectX::SimpleMath::Vector2 pos, std::wstring font = L"default_font", int fontSize = 12, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(1, 1, 1));
		virtual ~Text() {};

		void SetString(std::wstring str)					{ str_ = str; }
		void SetPos(DirectX::SimpleMath::Vector2 pos)		{ pos_ = pos; }
		void SetFont(std::wstring font);
		void SetFontSize(int fontSize)						{ fontSize_ = fontSize; }
		void SetColor(DirectX::SimpleMath::Color color)		{ color_ = color; }
		void SetActive(bool active)							{ isActive_ = active; }

		inline std::wstring GetString() const				{ return str_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const	{ return pos_; }
		inline std::wstring GetFont() const					{ return font_; }
		inline int GetFontSize() const						{ return fontSize_; }
		inline DirectX::SimpleMath::Color GetColor() const	{ return color_; }
		inline bool GetActive() const						{ return isActive_; }
	};
}