/* =====================================================================
//! @param		「Sprite」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <vector>
#include "TextureCache.h"
#include "../Common/Element.h"
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
	class Sprite : public Element
	{
	private:
		Texture*									texture_;				// テクスチャハンドル
		Vector2										pos_;					// 位置
		Vector2										size_;					// サイズ
		RECT*										textureRect_;			// 画像矩形
		Vector2										anchor_;				// アンカーポイント
		float										scale_;					// 拡大率
		float										angle_;					// 回転角
		bool										isActive_;				// アクティブ状態

		Sprite*										parentSprite_;			// 親スプライト
		std::vector<Sprite*>						childSprite_;			// 子スプライト

		bool										isAction_;				// アクション中かどうか

		std::unique_ptr<InterpolateDirector>		interpolateDirector_;	// 補間ステート

	public:
		/*
		// @method		コンストラクタ
		// @param		スプライトサイズ（Vector2）
		// @param		初期座標（Vector2）　：　デフォルト（Vector2::Zero）
		// @param		矩形取得（RECT*）　：　デフォルト（nullptr）
		// @param		スケール（float）　：　デフォルト（1.0f）
		// @param		回転角（float）　：　デフォルト（0.0f）
		*/
		Sprite(const Vector2& size, const Vector2& pos = Vector2::Zero, RECT* rect = nullptr, float scale = 1.0f, float angle = 0.0f);

		// コピーコンストラクタ
		Sprite(const Sprite& sprite);

		// デストラクタ
		virtual ~Sprite() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		void Update() override;

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

		void SetTexture(Texture* texture)								{ texture_ = texture; }
		void SetPos(const Vector2& pos)									{ pos_ = pos; }
		void SetSize(const Vector2& size)								{ size_ = size; }
		void SetRect(RECT* rect)										{ textureRect_ = rect; }
		void SetAnchor(const Vector2& anchor)							{ anchor_ = anchor; }
		void SetScale(float scale)										{ scale_ = scale; }
		void SetAngle(float angle)										{ angle_ = angle; }
		void SetActive(bool active)										{ isActive_ = active; }
		void SetIsAction(bool isAction)									{ isAction_ = isAction; }

		inline Texture* GetTexture() const								{ return texture_; }
		inline const Vector2& GetPos() const							{ return pos_; }
		inline const Vector2& GetSize() const							{ return size_; }
		inline RECT* GetRect() const									{ return textureRect_; }
		inline const Vector2& GetAnchor() const							{ return anchor_; }
		inline float GetScale() const									{ return scale_; }
		inline float GetAngle() const									{ return angle_; }
		inline bool GetActive() const									{ return isActive_; }
		inline Sprite* GetParent() const								{ return parentSprite_; }
		inline std::vector<Sprite*> GetChildren() const					{ return childSprite_; }
		inline bool IsAction() const									{ return isAction_; }
		inline InterpolateDirector* GetInterpolateDirector() const		{ return interpolateDirector_.get(); }

	public:
		// 代入オペレータ
		Sprite& operator=(const Sprite& sprite)
		{
			texture_      = sprite.texture_;
			pos_          = sprite.pos_;
			size_         = sprite.size_;
			textureRect_  = sprite.textureRect_;
			anchor_       = sprite.anchor_;
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
			return 
				texture_		== sprite.texture_		&& 
				pos_			== sprite.pos_			&& 
				size_			== sprite.size_			&& 
				textureRect_	== sprite.textureRect_	&& 
				anchor_			== sprite.anchor_		&& 
				scale_			== sprite.scale_		&& 
				angle_			== sprite.angle_		&& 
				isActive_		== sprite.isActive_		&& 
				parentSprite_	== sprite.parentSprite_	&& 
				childSprite_	== sprite.childSprite_	&& 
				isAction_		== sprite.isAction_;
		}
	};
}