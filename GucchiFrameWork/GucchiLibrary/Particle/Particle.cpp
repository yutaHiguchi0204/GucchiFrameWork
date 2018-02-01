/* =====================================================================
//! @param		「Particle」ソース
//! @create		樋口 裕太
//! @date		17/12/27
===================================================================== */

// ヘッダファイルのインクルード
#include "Particle.h"
#include "../Common/Constant.h"
#include "../Utility/Math.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const int Particle::FOREVER_EXIST = -1;			// 永続的存在
const float Particle::DEFAULT_SCALE = 1.0f;		// 初期スケール
const float Particle::DEFAULT_ROTATE = 0.0f;	// 初期回転角

// メンバ関数の定義

// コピーコンストラクタ
Particle::Particle(const Particle& particle)
{
	vertexStart_         = particle.vertexStart_;
	vertexEnd_           = particle.vertexEnd_;
	vertexNow_           = particle.vertexNow_;
	exisTime_            = particle.exisTime_;
	nowFrame_            = particle.nowFrame_;
	blendMode_           = particle.blendMode_;
	loopMode_            = particle.loopMode_;
	isExist_             = particle.isExist_;
	interpolateDirector_ = make_unique<InterpolateDirector>();
	interpolateDirector_->stateV3_->Entry(L"pos",	vertexStart_.position,				vertexEnd_.position,			exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateV4_->Entry(L"color", vertexStart_.color,					vertexEnd_.color,				exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"scale",	vertexStart_.textureCoordinate.x,	vertexEnd_.textureCoordinate.x, exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"rot",	vertexStart_.textureCoordinate.y,	vertexEnd_.textureCoordinate.y, exisTime_, INTERPOLATE_MODE::LERP);
}

/*==============================================================
// @brief		初期化処理
// @param		寿命（float）、始点情報（VertexPositionColorTexture）、終点情報（VertexPositionColorTexture）、ブレンドモード（BLEND_MODE）、ループモード（LOOP_MODE）
// @return		なし
===============================================================*/
void Particle::Initialize(float exisTime, VertexPositionColorTexture vertexDataStart, VertexPositionColorTexture vertexDataEnd, Asset3D::BLEND_MODE blendMode, LOOP_MODE loopMode)
{
	// 開始時点のデータを設定
	vertexStart_ = vertexDataStart;

	// 終了時点のデータを設定
	vertexEnd_ = vertexDataEnd;

	// 現在の頂点データに開始時点のデータを設定
	vertexNow_ = vertexStart_;

	// ブレンドモードの設定
	blendMode_ = blendMode;

	// 時間関係
	exisTime_ = exisTime;
	nowFrame_ = 0;

	// ループモードの設定
	loopMode_ = loopMode;

	// 存在
	isExist_ = true;

	// 補間ステートの準備
	interpolateDirector_ = make_unique<InterpolateDirector>();
	interpolateDirector_->stateV3_->Entry(L"pos",	vertexStart_.position,				vertexEnd_.position,			exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateV4_->Entry(L"color", vertexStart_.color,					vertexEnd_.color,				exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"scale",	vertexStart_.textureCoordinate.x,	vertexEnd_.textureCoordinate.x, exisTime_, INTERPOLATE_MODE::LERP);
	interpolateDirector_->stateF_->Entry(L"rot",	vertexStart_.textureCoordinate.y,	vertexEnd_.textureCoordinate.y, exisTime_, INTERPOLATE_MODE::LERP);
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Particle::Update()
{
	// 補間ステートの更新
	interpolateDirector_->Update();

	// 寿命が指定されていたらチェック
	if (exisTime_ != FOREVER_EXIST)
	{
		// 寿命を超えてたら破棄
		if (nowFrame_ / FRAME_PER_SECOND >= exisTime_)
		{
			// ループモードがREPEATで設定されてたら最初から
			if (loopMode_ == LOOP_MODE::REPEAT)
			{
				Reset();
				return;
			}
			// TURNに設定されてたらstartとendを入れ替えて最初から
			else if (loopMode_ == LOOP_MODE::TURN)
			{
				// データの入れ替え
				Math::SwapData(&vertexStart_, &vertexEnd_);
				Reset();
				return;
			}

			isExist_ = false;
			return;
		}
	}

	// パーティクルの更新
	vertexNow_.position				= interpolateDirector_->stateV3_->GetResult(L"pos");
	vertexNow_.color				= interpolateDirector_->stateV4_->GetResult(L"color");
	vertexNow_.textureCoordinate.x	= interpolateDirector_->stateF_->GetResult(L"scale");
	vertexNow_.textureCoordinate.y	= interpolateDirector_->stateF_->GetResult(L"rot");

	// フレームの更新
	nowFrame_++;
}

/*==============================================================
// @brief		リセット
// @param		なし
// @return		なし
===============================================================*/
void Particle::Reset()
{
	vertexNow_ = vertexStart_;
	nowFrame_ = 0;

	// 補間ステートのリセット
	interpolateDirector_->Reset();
}