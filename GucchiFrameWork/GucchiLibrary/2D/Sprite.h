/* =====================================================================
//! @param		「Sprite」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <SimpleMath.h>
#include <vector>
#include "TextureCache.h"
#include "../Utility/Interpolater.h"

namespace GucchiLibrary
{
	/*
	// @class		Sprite クラス
	// @content		2D用スプライトリソース
	// @use			SpriteFactoryを使い生成する
	// @use			テクスチャはTextureCacheによって管理される（SpriteFactory内）
	// @use			SpriteRendererに登録することで描画可能（この時オーダー値を変えることで描画順を変更可能）
	*/
	class Sprite
	{
	private:
		Texture*														texture_;			// テクスチャハンドル
		DirectX::SimpleMath::Vector2									pos_;				// 位置
		DirectX::SimpleMath::Vector2									size_;				// サイズ
		RECT*															textureRect_;		// 画像矩形
		float															scale_;				// 拡大率
		float															angle_;				// 回転角
		bool															isActive_;			// アクティブ状態

		Sprite*															parentSprite_;		// 親スプライト
		std::vector<Sprite*>											childSprite_;		// 子スプライト

		bool															isAction_;			// アクション中かどうか

		GucchiLibrary::InterpolateState<DirectX::SimpleMath::Vector2>	interpolateState_;	// 補間ステート

	public:
		/*
		// @method		コンストラクタ
		// @param		スプライトサイズ（Vector2）
		// @param		初期座標（Vector2）　：　デフォルト（Vector2::Zero）
		// @param		矩形取得（RECT*）　：　デフォルト（nullptr）
		// @param		スケール（float）　：　デフォルト（1.0f）
		// @param		回転角（float）　：　デフォルト（0.0f）
		*/
		Sprite(const DirectX::SimpleMath::Vector2& size, const DirectX::SimpleMath::Vector2& pos = DirectX::SimpleMath::Vector2::Zero, RECT* rect = nullptr, float scale = 1.0f, float angle = 0.0f);

		// コピーコンストラクタ
		Sprite(const Sprite& sprite);

		// デストラクタ
		virtual ~Sprite() {}

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update();

		/*
		// @method		SetParent
		// @content		親子関係構築（親設定）
		// @param		親スプライト（Sprite*）
		*/
		void SetParent(Sprite* sprite);

		/*
		// @method		AddChild
		// @content		親子関係構築（子設定）
		// @param		子スプライト（Sprite*）
		*/
		void AddChild(Sprite* sprite);

		/* アクセッサ */

		void SetTexture(Texture* texture)																	{ texture_ = texture; }
		void SetPos(const DirectX::SimpleMath::Vector2& pos)												{ pos_ = pos; }
		void SetSize(const DirectX::SimpleMath::Vector2& size)												{ size_ = size; }
		void SetRect(RECT* rect)																			{ textureRect_ = rect; }
		void SetScale(float scale)																			{ scale_ = scale; }
		void SetAngle(float angle)																			{ angle_ = angle; }
		void SetActive(bool active)																			{ isActive_ = active; }
		void SetIsAction(bool isAction)																		{ isAction_ = isAction; }

		inline Texture* GetTexture() const																	{ return texture_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const													{ return pos_; }
		inline DirectX::SimpleMath::Vector2 GetSize() const													{ return size_; }
		inline RECT* GetRect() const																		{ return textureRect_; }
		inline float GetScale() const																		{ return scale_; }
		inline float GetAngle() const																		{ return angle_; }
		inline bool GetActive() const																		{ return isActive_; }
		inline Sprite* GetParent() const																	{ return parentSprite_; }
		inline std::vector<Sprite*> GetChildren() const														{ return childSprite_; }
		inline bool IsAction() const																		{ return isAction_; }
		inline GucchiLibrary::InterpolateState<DirectX::SimpleMath::Vector2> GetInterpolateState() const	{ return interpolateState_; }

	public:
		// 代入オペレータ
		Sprite& operator=(const Sprite& sprite)
		{
			texture_      = sprite.texture_;
			pos_          = sprite.pos_;
			size_         = sprite.size_;
			textureRect_  = sprite.textureRect_;
			scale_        = sprite.scale_;
			angle_        = sprite.angle_;
			isActive_     = sprite.isActive_;
			parentSprite_ = sprite.parentSprite_;
			childSprite_  = sprite.childSprite_;
			isAction_     = sprite.isAction_;

			return (*this);
		}

		// 比較用オペレータ
		bool operator==(const Sprite& sprite) const
		{
			if (texture_		== sprite.texture_		&&
				pos_			== sprite.pos_			&&
				size_			== sprite.size_			&&
				textureRect_	== sprite.textureRect_	&&
				scale_			== sprite.scale_		&&
				angle_			== sprite.angle_		&&
				isActive_		== sprite.isActive_		&&
				parentSprite_	== sprite.parentSprite_	&&
				childSprite_	== sprite.childSprite_	&&
				isAction_		== sprite.isAction_
				)
			{
				return true;
			}

			return false;
		}
	};
}