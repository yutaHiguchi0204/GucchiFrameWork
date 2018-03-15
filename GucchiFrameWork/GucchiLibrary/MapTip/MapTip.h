/* =====================================================================
//! @param		「MapTipManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <vector>
#include "../Common/Element.h"

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
		// @mode		GOAL	：　ゴール
		*/
		enum class TIP_TYPE : int
		{
			NONE,
			SOLID,
			DAMAGE,
			START,
			GOAL,

			TYPE_NUM
		};

	private:
		int			data_;		// データ
		TIP_TYPE	type_;		// チップ属性

	public:
		// コンストラクタ
		TipData() = default;

		// デストラクタ
		virtual ~TipData() = default;

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
	class MapTip : public Element
	{
	protected:
		std::vector<std::vector<TipData>>	data_;				// データ
		int									dataTypeNum_;		// データの種類数

	public:
		/*
		// @method		コンストラクタ
		// @param		データ（vector<vector<int>>）
		// @param		データの種類数（int）
		*/
		MapTip(std::vector<std::vector<int>> data, int dataTypeNum);

		// デストラクタ
		virtual ~MapTip() = default;

		/*
		// @method		ResetData
		// @content		マップチップデータリセット
		*/
		virtual void ResetData() = 0;

		/*
		// @method		ChangeTip（pure）
		// @content		マップチップデータの変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		新データ（int）
		*/
		virtual void ChangeTip(int noX, int noY, int newData) = 0;

		/*
		// @method		SetActive（pure）
		// @content		マップのアクティブ状態の変更
		// @param		アクティブ状態（bool）
		*/
		virtual void SetActive(bool active) override = 0;
	};
}