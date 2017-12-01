/* =====================================================================
//! @param		「MapTip3D」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "MapTip.h"
#include <string>
#include <vector>
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		MapTip3D クラス
	// @content		３Ｄ用マップチップクラス
	*/
	class MapTip3D : public MapTip
	{
	private:
		std::unique_ptr<Object>						dummyObject_;		// 親用ダミーオブジェクト
		std::vector<std::vector<Object>>			object_;			// オブジェクト
		std::vector<std::shared_ptr<Object>>		masterObject_;		// オブジェクト格納用

	public:
		/*
		// @method		コンストラクタ（テクスチャ１つから均等に矩形分割し、読み込む）
		// @param		データ（vector<vector<int>>）
		// @param		モデルファイル名（wstring）
		// @param		データの種類数（int）
		*/
		MapTip3D(std::vector<std::vector<int>> data, const DirectX::SimpleMath::Vector3& tipSize, std::wstring modelFileName[], int typeNum, TipData::TIP_TYPE type[]);

		// デストラクタ
		virtual ~MapTip3D() {}

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

		void SetTranslate(const DirectX::SimpleMath::Vector3& trans) { dummyObject_->SetTranslate(trans); }
	};
}