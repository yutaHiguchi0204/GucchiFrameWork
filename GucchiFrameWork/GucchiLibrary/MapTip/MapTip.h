/* =====================================================================
//! @param		「MapTipManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"
#include <vector>

namespace GucchiLibrary
{
	/*
	// @class		TipData クラス
	// @content		チップデータクラス
	*/
	class TipData
	{
	public:
		/*
		// @content		チップの属性
		// @mode		NONE	：　特に何もなし
		// @mode		SOLID	：　ブロック
		// @mode		DAMAGE	：　ダメージチップ
		*/
		enum class TIP_TYPE
		{
			NONE,
			SOLID,
			DAMAGE,

			TYPE_NUM
		};

	private:
		int			data_;		// データ
		TIP_TYPE	type_;		// チップ属性

	public:
		// コンストラクタ
		TipData() {}

		// デストラクタ
		virtual ~TipData() {}

		/* アクセッサ */

		void SetData(int data)		{ data_ = data; }
		void SetType(TIP_TYPE type) { type_ = type; }

		inline int GetData() const		{ return data_; }
		inline TIP_TYPE GetType() const { return type_; }
	};

	/*
	// @class		MapTip クラス
	// @content		マップチップクラス
	*/
	class MapTip
	{
	protected:
		std::vector<std::vector<TipData>>	data_;				// データ
		std::vector<TipData::TIP_TYPE>		typeNum_;			// チップの属性
		int									dataTypeNum_;		// データの種類数

	public:
		/*
		// @method		コンストラクタ
		// @param		データ（vector<vector<int>>）
		// @param		データの種類数（int）
		// @param		チップの属性（TIP_TYPE）
		*/
		MapTip(std::vector<std::vector<int>> data, int dataTypeNum, TipData::TIP_TYPE type[]);

		// デストラクタ
		virtual ~MapTip() {}

		/*
		// @method		ResetData
		// @content		マップチップデータリセット
		*/
		virtual void ResetData() = 0;

		/*
		// @method		SetActive
		// @content		アクティブ状態の変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		アクティブ状態（bool）
		*/
		virtual void SetActive(int noX, int noY, bool active) = 0;

		/*
		// @method		ChangeTip（pure）
		// @content		マップチップデータの変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		新データ（int）
		*/
		virtual void ChangeTip(int noX, int noY, int newData) = 0;
	};
}