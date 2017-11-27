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
#include <string>
#include <wrl/client.h>
#include "Object.h"

namespace GucchiLibrary
{
	/*
	// @class		ObjectRenderer クラス（Singleton）
	// @content		オブジェクト管理用
	// @use			RegisterObject関数によって登録されたオブジェクトを描画する
	// @use			シーン遷移時などにReset関数を呼ぶことで登録したオブジェクトを解放する
	*/
	class ObjectRenderer : public SingletonDirector<ObjectRenderer>
	{
	private:
		std::list<Object> objectList_;

	private:
		friend class SingletonDirector<ObjectRenderer>;

		ObjectRenderer() {}

	public:
		/*
		// @method		RegisterObject
		// @content		オブジェクトの登録
		// @param		登録するオブジェクト（Object*）
		*/
		void RegisterObject(Object* object);

		/*
		// @method		SetActive
		// @content		オブジェクトのアクティブ状態の変更
		// @param		オブジェクト（Object*）
		// @param		アクティブ状態（bool）
		*/
		void SetActive(Object* object, bool active);

		/*
		// @method		Update
		// @content		アクティブ状態のオブジェクトを更新
		*/
		void Update();

		/*
		// @method		Draw
		// @content		アクティブ状態のオブジェクトを描画
		*/
		void Draw();

		/*
		// @method		DrawObject
		// @content		オブジェクトの描画
		// @param		オブジェクト（Object*）
		*/
		void DrawObject(Object* sprite);

		/*
		// @method		GetParentObjectPos
		// @content		親の位置を辿る
		// @param		親オブジェクト（Sprite*）
		// @return		最終位置（Matrix）
		*/
		DirectX::SimpleMath::Matrix GetParentObjectMatrix(Object* sprite);

		/*
		// @method		Reset
		// @content		登録されたオブジェクトのリストをリセット
		*/
		void Reset();

		/*
		// @method		SetBlendState
		// @content		ブレンドモード設定
		// @param		ブレンドモード（BLEND_MODE）
		*/
		void SetBlendState(Asset3D::BLEND_MODE mode);

		/*
		// @method		SetSubtractive
		// @content		減算描画設定
		// @param		減算描画用ステート（ID3D11BlendState*）
		*/
		void SetSubtractive(ID3D11BlendState* blendState);

		/*
		// @method		DisableLighting
		// @content		モデルのライティングを無効にする
		// @param		モデル（Model*）
		*/
		void DisableLighting(DirectX::Model* model);
	};

	/*
	// @class		ObjectFactory クラス（Singleton）
	// @content		オブジェクト生成用
	// @use			CreateObjectFromFile関数を呼ぶことでオブジェクトを生成する
	*/
	class ObjectFactory : public SingletonDirector<ObjectFactory>
	{
	private:
		Camera* camera_;			// 生成したオブジェクトに渡すカメラ

	private:
		friend class SingletonDirector<ObjectFactory>;

		ObjectFactory() {}

	public:
		/*
		// @method		CreateObjectFromFile
		// @content		指定したcmoファイルからオブジェクトを生成する
		// @param		モデルファイル名（拡張子を除く）（wstring）
		// @return		オブジェクト（unique_ptr<Object>）
		*/
		std::unique_ptr<Object> CreateObjectFromFile(const std::wstring fileName);

		/* アクセッサ */

		void SetCamera(Camera* camera) { camera_ = camera; }
	};
}