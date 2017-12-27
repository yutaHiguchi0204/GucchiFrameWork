/* =====================================================================
//! @param		「PrimitiveRenderer」ソース
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */

// ヘッダファイルのインクルード
#include "PrimitiveRenderer.h"
#include <vector>
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void PrimitiveRenderer::Initialize()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11Device* device = deviceResources.GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

	// プリミティブバッチの設定
	primitiveBatch_ = make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	// エフェクトの設定
	basicEffect_ = std::make_unique<BasicEffect>(device);

	// 頂点カラーの有効化
	basicEffect_->SetVertexColorEnabled(true);

	// シェーダ準備
	void const* shaderByteCode;
	size_t byteCodeLength;

	// 描画設定を元に適切なシェーダを取得
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// 入力レイアウトを作成
	device->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, inputLayout_.ReleaseAndGetAddressOf());

	// 画面サイズを取得
	RECT rect = DeviceResources::GetInstance().GetOutputSize();

	// 各種変換行列をセット
	basicEffect_->SetWorld(Matrix::Identity);
	basicEffect_->SetView(Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0)));
	basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter((float)rect.left, (float)rect.right, (float)rect.bottom, (float)rect.top, 0.1f, 10.0f));
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void PrimitiveRenderer::Draw()
{
	DeviceResources& deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();
	CommonStates* states = deviceResources.GetCommonStates();

	// 深度ステンシルの設定
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	// ブレンドステートの設定
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// カリング設定
	context->RSSetState(states->CullNone());

	// 入力レイアウトをセット
	context->IASetInputLayout(inputLayout_.Get());

	// エフェクトの適用
	basicEffect_->Apply(context);

	// 描画処理
	for (auto& primitive : primitiveList_)
	{
		// プリミティブタイプ
		Primitive::PRIMITIVE_TYPE type = primitive->GetType();

		// 塗りつぶし指定の場合、各専用描画関数で描画
		if (primitive->GetFillFlag())
		{
			switch (type)
			{
			case Primitive::PRIMITIVE_TYPE::POINT:			// 点
				DrawPoint(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::LINE:			// 線
				DrawLine(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// 三角
				DrawTriangle(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::SQUARE:			// 四角
				DrawSquare(primitive->GetPoints(), primitive->GetColor());
				break;

			case Primitive::PRIMITIVE_TYPE::CIRCLE:			// 円
				DrawCircle(primitive->GetPoints(), primitive->GetColor());
				break;
			}

			continue;
		}

		// 頂点数の取得
		int vertexNum = GetNumVertex(primitive->GetPoints());

		// 円の場合は頂点数を[分割数+1]にする
		if (type == Primitive::PRIMITIVE_TYPE::CIRCLE)
		{
			vertexNum = (int)(primitive->GetPoints()["rad&div"].y) + 1;
		}

		// 頂点データの設定
		VertexPositionColor* vertices = SetVertices(type, primitive->GetPoints(), primitive->GetColor(), vertexNum);

		// プリミティブの描画
		DrawPrimitive(vertices, vertexNum);

		// プリミティブの解放
		delete vertices;
	}
}

/*==============================================================
// @brief		プリミティブの描画
// @param		頂点データ（VertexPositionColor*）、頂点数（int）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawPrimitive(const VertexPositionColor* vertices, int vertexCount)
{
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, vertices, vertexCount);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		点の描画
// @param		頂点データ（VertexPositionColor*）、色（Color）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawPoint(map<string, Vector2> vertex, const Color& color)
{
	VertexPositionColor point;

	// 位置設定
	point.position = Vector3(vertex["point"].x, vertex["point"].y, 0);

	// 色設定
	point.color = color;

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &point, 1);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		線の描画
// @param		頂点データ（VertexPositionColor*）、色（Color）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawLine(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor start, end;

	// 位置設定
	start.position = Vector3(vertices["start"].x, vertices["start"].y, 0);
	end.position = Vector3(vertices["end"].x, vertices["end"].y, 0);

	// 色設定
	start.color = color;
	end.color = color;

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->DrawLine(start, end);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		三角の描画
// @param		頂点データ（VertexPositionColor*）、色（Color）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawTriangle(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor p1, p2, p3;

	// 位置設定
	p1.position = Vector3(vertices["p1"].x, vertices["p1"].y, 0);
	p2.position = Vector3(vertices["p2"].x, vertices["p2"].y, 0);
	p3.position = Vector3(vertices["p3"].x, vertices["p3"].y, 0);

	// 色設定
	p1.color = color;
	p2.color = color;
	p3.color = color;

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->DrawTriangle(p1, p2, p3);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		四角の描画
// @param		頂点データ（VertexPositionColor*）、色（Color）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawSquare(map<string, Vector2> vertices, const Color& color)
{
	VertexPositionColor tl, tr, bl, br;

	// 位置設定
	tl.position = Vector3(vertices["topLeft"].x, vertices["topLeft"].y, 0);
	tr.position = Vector3(vertices["topRight"].x, vertices["topRight"].y, 0);
	bl.position = Vector3(vertices["bottomLeft"].x, vertices["bottomLeft"].y, 0);
	br.position = Vector3(vertices["bottomRight"].x, vertices["bottomRight"].y, 0);

	// 色設定
	tl.color = color;
	tr.color = color;
	bl.color = color;
	br.color = color;

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->DrawQuad(tl, tr, br, bl);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		円の描画
// @param		頂点データ（VertexPositionColor*）、色（Color）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawCircle(map<string, Vector2> vertices, const Color& color)
{
	// 分割数
	const int div = (int)vertices["rad&div"].y;

	// 中心座標
	Vector3 center3D = Vector3(vertices["center"].x, vertices["center"].y, 0);

	// インデックスデータ準備
	uint16_t* indices = new uint16_t[div * 3];
	VertexPositionColor* v = new VertexPositionColor[div + 1];

	// インデックスデータの設定
	for (int i = 0; i < div; i++)
	{
		indices[i * 3 + 0] = div;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i + 1;
	}
	indices[(div - 1) * 3 + 2] = 0;

	// 頂点座標を一旦全て中心点の座標で設定
	for (int i = 0; i < div + 1; i++)
	{
		v[i].position = center3D;
		v[i].color = color;
	}

	// 円の外周分ずらす
	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i);
		v[i].position.x += vertices[key].x - vertices["center"].x;
		v[i].position.y += vertices[key].y - vertices["center"].y;
	}

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, div * 3, v, div + 1);
	primitiveBatch_->End();

	// データの解放
	delete indices;
	delete v;
}

/*==============================================================
// @brief		プリミティブの登録
// @param		プリミティブ（Primitive*）
// @return		なし
===============================================================*/
void PrimitiveRenderer::RegisterPrimitive(Primitive* primitive)
{
	primitiveList_.emplace_back(primitive);
}

/*==============================================================
// @brief		指定された頂点をもとに頂点データを設定
// @param		プリミティブタイプ（PRIMITIVE_TYPE）、頂点データ（map<string, Vector2>）、色（Color）、頂点数（int）
// @return		頂点データ（VertexPositionColor*）
===============================================================*/
VertexPositionColor* PrimitiveRenderer::SetVertices(Primitive::PRIMITIVE_TYPE type, map<string, Vector2> vertices, Color color, int vertexNum)
{
	VertexPositionColor* vertex = new VertexPositionColor[vertexNum];

	// 色の設定
	for (int i = 0; i < vertexNum; i++)
	{
		vertex[i].color = color;
	}

	// 頂点データの設定
	switch (type)
	{
	case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// 三角
		vertex[0].position = Vector3(vertices["p1"].x, vertices["p1"].y, 0);
		vertex[1].position = Vector3(vertices["p2"].x, vertices["p2"].y, 0);
		vertex[2].position = Vector3(vertices["p3"].x, vertices["p3"].y, 0);
		vertex[3].position = vertex[0].position;

		return vertex;
		break;

	case Primitive::PRIMITIVE_TYPE::SQUARE:			// 四角
		vertex[0].position = Vector3(vertices["topLeft"].x, vertices["topLeft"].y, 0);
		vertex[1].position = Vector3(vertices["bottomRight"].x, vertices["topLeft"].y, 0);
		vertex[2].position = Vector3(vertices["bottomRight"].x, vertices["bottomRight"].y, 0);
		vertex[3].position = Vector3(vertices["topLeft"].x, vertices["bottomRight"].y, 0);
		vertex[4].position = vertex[0].position;

		return vertex;
		break;

	case Primitive::PRIMITIVE_TYPE::CIRCLE:			// 円
		for (int i = 0; i < vertexNum - 1; i++)
		{
			string key = "Rad" + to_string(i);
			vertex[i].position = Vector3(vertices[key].x, vertices[key].y, 0);
		}
		vertex[vertexNum - 1].position = vertex[0].position;

		return vertex;
		break;

	default:
		break;
	}

	// ここにはこない
	return nullptr;
}

/*==============================================================
// @brief		頂点数の取得
// @param		頂点データ（map<string, Vector2>）
// @return		頂点数（int）
===============================================================*/
int PrimitiveRenderer::GetNumVertex(map<string, Vector2> vertices)
{
	return vertices.size() + 1;
}

/*==============================================================
// @brief		リストリセット
// @param		なし
// @return		なし
===============================================================*/
void PrimitiveRenderer::Reset()
{
	primitiveList_.clear();
}