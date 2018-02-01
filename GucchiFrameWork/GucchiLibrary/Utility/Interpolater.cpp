/* =====================================================================
//! @param		「Interpolater」ソース（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */

// ヘッダファイルのインクルード
#include "Interpolater.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
float Interpolater::startTime_ = 0.0f;
float Interpolater::nowTime_ = 0.0f;

// メンバ関数の定義

/*==============================================================
// @brief		線形補間（float）
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<float>*）
// @return		補間値（float）
===============================================================*/
float Interpolater::Lerp(float start, float end, float time, wstring action, InterpolateState<float>* state)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		線形補間（Vector2）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector2>*）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 Interpolater::Lerp(const Vector2& start, const Vector2& end, float time, wstring action, InterpolateState<Vector2>* state)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		線形補間（Vector3）
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector3>*）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 Interpolater::Lerp(const Vector3& start, const Vector3& end, float time, wstring action, InterpolateState<Vector3>* state)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		線形補間（Vector4）
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector4>*）
// @return		補間値（Vector4）
===============================================================*/
DirectX::SimpleMath::Vector4 Interpolater::Lerp(const Vector4& start, const Vector4& end, float time, wstring action, InterpolateState<Vector4>* state)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * lerpTime;
	}

	return data;
}

/*==============================================================
// @brief		二次補間（後が速い）（float）
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<float>*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseIn(float start, float end, float time, wstring action, InterpolateState<float>* state)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		二次補間（後が速い）（Vector2）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector2>*）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 Interpolater::EaseIn(const Vector2& start, const Vector2& end, float time, wstring action, InterpolateState<Vector2>* state)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		二次補間（後が速い）（Vector3）
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector3>*）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 Interpolater::EaseIn(const Vector3& start, const Vector3& end, float time, wstring action, InterpolateState<Vector3>* state)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		二次補間（後が速い）（Vector4）
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector4>*）
// @return		補間値（Vector4）
===============================================================*/
DirectX::SimpleMath::Vector4 Interpolater::EaseIn(const Vector4& start, const Vector4& end, float time, wstring action, InterpolateState<Vector4>* state)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * lerpTime);
	}

	return data;
}

/*==============================================================
// @brief		二次補間（先が速い）（float）
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<float>*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseOut(float start, float end, float time, wstring action, InterpolateState<float>* state)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		二次補間（先が速い）（Vector2）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector2>*）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 Interpolater::EaseOut(const Vector2& start, const Vector2& end, float time, wstring action, InterpolateState<Vector2>* state)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		二次補間（先が速い）（Vector3）
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector3>*）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 Interpolater::EaseOut(const Vector3& start, const Vector3& end, float time, wstring action, InterpolateState<Vector3>* state)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		二次補間（先が速い）（Vector4）
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector4>*）
// @return		補間値（Vector4）
===============================================================*/
DirectX::SimpleMath::Vector4 Interpolater::EaseOut(const Vector4& start, const Vector4& end, float time, wstring action, InterpolateState<Vector4>* state)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * (lerpTime * (2.0f - lerpTime));
	}

	return data;
}

/*==============================================================
// @brief		三次補間（float）
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<float>*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseInOut(float start, float end, float time, wstring action, InterpolateState<float>* state)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		三次補間（Vector2）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector2>*）
// @return		補間値（Vector2）
===============================================================*/
DirectX::SimpleMath::Vector2 Interpolater::EaseInOut(const Vector2& start, const Vector2& end, float time, wstring action, InterpolateState<Vector2>* state)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		三次補間（Vector3）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector3>*）
// @return		補間値（Vector3）
===============================================================*/
DirectX::SimpleMath::Vector3 Interpolater::EaseInOut(const Vector3& start, const Vector3& end, float time, wstring action, InterpolateState<Vector3>* state)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

/*==============================================================
// @brief		三次補間（Vector4）
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、補間アクション名（wstring）、補間ステート（InterpolateState<Vector4>*）
// @return		補間値（Vector4）
===============================================================*/
DirectX::SimpleMath::Vector4 Interpolater::EaseInOut(const Vector4& start, const Vector4& end, float time, wstring action, InterpolateState<Vector4>* state)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (state->GetState(action) == INTERPOLATE_STATE::NONE)
	{
		startTime_ = state->GetTimer(action);
		data = start;
		state->SetState(action, INTERPOLATE_STATE::NOW);
	}

	// 時間更新
	nowTime_ = state->GetTimer(action) - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		state->SetState(action, INTERPOLATE_STATE::FINISH);
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}

// コンストラクタ
InterpolateDirector::InterpolateDirector()
{
	// 実体化
	stateF_ = make_unique<InterpolateState<float>>();
	stateV2_ = make_unique<InterpolateState<Vector2>>();
	stateV3_ = make_unique<InterpolateState<Vector3>>();
	stateV4_ = make_unique<InterpolateState<Vector4>>();
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void InterpolateDirector::Update()
{
	stateF_->Update();
	stateV2_->Update();
	stateV3_->Update();
	stateV4_->Update();
}

/*==============================================================
// @brief		リセット
// @param		なし
// @return		なし
===============================================================*/
void InterpolateDirector::Reset()
{
	stateF_->Reset();
	stateV2_->Reset();
	stateV3_->Reset();
	stateV4_->Reset();
}