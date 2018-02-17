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
		using Vector3 = DirectX::SimpleMath::Vector3;

	private:
		std::unique_ptr<Object>						dummyObject_;		// 親用ダミーオブジェクト
		std::vector<std::vector<Object>>			object_;			// オブジェクト
		std::vector<std::shared_ptr<Object>>		masterObject_;		// オブジェクト格納用

	public:
		/*
		// @method		コンストラクタ（テクスチャ１つから均等に矩形分割し、読み込む）
		// @param		データ（vector<vector<int>>）
		// @param		マップチップデータ１つのオブジェクトサイズ（Vector3）
		// @param		モデルファイル名（wstring[]）
		// @param		データの種類数（int）
		// @param		チップの属性（TIP_TYPE[]）
		*/
		MapTip3D(std::vector<std::vector<int>> data, const Vector3& tipSize, std::wstring* modelFileName, int typeNum, TipData::TIP_TYPE* type);

		// デストラクタ
		virtual ~MapTip3D() = default;

		/*
		// @method		ResetData
		// @content		マップチップデータリセット
		*/
		void ResetData() override;

		/*
		// @method		SetActive
		// @content		マップのアクティブ状態の変更
		// @param		アクティブ状態（bool）
		*/
		void SetActive(bool active) override;

		/*
		// @method		ChangeTip
		// @content		マップチップデータの変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		新データ（int）
		*/
		void ChangeTip(int noX, int noY, int newData) override;

		/*
		// @method		SetObjectTranslate
		// @content		指定したオブジェクトの平行移動設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		平行移動（Vector3）
		*/
		void SetObjectTranslate(int noX, int noY, const Vector3& trans);

		/*
		// @method		SetObjectScale
		// @content		指定したオブジェクトのスケール設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		スケール（Vector3）
		*/
		void SetObjectScale(int noX, int noY, const Vector3& scale);

		/*
		// @method		SetObjectRotate
		// @content		指定したオブジェクトの回転角設定
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		回転角（Vector3）
		*/
		void SetObjectRotate(int noX, int noY, const Vector3& rot);

		/*
		// @method		SetObjectActive
		// @content		指定したオブジェクトのアクティブ状態の変更
		// @param		変えたいデータの番号x（int）
		// @param		変えたいデータの番号y（int）
		// @param		アクティブ状態（bool）
		*/
		void SetObjectActive(int noX, int noY, bool active);

		/*
		// @method		AddChild
		// @content		マップチップとの親子関係構築
		// @param		子にしたいオブジェクト（Object*）
		*/
		void AddChild(Object* object);

		/* アクセッサ */

		void SetTranslate(const Vector3& trans)											{ dummyObject_->SetTranslate(trans); }

		inline const Vector3& GetTranslate() const										{ return dummyObject_->GetTranslate(); }
		inline int GetObjectsRowNum() const												{ return static_cast<int>(object_.size()); }
		inline int GetObjectsColumnNum(int row) const									{ return static_cast<int>(object_[row].size()); }
		inline const Vector3& GetObjectTranslate(int noX, int noY) const				{ return object_[noY][noX].GetTranslate(); }
		inline const Vector3& GetObjectScale(int noX, int noY) const					{ return object_[noY][noX].GetScale(); }
		inline const Vector3& GetObjectRotate(int noX, int noY) const					{ return object_[noY][noX].GetRotate(); }
		inline InterpolateDirector* GetObjectInterpolateState(int noX, int noY) const	{ return object_[noY][noX].GetInterpolateDirector(); }
	};
}