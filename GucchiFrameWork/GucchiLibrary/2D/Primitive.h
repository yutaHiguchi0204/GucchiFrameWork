/* =====================================================================
//! @param		「Primitive」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
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
	public:
		/*
		// @content		プリミティブタイプ
		// @mode		LINE		：	線
		// @mode		TRIANGLE	：	三角
		*/
		enum class PRIMITIVE_TYPE
		{
			LINE,
			TRIANGLE,
			SQUARE,
			CIRCLE
		};

	private:
		PRIMITIVE_TYPE											type_;
		std::map<std::string, DirectX::SimpleMath::Vector2>		point_;
		DirectX::SimpleMath::Color								color_;
		bool													isFill_;

		// 円プリミティブ用
		DirectX::SimpleMath::Vector2							center_;
		float													radius_;

	public:
		// コンストラクタ
		Primitive();

		// デストラクタ
		virtual ~Primitive() {}

		/*
		// @method		Entry
		// @content		プリミティブ作成（線）
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(const DirectX::SimpleMath::Vector2& start, const DirectX::SimpleMath::Vector2& end, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（三角）
		// @param		塗りつぶすかどうか（bool）
		// @param		１点目（Vector2）
		// @param		２点目（Vector2）
		// @param		３点目（Vector2）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& _p1, const DirectX::SimpleMath::Vector2& _p2, const DirectX::SimpleMath::Vector2& _p3, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（四角）
		// @param		塗りつぶすかどうか（bool）
		// @param		左上の座標（Vector2）
		// @param		右下の座標（Vector2）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& topLeft, const DirectX::SimpleMath::Vector2& bottomRight, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/*
		// @method		Entry
		// @content		プリミティブ作成（円）
		// @param		塗りつぶすかどうか（bool）
		// @param		中心座標（Vector2）
		// @param		半径（float）
		// @param		分割数（int）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		*/
		void Entry(bool fillFlag, const DirectX::SimpleMath::Vector2& center, float radius, int div, const DirectX::SimpleMath::Color& color = DirectX::SimpleMath::Color(1, 1, 1, 1));

		/* アクセッサ */

		void SetColor(const DirectX::SimpleMath::Color& color)							{ color_ = color; }
		void SetFillFlag(bool fillFlag)													{ isFill_ = fillFlag; }

		inline PRIMITIVE_TYPE GetType()	const											{ return type_; }
		inline std::map<std::string, DirectX::SimpleMath::Vector2> GetPoints() const 	{ return point_; }
		inline DirectX::SimpleMath::Color GetColor() const								{ return color_; }
		inline bool GetFillFlag() const													{ return isFill_; }
		inline DirectX::SimpleMath::Vector2 GetCircleCenterPos() const					{ return center_; }
		inline float GetCircleRadius() const											{ return radius_; }
	};
}