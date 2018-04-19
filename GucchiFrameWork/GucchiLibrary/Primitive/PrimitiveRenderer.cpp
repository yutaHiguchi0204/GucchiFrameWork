/* =====================================================================
//! @param		「PrimitiveRenderer」ソース
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */

// ヘッダファイルのインクルード
#include "PrimitiveRenderer.h"
#include "../Common/DeviceResources.h"
#include "System/DebugSystem.h"

// 名前空間
using namespace DirectX;
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
	basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter(static_cast<float>(rect.left), static_cast<float>(rect.right), static_cast<float>(rect.bottom), static_cast<float>(rect.top), 0.1f, 10.0f));
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
		if (primitive->GetActive())
		{
			// プリミティブタイプ
			Primitive::PRIMITIVE_TYPE type = primitive->GetType();

			// ２Ｄ変換
			Primitive2D* primitive2D = dynamic_cast<Primitive2D*>(primitive);

			// ２Ｄ描画
			if (primitive2D)
			{
				Draw2D(primitive2D, type);
				continue;
			}

			// ３Ｄ変換
			Primitive3D* primitive3D = dynamic_cast<Primitive3D*>(primitive);

			// ３Ｄ描画
			if (primitive3D)
			{
				Draw3D(primitive3D);
			}
		}
	}
}

/*==============================================================
// @brief		２Ｄ用描画処理
// @param		２Ｄプリミティブ（Primitive2D*）、プリミティブタイプ（PRIMITIVE_TYPE）
// @return		なし
===============================================================*/
void PrimitiveRenderer::Draw2D(Primitive2D* primitive, Primitive::PRIMITIVE_TYPE type)
{
	// POINT3DとSEGMENTの場合はビュー行列とプロジェクション行列にカメラを設定する
	if (type == Primitive::PRIMITIVE_TYPE::POINT3D || type == Primitive::PRIMITIVE_TYPE::SEGMENT)
	{
		basicEffect_->SetView(camera_->GetView());
		basicEffect_->SetProjection(camera_->GetProjection());
	}
	else
	{
		// 画面サイズを取得
		RECT rect = DeviceResources::GetInstance().GetOutputSize();

		basicEffect_->SetView(Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0)));
		basicEffect_->SetProjection(Matrix::CreateOrthographicOffCenter(static_cast<float>(rect.left), static_cast<float>(rect.right), static_cast<float>(rect.bottom), static_cast<float>(rect.top), 0.1f, 10.0f));
	}

	// 塗りつぶし指定の場合、各専用描画関数で描画
	if (primitive->isFill_)
	{
		switch (type)
		{
		case Primitive::PRIMITIVE_TYPE::POINT:			// 点
		case Primitive::PRIMITIVE_TYPE::POINT3D:		// 点
			DrawPoint(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::LINE:			// 線
		case Primitive::PRIMITIVE_TYPE::SEGMENT:		// 線分
			DrawSegment(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::TRIANGLE:		// 三角
			DrawTriangle(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::RECTANGLE:		// 四角
			DrawRectangle(primitive->vertices_);
			break;

		case Primitive::PRIMITIVE_TYPE::CIRCLE:			// 円
			Circle* circle = dynamic_cast<Circle*>(primitive);
			DrawCircle(circle->vertices_, circle->div_);
			break;
		}

		return;
	}

	// 頂点データをまとめる
	VertexPositionColor* v = GetVerticesArray(primitive);

	// プリミティブの描画
	DrawPrimitive(v, primitive->vertices_.size());

	// データの解放
	delete[] v;
}

/*==============================================================
// @brief		３Ｄ用描画処理
// @param		３Ｄプリミティブ（Primitive3D*）
// @return		なし
===============================================================*/
void PrimitiveRenderer::Draw3D(Primitive3D* primitive)
{
	// 行列生成
	Matrix world = Matrix::Identity;
	Matrix view = camera_->GetView();
	Matrix proj = camera_->GetProjection();

	// プリミティブの描画
	//primitive->geometry_->Draw(world, view, proj, primitive->color_, nullptr, !primitive->isFill_);
}

/*==============================================================
// @brief		描画用にまとめられた頂点データの配列を取得
// @param		プリミティブ（Primitive2D*）
// @return		頂点データ配列（VertexPositionColor*）
===============================================================*/
VertexPositionColor* PrimitiveRenderer::GetVerticesArray(Primitive2D* primitive)
{
	VertexPositionColor* v = new VertexPositionColor[primitive->vertices_.size()];

	// 頂点データ配列の作成
	if (primitive->GetType() == Primitive::PRIMITIVE_TYPE::CIRCLE)
	{
		Circle* circle = dynamic_cast<Circle*>(primitive);
		for (int i = 0; i < circle->div_; i++)
		{
			string key = "Rad" + to_string(i / 10) + to_string(i % 10);
			v[i] = circle->vertices_[key];
		}
		v[circle->div_] = v[0];
	}
	else
	{
		int i = 0;
		for (auto& vertex : primitive->vertices_)
		{
			v[i] = vertex.second;
			i++;
		}
	}

	return v;
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
// @param		頂点データ（map<string, VertexPositionColor>）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawPoint(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &vertices["point"], 1);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		線分の描画
// @param		頂点データ（map<string, VertexPositionColor>）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawSegment(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawLine(vertices["start"], vertices["end"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		三角の描画
// @param		頂点データ（map<string, VertexPositionColor>）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawTriangle(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawTriangle(vertices["p0"], vertices["p1"], vertices["p2"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		四角の描画
// @param		頂点データ（map<string, VertexPositionColor>）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawRectangle(map<string, VertexPositionColor> vertices)
{
	primitiveBatch_->Begin();
	primitiveBatch_->DrawQuad(vertices["p0"], vertices["p1"], vertices["p2"], vertices["p3"]);
	primitiveBatch_->End();
}

/*==============================================================
// @brief		円の描画
// @param		頂点データ（map<string, VertexPositionColor>）、分割数（int）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DrawCircle(map<string, VertexPositionColor> vertices, int div)
{
	// インデックスデータの設定
	uint16_t* indices = new uint16_t[div * 3];
	for (int i = 0; i < div; i++)
	{
		indices[i * 3 + 0] = div;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i + 1;
	}
	indices[(div - 1) * 3 + 2] = 0;

	// 描画用頂点データの設定
	VertexPositionColor* v = new VertexPositionColor[div + 1];

	// 頂点座標を一旦全て中心点の座標で設定
	for (int i = 0; i < div + 1; i++)
	{
		v[i].position = vertices["center"].position;
		v[i].color = vertices["center"].color;
	}

	// 円の外周分ずらす
	for (int i = 0; i < div; i++)
	{
		string key = "Rad" + to_string(i / 10) + to_string(i % 10);
		v[i].position.x += vertices[key].position.x - vertices["center"].position.x;
		v[i].position.y += vertices[key].position.y - vertices["center"].position.y;
	}

	// 描画
	primitiveBatch_->Begin();
	primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices, div * 3, v, div + 1);
	primitiveBatch_->End();

	// データの解放
	delete[] v;
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
// @brief		プリミティブの解放
// @param		プリミティブ（Primitive*）
// @return		なし
===============================================================*/
void PrimitiveRenderer::DisposePrimitive(Primitive* primitive)
{
	primitiveList_.remove(primitive);
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

/*==============================================================
// @brief		点プリミティブの生成
// @param		座標（Vector2）、色（Color）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreatePoint(const Vector2& point, const Color& color)
{
	unique_ptr<Primitive> primitive = CreatePoint(Vector3(point.x, point.y, 0), color);

	// プリミティブタイプを"点"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::POINT);

	return primitive;
}

/*==============================================================
// @brief		点プリミティブの生成
// @param		座標（Vector3）、色（Color）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreatePoint(const Vector3& point, const Color& color)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// 位置設定
	primitive->vertices_["point"].position = point;

	// 色設定
	primitive->vertices_["point"].color = color;

	// プリミティブタイプを"点"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::POINT3D);

	return move(primitive);
}

/*==============================================================
// @brief		線分プリミティブの生成
// @param		始点（Vector2）、終点（Vector2）、色（Color）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateSegment(const Vector2& start, const Vector2& end, const Color& color)
{
	unique_ptr<Primitive> primitive = CreateSegment(Vector3(start.x, start.y, 0), Vector3(end.x, end.y, 0), color);

	// プリミティブタイプを"点"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::LINE);

	return primitive;
}

/*==============================================================
// @brief		線分プリミティブの生成
// @param		始点（Vector3）、終点（Vector3）、色（Color）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateSegment(const Vector3& start, const Vector3& end, const Color& color)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// 位置設定
	primitive->vertices_["start"].position = start;
	primitive->vertices_["end"].position = end;

	// 色設定
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// プリミティブタイプを"線"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::SEGMENT);

	return move(primitive);
}

/*==============================================================
// @brief		三角プリミティブの生成
// @param		１点目（Vector2）、２点目（Vector2）、３点目（Vector2）、色（Color）、塗りつぶすかどうか（bool）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color, bool isFill)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// 位置設定
	primitive->vertices_["p0"].position = Vector3(p1.x, p1.y, 0);
	primitive->vertices_["p1"].position = Vector3(p2.x, p2.y, 0);
	primitive->vertices_["p2"].position = Vector3(p3.x, p3.y, 0);

	// 色設定
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// 塗りつぶししない場合の処理
	primitive->isFill_ = isFill;
	if (!isFill)
	{
		// 始点（１点目）に戻す
		primitive->vertices_["p3"] = primitive->vertices_["p0"];
	}

	// プリミティブタイプを"三角"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::TRIANGLE);

	return move(primitive);
}

/*==============================================================
// @brief		長方形プリミティブの生成
// @param		左上座標（Vector2）、右上座標（Vector2）、色（Color）、塗りつぶすかどうか（bool）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateRectangle(const Vector2& topLeft, const Vector2& bottomRight, const Color& color, bool isFill)
{
	unique_ptr<Primitive2D> primitive = make_unique<Primitive2D>();

	// 位置設定
	primitive->vertices_["p0"].position = Vector3(topLeft.x, topLeft.y, 0);
	primitive->vertices_["p1"].position = Vector3(bottomRight.x, topLeft.y, 0);
	primitive->vertices_["p2"].position = Vector3(bottomRight.x, bottomRight.y, 0);
	primitive->vertices_["p3"].position = Vector3(topLeft.x, bottomRight.y, 0);

	// 色設定
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// 塗りつぶししない場合の処理
	primitive->isFill_ = isFill;
	if (!isFill)
	{
		// 始点（１点目）に戻す
		primitive->vertices_["p4"] = primitive->vertices_["p0"];
	}

	// プリミティブタイプを"長方形"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::RECTANGLE);

	return move(primitive);
}

/*==============================================================
// @brief		直方体プリミティブの生成
// @param		サイズ（Vector3）、色（Color）、塗りつぶすかどうか（bool）
// @return		プリミティブ（unique_ptr<Primitive3D>）
===============================================================*/
unique_ptr<Primitive3D> PrimitiveFactory::CreateBox(const Vector3& size, const Color& color, bool isFill)
{
	unique_ptr<Primitive3D> primitive = make_unique<Primitive3D>();

	// コンテキスト
	ID3D11DeviceContext* context = DeviceResources::GetInstance().GetD3DDeviceContext();

	// 球プリミティブの登録
	primitive->geometry_ = GeometricPrimitive::CreateBox(context, size);

	// 色設定
	primitive->color_ = color;

	// 塗りつぶすかどうか
	primitive->isFill_ = isFill;

	// プリミティブタイプを"直方体"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::BOX);

	return primitive;
}

/*==============================================================
// @brief		円プリミティブの生成
// @param		中心座標（Vector2）、半径（float）、分割数（int）、色（Color）、塗りつぶすかどうか（bool）
// @return		プリミティブ（unique_ptr<Primitive>）
===============================================================*/
unique_ptr<Primitive> PrimitiveFactory::CreateCircle(const Vector2& center, float radius, int div, const Color& color, bool isFill)
{
	unique_ptr<Circle> primitive = make_unique<Circle>();

	// 中心座標を保存
	primitive->vertices_["center"].position = Vector3(center.x, center.y, 0);

	// 半径と分割数を設定
	primitive->radius_ = radius;
	primitive->div_ = div;

	// 頂点データの設定
	string key;
	for (int i = 0; i < div; i++)
	{
		key = "Rad" + to_string(i / 10) + to_string(i % 10);
		primitive->vertices_[key].position.x = center.x + cosf(XM_2PI / div * i) * radius;
		primitive->vertices_[key].position.y = center.y + sinf(XM_2PI / div * i) * radius;
	}
	key = "Rad" + to_string(div / 10) + to_string(div % 10);
	primitive->vertices_[key] = primitive->vertices_["Rad00"];

	// 色設定
	for (auto& vertex : primitive->vertices_)
	{
		vertex.second.color = color;
	}

	// 塗りつぶししない場合の処理
	primitive->isFill_ = isFill;

	// プリミティブタイプを"円"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::CIRCLE);

	return move(primitive);
}

/*==============================================================
// @brief		球プリミティブの生成
// @param		半径（float）、分割数（int）、色（Color）、塗りつぶすかどうか（bool）
// @return		プリミティブ（unique_ptr<Primitive3D>）
===============================================================*/
unique_ptr<Primitive3D> PrimitiveFactory::CreateSphere(float diameter, int div, const Color& color, bool isFill)
{
	unique_ptr<Primitive3D> primitive = make_unique<Primitive3D>();

	// コンテキスト
	ID3D11DeviceContext* context = DeviceResources::GetInstance().GetD3DDeviceContext();

	// 球プリミティブの登録
	//primitive->geometry_ = GeometricPrimitive::CreateSphere(context, diameter, div);

	// 色設定
	primitive->color_ = color;

	// 塗りつぶすかどうか
	primitive->isFill_ = isFill;

	// プリミティブタイプを"球"に設定
	primitive->SetType(Primitive::PRIMITIVE_TYPE::SPHERE);

	return primitive;
}