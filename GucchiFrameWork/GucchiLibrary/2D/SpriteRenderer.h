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
	// クラスの定義（スプライト管理）
	class SpriteRenderer
	{
	private:
		std::list<Sprite> spriteList_;

	public:
		SpriteRenderer() {};
		virtual ~SpriteRenderer() {};

		void RegisterSprite(Sprite* sprite, int order = -1);		// スプライト登録
		void SetActive(Sprite* sprite, bool active);				// アクティブ状態の変更
		void SetOrder(Sprite* sprite, int order);					// 表示順の変更

		void Draw();												// アクティブ状態のスプライトを描画
	};

	// クラスの定義（スプライトの生成）
	class SpriteFactory : public SingletonDirector<SpriteFactory>
	{
	private:
		friend class SingletonDirector<SpriteFactory>;

		SpriteFactory() {};

	public:
		std::unique_ptr<Sprite> CreateSpriteFromFile(const std::wstring fileName, const DirectX::SimpleMath::Vector2& size);
	};
}