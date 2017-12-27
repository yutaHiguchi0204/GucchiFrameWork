/* =====================================================================
//! @param		「Camera」ソース
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */

// ヘッダファイルのインクルード
#include "Camera.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// メンバ関数の定義

// コンストラクタ
Camera::Camera(int width, int height)
{
	// ビューの設定
	view_.viewMat	= Matrix::Identity;
	view_.eyePos	= Vector3(0.0f, 6.0f, 10.0f);
	view_.refPos	= Vector3(0.0f, 2.0f, 0.0f);
	view_.upVec		= Vector3(0.0f, 1.0f, 0.0f);

	// プロジェクションの設定
	proj_.projMat	= Matrix::Identity;
	proj_.fov		= XMConvertToRadians(60.0f);
	proj_.aspect	= (float)width / height;
	proj_.nearClip	= 0.1f;
	proj_.farClip	= 1000.0f;
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Camera::Update()
{
	// ビュー行列の計算
	view_.viewMat = Matrix::CreateLookAt(view_.eyePos, view_.refPos, view_.upVec);

	// プロジェクション行列の計算
	proj_.projMat = Matrix::CreatePerspectiveFieldOfView(proj_.fov, proj_.aspect, proj_.nearClip, proj_.farClip);
	
	// ビルボード行列を計算
	CalcBillboard();
}

/*==============================================================
// @brief		ビルボード行列の計算
// @param		なし
// @return		なし
===============================================================*/
void Camera::CalcBillboard()
{
	// 視線方向
	Vector3 eyeDir = view_.eyePos - view_.refPos;

	// Y軸
	Vector3 axisY = Vector3::UnitY;

	// X軸
	Vector3 axisX = axisY.Cross(eyeDir);
	axisX.Normalize();

	// Z軸
	Vector3 axisZ = axisX.Cross(axisY);
	axisZ.Normalize();

	// Y軸周りビルボード行列（右手系の為Z方向反転）
	billboardConstrainY_ = Matrix::Identity;
	billboardConstrainY_.m[0][0] = axisX.x;
	billboardConstrainY_.m[0][1] = axisX.y;
	billboardConstrainY_.m[0][2] = axisX.z;
	billboardConstrainY_.m[1][0] = axisY.x;
	billboardConstrainY_.m[1][1] = axisY.y;
	billboardConstrainY_.m[1][2] = axisY.z;
	billboardConstrainY_.m[2][0] = -axisZ.x;
	billboardConstrainY_.m[2][1] = -axisZ.y;
	billboardConstrainY_.m[2][2] = -axisZ.z;

	axisY = eyeDir.Cross(axisX);
	axisY.Normalize();
	eyeDir.Normalize();

	// ビルボード行列（右手系の為Z方向反転）
	billboard_ = Matrix::Identity;
	billboard_.m[0][0] = axisX.x;
	billboard_.m[0][1] = axisX.y;
	billboard_.m[0][2] = axisX.z;
	billboard_.m[1][0] = axisY.x;
	billboard_.m[1][1] = axisY.y;
	billboard_.m[1][2] = axisY.z;
	billboard_.m[2][0] = -eyeDir.x;
	billboard_.m[2][1] = -eyeDir.y;
	billboard_.m[2][2] = -eyeDir.z;
}