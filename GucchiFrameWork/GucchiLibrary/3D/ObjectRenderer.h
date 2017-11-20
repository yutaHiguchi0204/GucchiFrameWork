/* =====================================================================
//! @param		「ObjectRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/06
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <CommonStates.h>
#include <Effects.h>
#include <list>
#include <PrimitiveBatch.h>
#include <string>
#include <VertexTypes.h>
#include <wrl/client.h>
#include "Object.h"

namespace GucchiLibrary
{
	// クラスの定義（オブジェクト管理）
	class ObjectRenderer : public SingletonDirector<ObjectRenderer>
	{
	private:
		std::list<Object> objectList_;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> primitiveBatch_;

	private:
		friend class SingletonDirector<ObjectRenderer>;

		ObjectRenderer() {}

	public:
		void Initialize();										// 初期化処理

		void RegisterObject(Object* object);					// オブジェクトの登録
		void SetActive(Object* object, bool active);			// アクティブ状態の変更

		void Draw();											// アクティブ状態のオブジェクトを描画
		void DrawSubtractive();									// アクティブ状態のオブジェクトを減算描画
		void Reset();											// リストリセット

		void SetBlendState(Asset3D::BLEND_MODE mode);			// ブレンド設定
		void SetSubtractive(ID3D11BlendState* blendState);		// 減算描画設定

		void DisableLighting(DirectX::Model* model);			// オブジェクトのライティングを無効にする
	};

	// クラスの定義（オブジェクトの生成）
	class ObjectFactory : public SingletonDirector<ObjectFactory>
	{
	private:
		Camera* camera_;			// 生成したオブジェクトに渡すカメラ

	private:
		friend class SingletonDirector<ObjectFactory>;

		ObjectFactory() {};

	public:
		std::unique_ptr<Object> CreateObjectFromFile(const std::wstring fileName);

		// アクセッサ
		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}