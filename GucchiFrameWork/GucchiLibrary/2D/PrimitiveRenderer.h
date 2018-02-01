/* =====================================================================
//! @param		「PrimitiveRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/23
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <Effects.h>
#include <memory>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Primitive.h"

namespace GucchiLibrary
{
	/*
	// @class		PrimitiveRenderer クラス（Singleton）
	// @content		プリミティブ描画用
	*/
	class PrimitiveRenderer : public SingletonDirector<PrimitiveRenderer>
	{
	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	primitiveBatch_;
		std::unique_ptr<DirectX::BasicEffect>									basicEffect_;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>								inputLayout_;

		std::list<Primitive*>													primitiveList_;

	private:
		friend class SingletonDirector<PrimitiveRenderer>;

		PrimitiveRenderer() = default;

	public:
		/*
		// @method		Initialize
		// @content		初期化処理
		*/
		void Initialize();

		/*
		// @method		Draw
		// @content		描画処理
		*/
		void Draw();

		/*
		// @method		DrawPrimitive
		// @content		プリミティブの描画
		// @param		頂点データ（VertexPositionColor*）
		// @param		頂点数（int）
		*/
		void DrawPrimitive(const DirectX::VertexPositionColor* vertices, int vertexCount);

		/*
		// @method		DrawPoint
		// @content		点の描画
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		*/
		void DrawPoint(std::map<std::string, DirectX::SimpleMath::Vector2> vertex, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawLine
		// @content		線の描画
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		*/
		void DrawLine(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawTriangle
		// @content		三角の描画
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		*/
		void DrawTriangle(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawSquare
		// @content		四角の描画
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		*/
		void DrawSquare(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		DrawCircle
		// @content		円の描画
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		*/
		void DrawCircle(std::map<std::string, DirectX::SimpleMath::Vector2> vertices, const DirectX::SimpleMath::Color& color);

		/*
		// @method		RegisterPrimitive
		// @content		プリミティブの登録
		// @param		登録するプリミティブ（Primitive*）
		*/
		void RegisterPrimitive(Primitive* primitive);

		/*
		// @method		SetVertices
		// @content		指定された頂点をもとに頂点データを設定
		// @param		プリミティブタイプ（PRIMITIVE_TYPE）
		// @param		頂点データ（map<string, Vector2>）
		// @param		色（Color）
		// @param		頂点数（int）
		// @return		頂点データ（VertexPositionColor*）
		*/
		DirectX::VertexPositionColor* SetVertices(Primitive::PRIMITIVE_TYPE type, std::map<std::string, DirectX::SimpleMath::Vector2> vertices, DirectX::SimpleMath::Color color, int vertexNum);

		/*
		// @method		GetNumVertex
		// @content		頂点数の取得
		// @param		頂点データ（map<string, Vector2>）
		// @return		頂点数（int）
		*/
		int GetNumVertex(std::map<std::string, DirectX::SimpleMath::Vector2> vertices);

		/*
		// @method		Reset
		// @content		登録されたプリミティブのリストをリセット
		*/
		void Reset();
	};
}