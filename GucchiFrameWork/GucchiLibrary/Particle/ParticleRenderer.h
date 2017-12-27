/* =====================================================================
//! @param		「ParticleRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/12/26
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <d3d11_1.h>
#include <map>
#include <memory>
#include <PrimitiveBatch.h>
#include <SimpleMath.h>
#include <vector>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Emitter.h"
#include "../Camera/Camera.h"

namespace GucchiLibrary
{
	/*
	// @class		ParticleRenderer クラス（Singleton）
	// @content		パーティクル描画用
	*/
	class ParticleRenderer : public SingletonDirector<ParticleRenderer>
	{
	public:
		/*
		// @struct		コンスタントバッファ 構造体
		// @content		パーティクルを描画する際に必要となる情報をまとめた構造体
		*/
		struct Constants
		{
			DirectX::SimpleMath::Matrix wvpMat;			// ワールド・ビュー・プロジェクションの合成行列
			DirectX::SimpleMath::Matrix billboard;		// ビルボード行列
		};

	public:
		static const std::vector<D3D11_INPUT_ELEMENT_DESC>	INPUT_LAYOUT;		// 入力レイアウト
		static const int									MAX_PARTICLE;		// パーティクルの最大数

	private:
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>	primitiveBatch_;		// プリミティブバッチ
		Microsoft::WRL::ComPtr<ID3D11InputLayout>										inputLayout_;			// 入力レイアウト

		Microsoft::WRL::ComPtr<ID3D11VertexShader>										vertexShader_;			// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>									geometryShader_;		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader>										pixelShader_;			// ピクセルシェーダ

		Microsoft::WRL::ComPtr<ID3D11Buffer>											cBuffer_;				// コンスタントバッファ

		Microsoft::WRL::ComPtr<ID3D11SamplerState>										sampler_;				// テクスチャサンプラー

		std::map<std::wstring, Emitter*>												emitter_;				// エミッター

		Camera*																			camera_;				// カメラ

	private:
		friend class SingletonDirector<ParticleRenderer>;

		ParticleRenderer() {}

	public:
		/*
		// @method		Initialize
		// @content		初期化処理
		*/
		void Initialize();

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();

		/*
		// @method		Draw
		// @content		描画処理
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		リストリセット
		*/
		void Reset();

		/*
		// @method		RegisterEmitter
		// @content		エミッターの登録
		// @param		エミッター（Emitter*）
		// @param		エミッター名（wstring）
		// @param		パーティクル用テクスチャファイル名（wstring）
		// @param		エミッターの座標（Vector3）	：	デフォルト（Vector3::Zero）
		*/
		void RegisterEmitter(Emitter* emitter, std::wstring emitterName, std::wstring textureFileName, DirectX::SimpleMath::Vector3 emitterPos = DirectX::SimpleMath::Vector3::Zero);

		/*
		// @method		DisposeEmitter
		// @content		エミッターの解放
		*/
		void DisposeEmitter(std::wstring emitterName);

		/* アクセッサ */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}