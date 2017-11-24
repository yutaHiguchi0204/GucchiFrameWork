/* =====================================================================
//! @param		「ObjectRenderer」ソース
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */

// ヘッダファイルのインクルード
#include "ObjectRenderer.h"
#include "ModelCache.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		オブジェクトの登録
// @param		オブジェクト（Object*）
// @return		なし
===============================================================*/
void ObjectRenderer::RegisterObject(Object* object)
{
	objectList_.push_back(*object);
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		オブジェクト（Object*）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void ObjectRenderer::SetActive(Object* object, bool active)
{
	object->SetActive(active);
}

/*==============================================================
// @brief		アクティブ状態のオブジェクトを描画
// @param		なし
// @return		なし
===============================================================*/
void ObjectRenderer::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();

	// 各項目の準備
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// 描画処理
	for (auto& object : objectList_)
	{
		// アクティブ状態のオブジェクトのみ表示
		if (object.GetActive())
		{
			// 描画前の準備
			object.DrawApply();

			// カメラ
			Camera* camera = object.GetCamera();

			// 減算描画の場合は減算指定をする
			if (object.GetBlendMode() == Asset3D::BLEND_MODE::SUBTRACTIVE)
			{
				object.GetModel()->Draw(context, *states, object.GetWorld(), camera->GetView(), camera->GetProjection(), false, [&]() { 
					context->OMSetBlendState(object.GetBlendStateSubtract(), nullptr, 0xffffffff);
				});
			}
			else
			{
				object.GetModel()->Draw(context, *states, object.GetWorld(), camera->GetView(), camera->GetProjection());
			}
		}
	}
}

/*==============================================================
// @brief		リストリセット
// @param		なし
// @return		なし
===============================================================*/
void ObjectRenderer::Reset()
{
	objectList_.clear();
}

/*==============================================================
// @brief		ブレンド設定
// @param		ブレンドモード（BLEND_MODE）
// @return		なし
===============================================================*/
void ObjectRenderer::SetBlendState(Asset3D::BLEND_MODE mode)
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// ブレンドモード設定
	switch (mode)
	{
	case Asset3D::BLEND_MODE::ALPHA:		// アルファブレンド
		context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);
		break;

	case Asset3D::BLEND_MODE::ADDITIVE:		// 加算ブレンド
		context->OMSetBlendState(states->Additive(), nullptr, 0xffffffff);
		break;

	default:
		context->OMSetBlendState(states->Opaque(), nullptr, 0xffffffff);
		break;
	}
}

/*==============================================================
// @brief		減算描画設定
// @param		ブレンドステート（ID3D11BlendState*）
// @return		なし
===============================================================*/
void ObjectRenderer::SetSubtractive(ID3D11BlendState* blendState)
{
	// 減算描画用のブレンドステートを作成
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ブレンドステートの作成
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	if (FAILED(deviceResources.GetD3DDevice()->CreateBlendState(&desc, &blendState)))
	{
		OutputDebugString(L"Create blend state is failed.");
		assert(0);
	}
}

/*==============================================================
// @brief		オブジェクトのライティングを無効にする
// @param		モデル（Model）
// @return		なし
===============================================================*/
void ObjectRenderer::DisableLighting(Model* model)
{
	if (model)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = model->meshes.begin();
		for (; it_mesh != model->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// 自己発光を最大値に
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// エフェクトに含む全ての平行光源分について処理する
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ライトを無効にする
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}

/*==============================================================
// @brief		オブジェクトの生成
// @param		ファイル名（wstring）
// @return		なし
===============================================================*/
unique_ptr<Object> ObjectFactory::CreateObjectFromFile(const wstring fileName)
{
	unique_ptr<Object> object = make_unique<Object>();

	// モデルの格納庫を準備
	ModelCache& cache = ModelCache::GetInstance();

	// モデルの読み込み
	Model* model = cache.LoadModel(fileName, object->GetEffectFactory());

	// モデルライティングを無効にする
	ObjectRenderer& objectRenderer_ = ObjectRenderer::GetInstance();
	objectRenderer_.DisableLighting(model);

	// オブジェクトにセット
	object->SetModel(model);
	object->SetCamera(camera_);

	return std::move(object);
}