/* =====================================================================
//! @param		「SceneManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"
#include "../2D/SpriteRenderer.h"
#include "../2D/TextRenderer.h"
#include "../3D/ObjectRenderer.h"
#include "../Particle/ParticleRenderer.h"
#include "../Primitive/PrimitiveRenderer.h"
#include "../Sound/SoundManager.h"

namespace GucchiLibrary
{
	/*
	// @class		IScene クラス
	// @content		シーンの基底クラス
	*/
	class IScene
	{
	protected:
		using Vector2    = DirectX::SimpleMath::Vector2;
		using Vector3    = DirectX::SimpleMath::Vector3;
		using Vector4    = DirectX::SimpleMath::Vector4;
		using Color      = DirectX::SimpleMath::Color;
		using Matrix     = DirectX::SimpleMath::Matrix;
		using Quaternion = DirectX::SimpleMath::Quaternion;

	protected:
		// TODO: 共通メンバ
		std::unique_ptr<Object> skyDome_;		// 天球
		std::unique_ptr<Camera> camera_;		// カメラ

		// ライブラリインタフェース
		ObjectRenderer&			objectRenderer_			= ObjectRenderer::GetInstance();			// オブジェクト描画用
		ObjectFactory&			objectFactory_			= ObjectFactory::GetInstance();				// オブジェクト生成用
		ParticleRenderer&		particleRenderer_		= ParticleRenderer::GetInstance();			// パーティクル描画用
		PrimitiveRenderer&		primitiveRenderer_		= PrimitiveRenderer::GetInstance();			// プリミティブ描画用
		SpriteRenderer&			spriteRenderer_			= SpriteRenderer::GetInstance();			// スプライト描画用
		SpriteFactory&			spriteFactory_			= SpriteFactory::GetInstance();				// スプライト生成用
		TextRenderer&			textRenderer_			= TextRenderer::GetInstance();				// テキスト描画用
		SoundManager&			soundManager_			= SoundManager::GetInstance();				// サウンドマネージャ

	public:
		// コンストラクタ
		IScene() = default;

		// デストラクタ
		virtual ~IScene() = default;

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
		// @method		CommonInitialize
		// @content		全シーン共通の初期化処理
		*/
		virtual void CommonInitialize();

		/*
		// @method		CommonUpdate
		// @content		全シーン共通の更新処理
		*/
		virtual void CommonUpdate();

		/*
		// @method		CommonDraw
		// @content		全シーン共通の描画処理
		*/
		virtual void CommonDraw();

		/*
		// @method		CommonFinalize
		// @content		全シーン共通の終了処理
		*/
		virtual void CommonFinalize();

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
		// @method		Finalize
		// @content		終了処理
		*/
		void Finalize();

		/*
		// @method		RegisterScene
		// @content		シーンの登録
		// @param		シーン名（string）
		// @param		シーンインスタンス（unique_ptr<IScene>）
		*/
		void RegisterScene(std::string scene, std::unique_ptr<IScene> newScene);

		/*
		// @method		ChangeScene
		// @content		シーンの変更
		// @param		シーン名（string）
		// @param		シーンインスタンス（unique_ptr<IScene>）
		*/
		void ChangeScene(std::string scene, std::unique_ptr<IScene> newScene);

		/*
		// @method		CheckScene
		// @content		前フレームとシーンが同じかどうかをチェックする（異なる場合はDrawを呼ばない）
		// @return		結果（bool）
		*/
		bool CheckScene();
	};
}