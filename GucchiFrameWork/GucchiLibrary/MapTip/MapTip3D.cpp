/* =====================================================================
//! @param		「MapTip3D」ソース
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */

// ヘッダファイルのインクルード
#include "MapTip3D.h"
#include <cassert>
#include "../3D/ObjectRenderer.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
MapTip3D::MapTip3D(vector<vector<int>> data, const Vector3& tipSize, wstring modelFileName[], int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No object type. Please configuration \"typeNum\".");
		assert(0);
	}

	// ダミーオブジェクト設定
	ObjectRenderer& renderer = ObjectRenderer::GetInstance();
	dummyObject_ = make_unique<Object>();
	renderer.RegisterObject(dummyObject_.get());

	// オブジェクト設定
	ObjectFactory& factory = ObjectFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// オブジェクト生成・登録
		masterObject_.emplace_back(factory.CreateObjectFromFile(modelFileName[i]));
	}

	// オブジェクトデータに反映
	for (int i = 0; i < (int)data_.size(); i++)
	{
		object_.emplace_back();

		for (auto& data : data_[i])
		{
			object_[i].emplace_back(*masterObject_[data.GetData()].get());
		}
	}

	// オブジェクトの登録
	for (int i = 0; i < (int)object_.size(); i++)
	{
		int j = 0;
		for (auto& object : object_[i])
		{
			// 位置の指定
			object.SetTranslate(Vector3(tipSize.x * j, 0.f, tipSize.z * i));

			// 親子関係構築
			object.SetParent(dummyObject_.get());

			j++;
		}
	}
}

/*==============================================================
// @brief		コンテナデータリセット
// @param		なし
// @return		なし
===============================================================*/
void MapTip3D::ResetData()
{
	object_.clear();
	for (auto& data : data_)
	{
		data.clear();
	}
	data_.clear();
	dummyObject_->SetTranslate(Vector3::Zero);
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip3D::SetActive(int noX, int noY, bool active)
{
	object_.at(noY).at(noX).SetActive(active);
}

/*==============================================================
// @brief		マップチップデータの変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、新データ（int）
// @return		なし
===============================================================*/
void MapTip3D::ChangeTip(int noX, int noY, int newData)
{
	data_.at(noY).at(noX).SetData(newData);

	// 新しいスプライトデータに書き換える
	object_.at(noY).at(noX) = *masterObject_.at(data_.at(noY).at(noX).GetData()).get();
}