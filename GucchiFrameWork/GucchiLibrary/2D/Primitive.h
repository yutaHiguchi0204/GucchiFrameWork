/* =====================================================================
//! @param		「Primitive」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <list>
#include <map>
#include <SimpleMath.h>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		Primitive クラス
	// @content		プリミティブ
	*/
	class Primitive
	{
	private:
		using Vector2	= DirectX::SimpleMath::Vector2;
		using Color		= DirectX::SimpleMath::Color;

	public:
		/*
		// @content		プリミティブタイプ
		// @mode		POINT		：	点
		// @mode		LINE		：	線
		// @mode		TRIANGLE	：	三角
		// @mode		SQUARE		：　四角
		// @mode		CIRCLE		：　円
		*/
		enum class PRIMITIVE_TYPE
		{
			POINT,
			LINE,
			TRIANGLE,
			SQUARE,
			CIRCLE
		};

	protected:
		PRIMITIVE_TYPE						type_;
		std::map<std::string, Vector2>		point_;
		Color								color_;
		bool								isFill_;

	public:
		// コンストラクタ
		Primitive();

		// デストラクタ
		virtual ~Primitive() = default;

		/*
		// @method		Entry
		// @content		プリミティブ作成（点）
		// @param		座標（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(const Vector2& point, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（線）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(const Vector2& start, const Vector2& end, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（三角）
		// @param		塗りつぶすかどうか（bool）
		// @param		１点目（Vector2）
		// @param		２点目（Vector2）
		// @param		３点目（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const Vector2& _p1, const Vector2& _p2, const Vector2& _p3, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（四角）
		// @param		塗りつぶすかどうか（bool）
		// @param		左上の座標（Vector2）
		// @param		右下の座標（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const Vector2& topLeft, const Vector2& bottomRight, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（円）
		// @param		塗りつぶすかどうか（bool）
		// @param		中心座標（Vector2）
		// @param		半径（float）
		// @param		分割数（int）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const Vector2& center, float radius, int div, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		GetKeys
		// @content		キーの取得
		// @return		全てのキー（list<string>）
		*/
		std::list<std::string> GetKeys() const;

		/* アクセッサ */

		void SetPoint(std::string key, const Vector2& point)		{ point_[key] = point; }
		void SetColor(const Color& color)							{ color_ = color; }
		void SetFillFlag(bool fillFlag)								{ isFill_ = fillFlag; }

		inline PRIMITIVE_TYPE GetType()	const						{ return type_; }
		inline std::map<std::string, Vector2> GetPoints() const 	{ return point_; }
		inline const Color& GetColor() const						{ return color_; }
		inline bool GetFillFlag() const								{ return isFill_; }
	};
}