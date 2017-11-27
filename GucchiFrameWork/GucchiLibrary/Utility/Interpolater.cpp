/* =====================================================================
//! @param		「Interpolater」ソース（補間ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/09
===================================================================== */

// ヘッダファイルのインクルード
#include "Interpolater.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;

// 静的メンバの定義
float Interpolater::startTime_ = 0.0f;
float Interpolater::nowTime_ = 0.0f;
bool Interpolater::isNowLerp_ = false;

// メンバ関数の定義

/*==============================================================
// @brief		線形補間（float）
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（float）
===============================================================*/
float Interpolater::LinearLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector2）
===============================================================*/
Vector2 Interpolater::LinearLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector3）
===============================================================*/
Vector3 Interpolater::LinearLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector4）
===============================================================*/
Vector4 Interpolater::LinearLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseInLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector2）
===============================================================*/
Vector2 Interpolater::EaseInLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector3）
===============================================================*/
Vector3 Interpolater::EaseInLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector4）
===============================================================*/
Vector4 Interpolater::EaseInLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseOutLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector2）
===============================================================*/
Vector2 Interpolater::EaseOutLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector3）、終了（Vector3）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector3）
===============================================================*/
Vector3 Interpolater::EaseOutLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector4）、終了（Vector4）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector4）
===============================================================*/
Vector4 Interpolater::EaseOutLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（float）、終了（float）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（float）
===============================================================*/
float Interpolater::EaseInOutLerp(float start, float end, float time, float* objTimer)
{
	float data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector2）
===============================================================*/
Vector2 Interpolater::EaseInOutLerp(Vector2 start, Vector2 end, float time, float* objTimer)
{
	Vector2 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector3）
===============================================================*/
Vector3 Interpolater::EaseInOutLerp(Vector3 start, Vector3 end, float time, float* objTimer)
{
	Vector3 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
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
// @param		開始（Vector2）、終了（Vector2）、かける時間（float、単位：秒）、オブジェクト個別のタイマー（float*）
// @return		補間値（Vector4）
===============================================================*/
Vector4 Interpolater::EaseInOutLerp(Vector4 start, Vector4 end, float time, float* objTimer)
{
	Vector4 data;

	// 補間中でないなら時間等を初期化
	if (!isNowLerp_)
	{
		startTime_ = *objTimer;
		data = start;
		isNowLerp_ = true;
	}

	// 時間更新
	nowTime_ = *objTimer - startTime_;

	// 補間完了かどうか
	if (nowTime_ >= (time * 60.0f))
	{
		isNowLerp_ = false;
		return end;
	}
	else
	{
		float lerpTime = nowTime_ / (time * 60.0f);
		data = start + (end - start) * ((lerpTime * lerpTime) * (3.0f - lerpTime * 2.0f));
	}

	return data;
}