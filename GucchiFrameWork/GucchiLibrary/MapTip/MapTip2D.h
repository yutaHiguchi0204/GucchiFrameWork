/* =====================================================================
//! @param		「MapTip2D」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "MapTip.h"
#include "../2D/Sprite.h"

namespace GucchiLibrary
{
	/*
	// @class		MapTip2D クラス
	// @content		２Ｄ用マップチップクラス
	*/
	class MapTip2D : public MapTip
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;

	private:
		std::unique_ptr<Sprite>						dummySprite_;		// 親用ダミースプライト
		std::vector<std::vector<Sprite>>			sprite_;			// スプライトデータ
		std::vector<std::shared_ptr<Sprite>>		masterSprite_;		// スプライト格納用

	public:
		/*
		// @method		コンストラクタ（テクスチャ１つから均等に矩形分割し、読み込む）
		// @param		データ（vector<vector<int>>）
		// @param		マップチップデータ１つのスプライトサイズ（Vector2）
		// @param		テクスチャ名（横長の均等にテクスチャが割り振られてるものにしてください）（wstring）
		// @param		データの種類数（int）
		// @param		チップの属性（TIP_TYPE[]）
		*/
		MapTip2D(std::vector<std::vector<int>> data, const Vector2& spriteSize, std::wstring textureName, int typeNum, TipData::TIP_TYPE* type);

		/*
		// @method		コンストラクタ（個々のテクスチャを読み込む）
		// @param		データ（vector<vector<int>>）
		// @param		マップチップデータ１つのスプライトサイズ（Vector2）
		// @param		テクスチャ（wstring[]）
		// @param		データの種類数（int）
		// @param		チップの属性（TIP_TYPE[]）
		*/
		MapTip2D(std::vector<std::vector<int>> data, const Vector2& spriteSize, std::wstring* textureName, int typeNum, TipData::TIP_TYPE* type);

		// デストラクタ
		virtual ~MapTip2D() = default;

		/*
		// @method		ResetData
		// @content		マップチップデータリセット
		*/
		void ResetData() override;

		/*
		// @method		ChangeTip（pure）
		// @content		マップチップデータの変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		新データ（int）
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/*
		// @method		SetSpritePos
		// @content		指定したスプライトの位置設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		位置（Vector2）
		*/
		void SetSpritePos(int noX, int noY, const Vector2& pos);

		/*
		// @method		SetSpriteScale
		// @content		指定したスプライトのスケール設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		スケール（float）
		*/
		void SetSpriteScale(int noX, int noY, float scale);

		/*
		// @method		SetSpriteAngle
		// @content		指定したスプライトの回転角設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		回転角（float）
		*/
		void SetSpriteAngle(int noX, int noY, float angle);

		/*
		// @method		SetSpriteActive
		// @content		指定したスプライトのアクティブ状態の変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		アクティブ状態（bool）
		*/
		void SetSpriteActive(int noX, int noY, bool active);

		/*
		// @method		AddChild
		// @content		マップチップとの親子関係構築
		// @param		子にしたいスプライト（Sprite*）
		*/
		void AddChild(Sprite* sprite);

		/* アクセッサ */

		void SetPos(const Vector2& pos)														{ dummySprite_->SetPos(pos); }

		inline const Vector2& GetPos() const												{ return dummySprite_->GetPos(); }
		inline int GetSpritesRowNum() const													{ return static_cast<int>(sprite_.size()); }
		inline int GetSpritesColumnNum(int row) const										{ return static_cast<int>(sprite_[row].size()); }
		inline const Vector2& GetSpritePos(int noX, int noY) const							{ return sprite_[noY][noX].GetPos(); }
		inline float GetSpriteScale(int noX, int noY) const									{ return sprite_[noY][noX].GetScale(); }
		inline float GetSpriteAngle(int noX, int noY) const									{ return sprite_[noY][noX].GetAngle(); }
		inline InterpolateDirector* GetSpriteInterpolateDirector(int noX, int noY) const	{ return sprite_[noY][noX].GetInterpolateDirector(); }
	};
}