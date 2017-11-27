/* =====================================================================
//! @param		「DefaultCamera」ソース
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */

// ヘッダファイルのインクルード
#include "DefaultCamera.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// 静的メンバの定義
const float DefaultCamera::DEFAULT_DISTANCE = 5.0f;

// メンバ関数の定義

// コンストラクタ
DefaultCamera::DefaultCamera(int width, int height)
	: Camera(width, height)
	, angle_(Vector2::Zero)
	, tmpAngle_(Vector2::Zero)
	, dragStartPos_(Vector2::Zero)
	, wheelValue_(0)
{
	// 画面サイズに対する相対スケールを設定
	relScale_ = Vector2(1.0f / width, 1.0f / height);
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void DefaultCamera::Update()
{
	// 親クラスの更新
	Camera::Update();

	/* ドラッグでカメラを動かす */
	// ドラッグ開始
	if (mouse_.GetTracker().leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		// マウスの座標を取得
		dragStartPos_ = Vector2((float)mouse_.GetState().x, (float)mouse_.GetState().y);
	}
	// ドラッグ終了
	else if (mouse_.GetTracker().leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		// 現在の回転角を保存
		angle_ = tmpAngle_;
	}

	// ドラッグ中はカメラ移動
	if (mouse_.GetState().leftButton)
	{
		Motion(Vector2((float)mouse_.GetState().x, (float)mouse_.GetState().y));
	}

	// マウスのフォイール値でカメラのビュー拡大率を確定
	wheelValue_ = mouse_.GetState().scrollWheelValue;
	if (wheelValue_ > 0)
	{
		wheelValue_ = 0;
		mouse_.GetMouse()->ResetScrollWheelValue();
	}

	// ビュー行列の算出
	Matrix rotY = Matrix::CreateRotationY(tmpAngle_.y);
	Matrix rotX = Matrix::CreateRotationX(tmpAngle_.x);
	Matrix rot = rotY * rotX;

	// ビューアングルの初期化
	view_.eyePos = Vector3(0.0f, 0.0f, 1.0f);
	view_.refPos = Vector3::Zero;
	view_.upVec = Vector3(0.0f, 1.0f, 0.0f);

	// ビューアングルの更新
	view_.eyePos = Vector3::Transform(view_.eyePos, rot.Invert());
	view_.eyePos *= (DEFAULT_DISTANCE - wheelValue_ / 100);
	view_.upVec = Vector3::Transform(view_.upVec, rot.Invert());

	// ビューアングル確定
	view_.viewMat = Matrix::CreateLookAt(view_.eyePos, view_.refPos, view_.upVec);
}

/*==============================================================
// @brief		カメラ回転モーション
// @param		マウスの座標（Vector2）
// @return		なし
===============================================================*/
void DefaultCamera::Motion(Vector2 mousePos)
{
	// 相対座標の取得
	Vector2 dragPos;
	dragPos.x = (mousePos.x - dragStartPos_.x) * relScale_.x;
	dragPos.y = (mousePos.y - dragStartPos_.y) * relScale_.y;

	// ドラッグされていたら回転させる
	if (dragPos.x != 0.0f || dragPos.y != 0.0f)
	{
		// 回転
		Vector2 angle = Vector2(dragPos.y * XM_PI, dragPos.x * XM_PI);

		// 回転角の保存
		tmpAngle_ = angle_ + angle;
	}
}