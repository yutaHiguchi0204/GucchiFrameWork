/* =====================================================================
//! @param		「SceneManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"
#include <CommonStates.h>

namespace GucchiLibrary
{
	// シーンインタフェース
	class IScene
	{
	public:
		IScene() {};
		virtual ~IScene() {};

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Finalize() = 0;
	};

	// シーンマネージャ
	class SceneManager : public SingletonDirector<SceneManager>
	{
	public:
		enum SCENE
		{
			PLAY
		};

	private:
		SCENE nowScene_;
		SCENE beforeFrameScene_;

	private:
		friend class SingletonDirector<SceneManager>;

		SceneManager();

	public:
		std::unique_ptr<IScene> ChangeScene(SCENE scene);	// シーンの変更
		void Update();										// シーン管理の更新
		bool CheckScene();									// シーンチェック（前フレームとシーンが異なる場合は描画しない）
	};
}