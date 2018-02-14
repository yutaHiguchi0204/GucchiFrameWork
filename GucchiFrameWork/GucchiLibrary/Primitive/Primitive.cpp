/* =====================================================================
//! @param		「Primitive」ソース
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */

// ヘッダファイルのインクルード
#include "Primitive.h"

// 名前空間
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Primitive::Primitive()
	: pos_(Vector3::Zero)
	, isFill_(true)
{
}

// コンストラクタ
Primitive2D::Primitive2D()
	: Primitive()
{
}

// コンストラクタ
Primitive3D::Primitive3D()
	: Primitive()
{
}

/*==============================================================
// @brief		キーの取得
// @param		なし
// @return		全てのキー（vector<string>）
===============================================================*/
vector<string> Primitive2D::GetKeys() const
{
	vector<string> keys;

	// キーを取得
	for (auto& vertex : vertices_)
	{
		keys.emplace_back(vertex.first);
	}

	return keys;
}