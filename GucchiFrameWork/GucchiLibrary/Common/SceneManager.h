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
	// シーンインタフェース
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
		IScene() {}
		virtual ~IScene() {};

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Finalize() = 0;

		virtual void ResetDevice();
	};

	// シーンマネージャ
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