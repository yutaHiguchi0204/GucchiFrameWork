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
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	/*
	// @class		PrimitiveRenderer クラス（Singleton）
	// @content		プリミティブ描画用
	*/
	class PrimitiveRenderer : public SingletonDirector<PrimitiveRenderer>
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix  = DirectX::SimpleMath::Matrix;
		using Color   = DirectX::SimpleMath::Color;

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>	primitiveBatch_;		// プリミティブバッチ
		std::unique_ptr<DirectX::BasicEffect>									basicEffect_;			// エフェクト
		Microsoft::WRL::ComPtr<ID3D11InputLayout>								inputLayout_;			// 入力レイアウト

		std::list<Primitive*>													primitiveList_;			// プリミティブリスト

		Camera*																	camera_;				// カメラ

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
		// @method		Draw2D
		// @content		２Ｄ用描画処理
		// @param		２Ｄプリミティブ（Primitive2D*）
		// @param		プリミティブタイプ（PRIMITIVE_TYPE）
		*/
		void Draw2D(Primitive2D* primitive, Primitive::PRIMITIVE_TYPE type);

		/*
		// @method		Draw3D
		// @content		３Ｄ用描画処理
		// @param		３Ｄプリミティブ（Primitive3D*）
		*/
		void Draw3D(Primitive3D* primitive);

		/*
		// @method		GetVerticesArray
		// @content		描画用にまとめられた頂点データの配列を取得
		// @param		プリミティブ（Primitive2D*）
		// @return		頂点データ配列（VertexPositionColor*）
		*/
		DirectX::VertexPositionColor* GetVerticesArray(Primitive2D* primitive);

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
		// @param		頂点データ（map<string, VertexPositionColor>）
		*/
		void DrawPoint(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawSegment
		// @content		線分の描画
		// @param		頂点データ（map<string, VertexPositionColor>）
		*/
		void DrawSegment(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawTriangle
		// @content		三角の描画
		// @param		頂点データ（map<string, VertexPositionColor>）
		*/
		void DrawTriangle(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawRectangle
		// @content		四角の描画
		// @param		頂点データ（map<string, VertexPositionColor>）
		*/
		void DrawRectangle(std::map<std::string, DirectX::VertexPositionColor> vertices);

		/*
		// @method		DrawCircle
		// @content		円の描画
		// @param		頂点データ（map<string, VertexPositionColor>）
		// @param		分割数（int）
		*/
		void DrawCircle(std::map<std::string, DirectX::VertexPositionColor> vertices, int div);

		/*
		// @method		RegisterPrimitive
		// @content		プリミティブの登録
		// @param		登録するプリミティブ（Primitive*）
		*/
		void RegisterPrimitive(Primitive* primitive);

		/*
		// @method		DisposePrimitive
		// @content		プリミティブの解放
		// @param		解放するプリミティブ（Primitive*）
		*/
		void DisposePrimitive(Primitive* primitive);

		/*
		// @method		Reset
		// @content		登録されたプリミティブのリストをリセット
		*/
		void Reset();

		/* アクセッサ */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};

	/*
	// @class		PrimitiveFactory クラス
	// @content		プリミティブ生成用
	*/
	class PrimitiveFactory
	{
	public:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Color = DirectX::SimpleMath::Color;

	public:
		/*
		// @method		CreatePoint（static）
		// @content		点プリミティブの生成
		// @param		座標（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreatePoint(const Vector2& point, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreatePoint（static）
		// @content		点プリミティブの生成
		// @param		座標（Vector3）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreatePoint(const Vector3& point, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateSegment（static）
		// @content		線分プリミティブの生成
		// @param		始点（Vector2）
		// @param		終点（Vector2）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreateSegment(const Vector2& start, const Vector2& end, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateSegment（static）
		// @content		線分プリミティブの生成
		// @param		始点（Vector3）
		// @param		終点（Vector3）
		// @param		色（Color）	：	デフォルト（Color(1, 1, 1, 1)）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreateSegment(const Vector3& start, const Vector3& end, const Color& color = Color(1, 1, 1, 1));

		/*
		// @method		CreateTriangle（static）
		// @content		三角プリミティブの生成
		// @param		１点目（Vector2）
		// @param		２点目（Vector2）
		// @param		３点目（Vector2）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		// @param		塗りつぶすかどうか（bool）	：	デフォルト（false）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreateTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateRectangle（static）
		// @content		長方形プリミティブの生成
		// @param		左上座標（Vector2）
		// @param		右下座標（Vector2）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		// @param		塗りつぶすかどうか（bool）	：	デフォルト（false）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreateRectangle(const Vector2& topLeft, const Vector2& bottomRight, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateBox（static）
		// @content		直方体プリミティブの生成
		// @param		サイズ（Vector3）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		// @param		塗りつぶすかどうか（bool）	：	デフォルト（false）
		// @return		プリミティブ（unique_ptr<Primitive3D>）
		*/
		static std::unique_ptr<Primitive3D> CreateBox(const Vector3& size, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateCircle（static）
		// @content		円プリミティブの生成
		// @param		中心座標（Vector2）
		// @param		半径（float）
		// @param		分割数（int）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		// @param		塗りつぶすかどうか（bool）	：	デフォルト（false）
		// @return		プリミティブ（std::unique_ptr<Primitive>）
		*/
		static std::unique_ptr<Primitive> CreateCircle(const Vector2& center, float radius, int div, const Color& color = Color(1, 1, 1, 1), bool isFill = false);

		/*
		// @method		CreateSphere（static）
		// @content		球プリミティブの生成
		// @param		直径（float）
		// @param		分割数（int）
		// @param		色（Color）					：	デフォルト（Color(1, 1, 1, 1)）
		// @param		塗りつぶすかどうか（bool）	：	デフォルト（false）
		// @return		プリミティブ（unique_ptr<Primitive3D>）
		*/
		static std::unique_ptr<Primitive3D> CreateSphere(float diameter, int div, const Color& color = Color(1, 1, 1, 1), bool isFill = false);
	};
}