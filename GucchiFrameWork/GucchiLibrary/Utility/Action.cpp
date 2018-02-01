/* =====================================================================
//! @param		「Action」ソース（移動関係ライブラリ）
//! @create		樋口 裕太
//! @date		17/12/02
===================================================================== */

// ヘッダファイルのインクルード
#include "Action.h"
#include "../Utility/Interpolater.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;

// メンバ関数の定義

/*==============================================================
// @brief		線形移動（絶対移動）
// @param		スプライト（Sprite*）、移動にかける時間（float）、終点（Vector2）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 MoveTo::Action(Sprite* sprite, float time, const Vector2& pos)
{
	// 補間ステートの準備
	InterpolateState<Vector2>* state = sprite->GetInterpolateDirector()->stateV2_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"MoveTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在の位置（始点）
		Vector2 start = sprite->GetPos();

		// 終点
		Vector2 end = pos;

		// 線形補間
		state->Entry(L"MoveTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveTo");
}

/*==============================================================
// @brief		線形移動（絶対移動）
// @param		オブジェクト（Object*）、移動にかける時間（float）、終点（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 MoveTo::Action(Object* object, float time, const Vector3& trans)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"MoveTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在の位置（始点）
		Vector3 start = object->GetTranslate();

		// 終点
		Vector3 end = trans;

		// 線形補間
		state->Entry(L"MoveTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveTo");
}

/*==============================================================
// @brief		線形移動（相対移動）
// @param		スプライト（Sprite*）、移動にかける時間（float）、移動距離（Vector2）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 MoveBy::Action(Sprite* sprite, float time, const Vector2& distance)
{
	// 補間ステートの準備
	InterpolateState<Vector2>* state = sprite->GetInterpolateDirector()->stateV2_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"MoveBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在の位置（始点）
		Vector2 start = sprite->GetPos();

		// 終点
		Vector2 end = Vector2(start.x + distance.x, start.y + distance.y);

		// 線形補間
		state->Entry(L"MoveBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveBy");
}

/*==============================================================
// @brief		線形移動（相対移動）
// @param		オブジェクト（Object*）、移動にかける時間（float）、移動距離（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 MoveBy::Action(Object* object, float time, const Vector3& distance)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"MoveBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在の位置（始点）
		Vector3 start = object->GetTranslate();

		// 終点
		Vector3 end = Vector3(start.x + distance.x, start.y + distance.y, start.z + distance.z);

		// 線形補間
		state->Entry(L"MoveBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"MoveBy");
}

/*==============================================================
// @brief		スケール変化（絶対変化）
// @param		スプライト（Sprite*）、変化にかける時間（float）、スケール値（float）
// @return		補間値（float）
===============================================================*/
float ScaleTo::Action(Sprite* sprite, float time, float scale)
{
	// 補間ステートの準備
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"ScaleTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		float start = sprite->GetScale();

		// 終点
		float end = scale;

		// 線形補間
		state->Entry(L"ScaleTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleTo");
}

/*==============================================================
// @brief		スケール変化（絶対変化）
// @param		オブジェクト（Object*）、変化にかける時間（float）、スケール値（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 ScaleTo::Action(Object* object, float time, const Vector3& scale)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"ScaleTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		Vector3 start = object->GetScale();

		// 終点
		Vector3 end = scale;

		// 線形補間
		state->Entry(L"ScaleTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleTo");
}

/*==============================================================
// @brief		スケール変化（相対変化）
// @param		スプライト（Sprite*）、変化にかける時間（float）、現在のスケールからの倍率（float）
// @return		補間値（float）
===============================================================*/
float ScaleBy::Action(Sprite* sprite, float time, const float scale)
{
	// 補間ステートの準備
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"ScaleBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		float start = sprite->GetScale();

		// 終点
		float end = start * scale;

		// 線形補間
		state->Entry(L"ScaleBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleBy");
}

/*==============================================================
// @brief		スケール変化（相対変化）
// @param		オブジェクト（Object*）、変化にかける時間（float）、現在のスケールからの倍率（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 ScaleBy::Action(Object* object, float time, const Vector3& scale)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"ScaleBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		Vector3 start = object->GetScale();

		// 終点
		Vector3 end = start * scale;

		// 線形補間
		state->Entry(L"ScaleBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"ScaleBy");
}

/*==============================================================
// @brief		回転（絶対回転）
// @param		スプライト（Sprite*）、回転にかける時間（float）、回転角（float）
// @return		補間値（float）
===============================================================*/
float RotateTo::Action(Sprite* sprite, float time, float angle)
{
	// 補間ステートの準備
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"RotateTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在の回転角
		float start = sprite->GetAngle();

		// 終点
		float end = angle;

		// 線形補間
		state->Entry(L"RotateTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateTo");
}

/*==============================================================
// @brief		回転（絶対回転）
// @param		オブジェクト（Object*）、回転にかける時間（float）、回転角（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 RotateTo::Action(Object* object, float time, const Vector3& rot)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"RotateTo") == INTERPOLATE_STATE::NONE)
	{
		// 現在の回転角
		Vector3 start = object->GetRotate();

		// 終点
		Vector3 end = rot;

		// 線形補間
		state->Entry(L"RotateTo", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateTo");
}

/*==============================================================
// @brief		回転（相対回転）
// @param		スプライト（Sprite*）、回転にかける時間（float）、現在の角度からの回転角（float）
// @return		補間値（float）
===============================================================*/
float RotateBy::Action(Sprite* sprite, float time, float angle)
{
	// 補間ステートの準備
	InterpolateState<float>* state = sprite->GetInterpolateDirector()->stateF_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"RotateBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		float start = sprite->GetAngle();

		// 終点
		float end = start + angle;

		// 線形補間
		state->Entry(L"RotateBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateBy");
}

/*==============================================================
// @brief		回転（相対回転）
// @param		オブジェクト（Object*）、回転にかける時間（float）、現在の角度からの回転角（Vector3）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 RotateBy::Action(Object* object, float time, const Vector3& rot)
{
	// 補間ステートの準備
	InterpolateState<Vector3>* state = object->GetInterpolateDirector()->stateV3_.get();

	// 開始してなかったら補間開始
	if (state->GetState(L"RotateBy") == INTERPOLATE_STATE::NONE)
	{
		// 現在のスケール
		Vector3 start = object->GetRotate();

		// 終点
		Vector3 end = start + rot;

		// 線形補間
		state->Entry(L"RotateBy", start, end, time, INTERPOLATE_MODE::LERP);
	}

	return state->GetResult(L"RotateBy");
}