/* =====================================================================
//! @param		「SceneManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"
#include <CommonStates.h>
#include <map>
#include <string>
#include "../2D/SpriteRenderer.h"
#include "../2D/TextRenderer.h"
#include "../3D/ObjectRenderer.h"

namespace GucchiLibrary
{
	/*
	// @class		IScene クラス
	// @content		シーンの基底クラス
	*/
	class IScene
	{
	protected:
		// TODO: 共通メンバ
		std::unique_ptr<Camera> camera_;

		// ライブラリインタフェース
		ObjectRenderer&		objectRenderer_		= ObjectRenderer::GetInstance();			// オブジェクト描画用
		ObjectFactory&		objectFactory_		= ObjectFactory::GetInstance();				// オブジェクト生成用
		SpriteRenderer&		spriteRenderer_		= SpriteRenderer::GetInstance();			// スプライト描画用
		SpriteFactory&		spriteFactory_		= SpriteFactory::GetInstance();				// スプライト生成用
		TextRenderer&		textRenderer_		= TextRenderer::GetInstance();				// テキスト描画用

	public:
		// コンストラクタ
		IScene() {}

		// デストラクタ
		virtual ~IScene() {};

		/*
		// @method		Initialize（pure）
		// @content		初期化処理
		*/
		virtual void Initialize() = 0;

		/*
		// @method		Update（pure）
		// @content		更新処理
		*/
		virtual void Update() = 0;

		/*
		// @method		Draw（pure）
		// @content		描画処理
		*/
		virtual void Draw() = 0;

		/*
		// @method		Finalize（pure）
		// @content		終了処理
		*/
		virtual void Finalize() = 0;

		/*
		// @method		ResetDevice
		// @content		ライブラリインタフェースのリセット
		*/
		virtual void ResetDevice();
	};

	/*
	// @class		SceneManager クラス（Singleton）
	// @content		シーンマネージャ
	// @use			RegisterScene関数でシーンを登録しておくことによって、登録されたシーンに容易に変更ができる
	*/
	class SceneManager : public SingletonDirector<SceneManager>
	{
	private:
		std::map<std::string, std::unique_ptr<IScene>> sceneList_;			// 登録されたシーン
		std::string nowScene_;												// 現在のシーン
		std::string beforeScene_;											// 前フレームのシーン

	private:
		friend class SingletonDirector<SceneManager>;

		SceneManager();

	public:
		void Initialize();																// シーンの初期化
		void Update();																	// シーンの更新
		void Draw();																	// シーンの描画
		void Finalize();																// シーンの終了処理

		void RegisterScene(std::string scene, std::unique_ptr<IScene> newScene);		// シーンの登録
		void ChangeScene(std::string scene);											// シーンの変更
		bool CheckScene();																// シーンチェック（前フレームとシーンが異なる場合は描画しない）
	};
}