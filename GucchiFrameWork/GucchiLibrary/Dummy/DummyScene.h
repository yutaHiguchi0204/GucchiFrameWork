/* =====================================================================
//! @param		「DummyScene」ヘッダ
//! @create		樋口 裕太
//! @date		yy/mm/dd
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "GucchiLibrary.h"

// クラスの定義
class DummyScene : public GucchiLibrary::IScene
{
private:
	// TODO: DummySceneのメンバ

	// ライブラリインタフェース（複数回使用する際はメンバとして持っといたほうがいいです）

public:
	// コンストラクタ
	DummyScene() = default;

	// デストラクタ
	virtual ~DummyScene() = default;

	/*
	// @method		Initialize
	// @content		初期化処理
	*/
	void Initialize() override;

	/*
	// @method		Update
	// @content		更新処理
	*/
	void Update() override;

	/*
	// @method		Draw
	// @content		描画処理
	*/
	void Draw() override;

	/*
	// @method		Finalize
	// @content		終了処理
	*/
	void Finalize() override;
};