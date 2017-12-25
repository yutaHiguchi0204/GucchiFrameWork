/* =====================================================================
//! @param		「Asset3D」ソース
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */

// ヘッダファイルのインクルード
#include "Asset3D.h"
#include "ObjectRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
ID3D11BlendState* Asset3D::blendStateSubtract_;

// メンバ関数の定義

// コンストラクタ
Asset3D::Asset3D(const Vector3& trans, const Vector3& scale, const Vector3& rot, const Quaternion& quat, BLEND_MODE mode)
	: scale_(scale)
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
	ObjectRenderer& objectRenderer = ObjectRenderer::GetInstance();
	blendStateSubtract_ = objectRenderer.SetSubtractive();

	// 補間ステートの準備
	interpolateDirector_ = make_unique<InterpolateDirector>();
}

// コピーコンストラクタ
Asset3D::Asset3D(const Asset3D& asset)
{
	basicEffect_         = asset.basicEffect_;
	inputLayout_         = asset.inputLayout_;
	effectFactory_       = asset.effectFactory_;
	camera_              = asset.camera_;
	scale_               = asset.scale_;
	rot_                 = asset.rot_;
	quat_                = asset.quat_;
	trans_               = asset.trans_;
	world_               = asset.world_;
	blendStateSubtract_  = asset.blendStateSubtract_;
	blendMode_           = asset.blendMode_;
	isActive_            = asset.isActive_;
	isUseQuaternion_     = asset.isUseQuaternion_;
	interpolateDirector_ = make_unique<InterpolateDirector>();
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
	ObjectRenderer& objectRenderer = ObjectRenderer::GetInstance();
	objectRenderer.SetBlendState(blendMode_);

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