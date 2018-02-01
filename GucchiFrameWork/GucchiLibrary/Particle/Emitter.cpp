/* =====================================================================
//! @param		「Emitter」ソース
//! @create		樋口 裕太
//! @date		17/12/27
===================================================================== */

// ヘッダファイルのインクルード
#include "Emitter.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const int Emitter::FOREVER_EXIST = -1;			// 寿命

// メンバ関数の定義

// コンストラクタ
Emitter::Emitter(const Vector3& pos, float exisTime)
	: texture_(nullptr)
	, pos_(pos)
	, exisTime_(exisTime)
	, nowFrame_(0.0f)
	, isExist_(true)
	, parentObject_(nullptr)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// プリミティブバッチの設定
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Emitter::Update()
{
	// 存在できる時間が指定されていたらチェック
	if (exisTime_ != FOREVER_EXIST)
	{
		// 存在できる時間を超えてたら破棄
		if (nowFrame_ / FRAME_PER_SECOND >= exisTime_)
		{
			isExist_ = false;
		}
	}

	// フレームの更新
	nowFrame_++;

	// パーティクルの更新
	for (auto particleItr = particle_.begin(); particleItr != particle_.end();)
	{
		// 存在していなかったらリストから消す
		if (!(*particleItr)->IsExist())
		{
			particleItr = particle_.erase(particleItr);
			continue;
		}

		(*particleItr)->Update();

		++particleItr;
	}
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void Emitter::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// バッチ処理開始
	primitiveBatch_->Begin();

	for (auto& particle : particle_)
	{
		// ブレンドステート設定
		Asset3D::SetBlendState(particle->GetBlendMode());

		// テクスチャ設定
		context->PSSetShaderResources(0, 1, texture_->GetShaderResourceView().GetAddressOf());

		// 座標の設定（ローカル＋エミッター）
		VertexPositionColorTexture vertex = particle->GetVertexNow();
		vertex.position = vertex.position + pos_;

		// 親モデルが設定されていたら親モデルの座標も足す
		if (parentObject_)
		{
			Object* p = parentObject_;
			while (p != nullptr)
			{
				vertex.position = vertex.position + p->GetTranslate();
				p = p->GetParent();
			}
		}

		// パーティクルの描画
		primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	}

	// バッチ処理終了
	primitiveBatch_->End();
}

/*==============================================================
// @brief		パーティクル生成
// @param		寿命（float）、始点情報（VertexPositionColorTexture）、終点情報（VertexPositionColorTexture）、ブレンドモード（BLEND_MODE）、ループモード（LOOP_MODE）
// @return		なし
===============================================================*/
void Emitter::Entry(float exisTime, VertexPositionColorTexture vertexDataStart, VertexPositionColorTexture vertexDataEnd, Asset3D::BLEND_MODE blendMode, Particle::LOOP_MODE loopMode)
{
	// パーティクルの作成
	unique_ptr<Particle> particle = make_unique<Particle>();
	particle->Initialize(exisTime, vertexDataStart, vertexDataEnd, blendMode, loopMode);

	// パーティクルの登録
	particle_.emplace_back(move(particle));
}

/*==============================================================
// @brief		テクスチャの読み込み
// @param		テクスチャファイル名（wstring）
// @return		なし
===============================================================*/
void Emitter::LoadTexture(const wstring fileName)
{
	TextureCache& textureCache = TextureCache::GetInstance();
	texture_ = textureCache.LoadTexture(fileName);
}