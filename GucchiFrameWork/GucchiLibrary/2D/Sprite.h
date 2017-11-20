/* =====================================================================
//! @param		「Sprite」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/17
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>
#include "TextureCache.h"

namespace GucchiLibrary
{
	// クラスの定義
	class Sprite
	{
	private:
		Texture*						texture_;			// テクスチャハンドル
		DirectX::SimpleMath::Vector2	pos_;				// 位置
		DirectX::SimpleMath::Vector2	size_;				// サイズ
		RECT*							textureRect_;		// 画像矩形
		float							scale_;				// 拡大率
		float							angle_;				// 回転角
		bool							isActive_;			// アクティブ状態

	public:
		Sprite(const DirectX::SimpleMath::Vector2& size, const DirectX::SimpleMath::Vector2& pos = DirectX::SimpleMath::Vector2::Zero, RECT* rect = nullptr, float scale = 1.0f, float angle = 0.0f);
		virtual ~Sprite() {};

		void SetTexture(Texture* texture)							{ texture_ = texture; }
		void SetPos(const DirectX::SimpleMath::Vector2& pos)		{ pos_ = pos; }
		void SetSize(const DirectX::SimpleMath::Vector2& size)		{ size_ = size; }
		void SetRect(RECT* rect)									{ textureRect_ = rect; }
		void SetScale(float scale)									{ scale_ = scale; }
		void SetAngle(float angle)									{ angle_ = angle; }
		void SetActive(bool active)									{ isActive_ = active; }

		inline Texture* GetTexture() const							{ return texture_; }
		inline DirectX::SimpleMath::Vector2 GetPos() const			{ return pos_; }
		inline DirectX::SimpleMath::Vector2 GetSize() const			{ return size_; }
		inline RECT* GetRect() const								{ return textureRect_; }
		inline float GetScale() const								{ return scale_; }
		inline float GetAngle() const								{ return angle_; }
		inline bool GetActive() const								{ return isActive_; }

	public:
		// 比較用オペレータ
		bool operator==(const Sprite& sprite) const
		{
			if (texture_		== sprite.GetTexture()	&&
				pos_			== sprite.GetPos()		&&
				size_			== sprite.GetSize()		&&
				textureRect_	== sprite.GetRect()		&&
				scale_			== sprite.GetScale()	&&
				angle_			== sprite.GetAngle()	&&
				isActive_		== sprite.GetActive()
				)
			{
				return true;
			}

			return false;
		}
	};
}