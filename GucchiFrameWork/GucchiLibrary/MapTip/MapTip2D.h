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
		*/
		MapTip2D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector2& spriteSize, std::wstring textureName, int typeNum, TipData::TIP_TYPE type[]);

		/*
		// @method		コンストラクタ（個々のテクスチャを読み込む）
		// @param		データ（vector<vector<int>>）
		// @param		マップチップデータ１つのスプライトサイズ（Vector2）
		// @param		テクスチャ（wstring[]）
		// @param		データの種類数（int）
		*/
		MapTip2D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector2& spriteSize, std::wstring textureName[], int typeNum, TipData::TIP_TYPE type[]);

		// デストラクタ
		virtual ~MapTip2D() {}

		/*
		// @method		ResetData
		// @content		マップチップデータリセット
		*/
		void ResetData() override;

		/*
		// @method		SetActive
		// @content		アクティブ状態の変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		アクティブ状態（bool）
		*/
		void SetActive(int noX, int noY, bool active) override;

		/*
		// @method		ChangeTip（pure）
		// @content		マップチップデータの変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		新データ（int）
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/* アクセッサ */

		void SetPos(const DirectX::SimpleMath::Vector2& pos) { dummySprite_->SetPos(pos); }
	};
}