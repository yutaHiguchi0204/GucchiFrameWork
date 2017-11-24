/* =====================================================================
//! @param		「SpriteRenderer」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <list>
#include "Sprite.h"

namespace GucchiLibrary
{
	/*
	// @class		SpriteRenderer クラス（Singleton）
	// @content		スプライト管理用
	// @use			RegisterSprite関数によって登録されたスプライトを描画する
	// @use			シーン遷移時などにReset関数を呼ぶことで登録したスプライトを解放する
	*/
	class SpriteRenderer : public SingletonDirector<SpriteRenderer>
	{
	private:
		std::list<Sprite> spriteList_;

	private:
		friend class SingletonDirector<SpriteRenderer>;

		SpriteRenderer() {};

	public:
		/*
		// @method		RegisterSprite
		// @content		スプライトの登録
		// @param		登録するスプライト（Sprite*）
		// @param		オーダー値（int）　：　デフォルト（-1）
		*/
		void RegisterSprite(Sprite* sprite, int order = -1);

		/*
		// @method		SetActive
		// @content		スプライトのアクティブ状態の変更
		// @param		スプライト（Sprite*）
		// @param		アクティブ状態（bool）
		*/
		void SetActive(Sprite* sprite, bool active);

		/*
		// @method		SetOrder
		// @content		オーダー値の変更
		// @param		スプライト（Sprite*）
		// @param		オーダー値（int）
		*/
		void SetOrder(Sprite* sprite, int order);

		/*
		// @method		Draw
		// @content		アクティブ状態のスプライトを描画
		*/
		void Draw();

		/*
		// @method		Reset
		// @content		登録されたスプライトのリストをリセット
		*/
		void Reset();
	};

	/*
	// @class		SpriteFactory クラス（Singleton）
	// @content		スプライト生成用
	// @use			CreateSpriteFromFile関数を呼ぶことでスプライトを生成する
	*/
	class SpriteFactory : public SingletonDirector<SpriteFactory>
	{
	private:
		friend class SingletonDirector<SpriteFactory>;

		SpriteFactory() {};

	public:
		/*
		// @method		CreateSpriteFromFile
		// @content		指定したテクスチャからスプライトを生成する
		// @param		テクスチャ名（拡張子を除く）（wstring）
		// @param		テクスチャサイズ（Vector2）
		*/
		std::unique_ptr<Sprite> CreateSpriteFromFile(const std::wstring fileName, const DirectX::SimpleMath::Vector2& size);
	};
}