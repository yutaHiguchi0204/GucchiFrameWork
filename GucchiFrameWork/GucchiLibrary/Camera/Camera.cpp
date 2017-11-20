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
}