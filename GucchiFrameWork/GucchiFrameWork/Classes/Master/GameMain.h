/* =====================================================================
//! @param		「GameMain」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/12
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"

// クラスの定義
class GameMain
{
private:
	// TODO: ここに新しく追加
	std::unique_ptr<GucchiLibrary::Sprite> test_;
	std::unique_ptr<GucchiLibrary::Sprite> test2_;

private:
	// ライブラリインタフェース
	std::unique_ptr<GucchiLibrary::SpriteRenderer> renderer_;									// スプライト描画用（描画したいスプライトをレンダラーに登録してください）
	GucchiLibrary::SpriteFactory& factory_ = GucchiLibrary::SpriteFactory::GetInstance();		// スプライト生成用（スプライトを生成する際に使用してください、画像の使いまわし可）

public:
	GameMain() {};
	virtual ~GameMain() {};

	void Initialize();			// 初期化処理
	void Update();				// 更新処理
	void Render();				// 描画処理
	void Finalize();			// 終了処理
};