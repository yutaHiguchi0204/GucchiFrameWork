/* =====================================================================
//! @param		「ParticleRenderer」ソース
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */

// ヘッダファイルのインクルード
#include "ParticleRenderer.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"
#include "../System/DebugSystem.h"
#include "../Utility/BinaryFileManager.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// 静的メンバの定義
const vector<D3D11_INPUT_ELEMENT_DESC> ParticleRenderer::INPUT_LAYOUT = {		// 入力レイアウト
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
const int ParticleRenderer::MAX_PARTICLE = 32768;								// パーティクルの最大数

// メンバ関数の定義

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void ParticleRenderer::Initialize()
{
	DeviceResources& deviceResources	= DeviceResources::GetInstance();
	ID3D11Device* device				= deviceResources.GetD3DDevice();
	ID3D11DeviceContext* context		= deviceResources.GetD3DDeviceContext();

	// ファイル
	const wstring SHADER_DIRECTORY = L"Resources/Shaders/";
	const wstring FILE_VS = SHADER_DIRECTORY + L"ParticleVertexShader"		+ EXT_CSO;
	const wstring FILE_GS = SHADER_DIRECTORY + L"ParticleGeometryShader"	+ EXT_CSO;
	const wstring FILE_PS = SHADER_DIRECTORY + L"ParticlePixelShader"		+ EXT_CSO;

	// シェーダファイルの読み込み
	BinaryFile shaderVS = BinaryFileManager::LoadBinaryFile(FILE_VS);
	BinaryFile shaderGS = BinaryFileManager::LoadBinaryFile(FILE_GS);
	BinaryFile shaderPS = BinaryFileManager::LoadBinaryFile(FILE_PS);

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(shaderVS.GetData(), shaderVS.GetSize(), NULL, vertexShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateVertexShader Failed.", true);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(shaderGS.GetData(), shaderGS.GetSize(), NULL, geometryShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateGeometryShader Failed.", true);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(shaderPS.GetData(), shaderPS.GetSize(), NULL, pixelShader_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreatePixelShader Failed.", true);
		return;
	}

	// プリミティブバッチ作成
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, MAX_PARTICLE);

	// 頂点フォーマットを指定して入力レイアウトを作成
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		shaderVS.GetData(),
		shaderVS.GetSize(),
		inputLayout_.GetAddressOf()
	);

	// コンスタントバッファの設定
	D3D11_BUFFER_DESC cBuffer;
	cBuffer.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cBuffer.ByteWidth			= sizeof(Constants);
	cBuffer.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	cBuffer.MiscFlags			= 0;
	cBuffer.StructureByteStride = 0;
	cBuffer.Usage				= D3D11_USAGE_DYNAMIC;

	// コンスタントバッファの作成
	if (FAILED(device->CreateBuffer(&cBuffer, nullptr, cBuffer_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"CreateBuffer Failed.", true);
		return;
	}

	// テクスチャサンプラーの設定
	D3D11_SAMPLER_DESC sampler;
	ZeroMemory(&sampler, sizeof(sampler));				// ゼロクリア
	sampler.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;

	// テクスチャサンプラーの作成
	if (FAILED(device->CreateSamplerState(&sampler, sampler_.ReleaseAndGetAddressOf())))
	{
		DebugSystem::DebugLog(L"Create sampler state failed.", true);
		return;
	}
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void ParticleRenderer::Update()
{
	// 存在していないエミッターはリストから消す
	for (auto& emitter : emitter_)
	{
		if (emitter.second && !emitter.second->IsExist())
		{
			DisposeEmitter(emitter.first);
		}
	}

	// エミッター更新
	for (auto& emitter : emitter_)
	{
		if (emitter.second && emitter.second->GetActive())
		{
			emitter.second->Update();
		}
	}
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void ParticleRenderer::Draw()
{
	DeviceResources& deviceResources	= DeviceResources::GetInstance();
	ID3D11DeviceContext* context		= deviceResources.GetD3DDeviceContext();
	CommonStates* states				= deviceResources.GetCommonStates();

	// 行列生成
	Matrix world = Matrix::CreateScale(3.0f);
	Matrix view = camera_->GetView();
	Matrix proj = camera_->GetProjection();

	// 行列の合成
	Matrix wvp = world * view * proj;

	// 各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(cBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.wvpMat = wvp;
		constants.billboard = camera_->GetBillboard();
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));

		// メモリ解放
		context->Unmap(cBuffer_.Get(), 0);
	}

	// コンスタントバッファのセット
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, cBuffer_.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// シェーダーをセット
	context->VSSetShader(vertexShader_.Get(), nullptr, 0);
	context->GSSetShader(geometryShader_.Get(), nullptr, 0);
	context->PSSetShader(pixelShader_.Get(), nullptr, 0);

	// 入力レイアウトをセット
	context->IASetInputLayout(inputLayout_.Get());

	// カリング設定
	context->RSSetState(states->CullNone());

	// 深度ステンシル設定
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	// テクスチャサンプラー設定
	context->PSSetSamplers(0, 1, sampler_.GetAddressOf());

	// エミッターの描画
	for (auto& emitter : emitter_)
	{
		if (emitter.second && emitter.second->GetActive())
		{
			emitter.second->Draw();
		}
	}

	// シェーダークリア
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/*==============================================================
// @brief		リセット
// @param		なし
// @return		なし
===============================================================*/
void ParticleRenderer::Reset()
{
	emitter_.clear();
}

/*==============================================================
// @brief		エミッターの登録
// @param		エミッター（Emitter*）、エミッター名（wstring）、テクスチャファイル名（wstring）、エミッターの座標（Vector3）
// @return		なし
===============================================================*/
void ParticleRenderer::RegisterEmitter(Emitter* emitter, wstring emitterName, wstring textureFileName, const Vector3& emitterPos)
{
	emitter_[emitterName] = emitter;
	emitter_[emitterName]->LoadTexture(textureFileName);
	emitter_[emitterName]->SetPos(emitterPos);
}

/*==============================================================
// @brief		エミッターの登録
// @param		エミッター名（wstring）
// @return		なし
===============================================================*/
void ParticleRenderer::DisposeEmitter(wstring emitterName)
{
	emitter_[emitterName] = nullptr;
}