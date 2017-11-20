/* =====================================================================
//! @param		「Object」ソース
//! @create		樋口 裕太
//! @date		17/11/15
===================================================================== */

// ヘッダファイルのインクルード
#include "Object.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
Object::Object(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, Asset3D::BLEND_MODE mode)
	: Asset3D(trans, scale, rot, quat, mode)
{
}