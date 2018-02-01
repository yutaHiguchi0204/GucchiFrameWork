/* =====================================================================
//! @param		「Asset3D」ソース
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */

// ヘッダファイルのインクルード
#include "Asset3D.h"
#include "ObjectRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DebugSwitch.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
ID3D11BlendState* Asset3D::blendStateSubtractive_;

// メンバ関数の定義

// コンストラクタ
Asset3D::Asset3D(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, BLEND_MODE mode)
	: camera_(nullptr)
	, scale_(scale)
	, rot_(rot)
	, quat_(quat)
	, trans_(trans)
	, world_(Matrix::Identity)
	, blendMode_(mode)
	, isActive_(true)
	, isUseQuaternion_(false)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// エフェクト作成
	basicEffect_ = make_shared<BasicEffect>(deviceResources.GetD3DDevice());
	basicEffect_->SetVertexColorEnabled(true);

	// シェーダの取得
	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// 入力レイアウトの設定
	deviceResources.GetD3DDevice()->CreateInputLayout(
		VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		inputLayout_.GetAddressOf()
	);

	// エフェクトファクトリの作成
	effectFactory_ = make_shared<EffectFactory>(deviceResources.GetD3DDevice());

	// テクスチャ読み取りパスを設定
	effectFactory_->SetDirectory(FILE_PATH_MODEL.c_str());

	// 減算描画設定
	blendStateSubtractive_ = SetSubtractive();

	// 補間ステートの準備
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

// コピーコンストラクタ
Asset3D::Asset3D(const Asset3D& asset)
{
	basicEffect_           = asset.basicEffect_;
	inputLayout_           = asset.inputLayout_;
	effectFactory_         = asset.effectFactory_;
	camera_                = asset.camera_;
	scale_                 = asset.scale_;
	rot_                   = asset.rot_;
	quat_                  = asset.quat_;
	trans_                 = asset.trans_;
	world_                 = asset.world_;
	blendStateSubtractive_ = asset.blendStateSubtractive_;
	blendMode_             = asset.blendMode_;
	isActive_              = asset.isActive_;
	isUseQuaternion_       = asset.isUseQuaternion_;
	interpolateDirector_   = make_unique<InterpolateDirector>();
}

/*==============================================================
// @brief		ブレンド設定
// @param		ブレンドモード（BLEND_MODE）
// @return		なし
===============================================================*/
void Asset3D::SetBlendState(BLEND_MODE mode)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// ブレンドモード設定
	switch (mode)
	{
	case Asset3D::BLEND_MODE::ALPHA:			// アルファブレンド
		context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::ADDITIVE:			// 加算ブレンド
		context->OMSetBlendState(states->Additive(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::SUBTRACTIVE:		// 減算ブレンド
		context->OMSetBlendState(blendStateSubtractive_, nullptr, 0xffffffff);
		break;

	default:
		context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
		break;
	}
}

/*==============================================================
// @brief		減算描画設定
// @param		なし
// @return		減算描画用ブレンドステート（ID3D11BlendState*）
===============================================================*/
ID3D11BlendState* Asset3D::SetSubtractive()
{
	// 減算描画用のブレンドステートを作成
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable					= false;
	desc.IndependentBlendEnable					= false;
	desc.RenderTarget[0].BlendEnable			= true;
	desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend				= D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// ブレンドステートの作成
	ID3D11BlendState* blendState;
	if (FAILED(deviceResources.GetD3DDevice()->CreateBlendState(&desc, &blendState)))
	{
#if defined(MODE_DEBUG)
		OutputDebugString(L"Create blend state is failed.");
#endif
		assert(false);
	}

	return blendState;
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void Asset3D::Update()
{
	// 補間ステートの更新
	interpolateDirector_->Update();

	// スケーリング行列の計算
	Matrix scaleMat = Matrix::CreateScale(scale_);

	// 回転行列の計算
	Matrix rotMat = Matrix::Identity;
	if (isUseQuaternion_)
	{
		// クォータニオンで計算
		rotMat = Matrix::CreateFromQuaternion(quat_);
	}
	else
	{
		// オイラー角で計算
		rotMat = Matrix::CreateFromYawPitchRoll(rot_.y, rot_.x, rot_.z);
	}

	// 平行移動行列の計算
	Matrix transMat = Matrix::CreateTranslation(trans_);

	// ワールド行列の計算
	world_ = scaleMat * rotMat * transMat;
}

/*==============================================================
// @brief		描画前の準備
// @param		なし
// @return		なし
===============================================================*/
void Asset3D::DrawApply()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// ブレンドモード設定
	SetBlendState(blendMode_);

	// 深度ステンシルを更新しない
	context->OMSetDepthStencilState(states->DepthRead(), 0);

	// 描画設定
	context->RSSetState(states->CullNone());

	// 行列の設定
	basicEffect_->SetWorld(world_);
	basicEffect_->SetView(camera_->GetView());
	basicEffect_->SetProjection(camera_->GetProjection());

	// エフェクトの実行
	basicEffect_->Apply(context);

	// 入力レイアウトの設定
	context->IASetInputLayout(inputLayout_.Get());
}