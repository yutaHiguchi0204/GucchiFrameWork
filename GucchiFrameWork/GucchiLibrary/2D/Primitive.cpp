/* =====================================================================
//! @param		「Primitive」ソース
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */

// ヘッダファイルのインクルード
#include "Primitive.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Primitive::Primitive()
	: isFill_(true)
{
}

/*==============================================================
// @brief		プリミティブ作成（線）
// @param		始点（Vector2）、終点（Vector2）、色（Color）
// @return		なし
===============================================================*/
void Primitive::Entry(const Vector2& start, const Vector2& end, const Color& color)
{
	point_["start"] = start;
	point_["end"] = end;
	color_ = color;

	// タイプを線に設定
	type_ = PRIMITIVE_TYPE::LINE;
}

/*==============================================================
// @brief		プリミティブ作成（三角）
// @param		塗りつぶすかどうか（bool）、１点目（Vector2）、２点目（Vector2）、３点目（Vector2）、色（Color）
// @return		なし
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& _p1, const Vector2& _p2, const Vector2& _p3, const Color& color)
{
	point_["p1"] = _p1;
	point_["p2"] = _p2;
	point_["p3"] = _p3;
	color_ = color;

	// タイプを三角に設定
	type_ = PRIMITIVE_TYPE::TRIANGLE;

	// 塗りつぶすかどうか
	isFill_ = fillFlag;
}

/*==============================================================
// @brief		プリミティブ作成（四角）
// @param		塗りつぶすかどうか（bool）、左上の座標（Vector2）、右下の座標（Vector2）、色（Color）
// @return		なし
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& topLeft, const Vector2& bottomRight, const Color& color)
{
	point_["topLeft"] = topLeft;
	point_["topRight"] = Vector2(bottomRight.x, topLeft.y);
	point_["bottomLeft"] = Vector2(topLeft.x, bottomRight.y);
	point_["bottomRight"] = bottomRight;
	color_ = color;

	// タイプを四角に設定
	type_ = PRIMITIVE_TYPE::SQUARE;

	// 塗りつぶすかどうか
	isFill_ = fillFlag;
}

/*==============================================================
// @brief		プリミティブ作成（円）
// @param		塗りつぶすかどうか（bool）、中心座標（Vector2）、半径（float）、分割数（int）、色（Color）
// @return		なし
===============================================================*/
void Primitive::Entry(bool fillFlag, const Vector2& center, float radius, int div, const Color& color)
{
	// ポイントの１番目と２番目をデータ保存用とする
	point_["center"] = center;
	point_["rad&div"].x = radius;
	point_["rad&div"].y = (float)div;

	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i);
		point_[key].x = center.x + cosf(XM_2PI / div * i) * radius;
		point_[key].y = center.y + sinf(XM_2PI / div * i) * radius;
	}

	color_ = color;

	// タイプを四角に設定
	type_ = PRIMITIVE_TYPE::CIRCLE;

	// 塗りつぶすかどうか
	isFill_ = fillFlag;
}