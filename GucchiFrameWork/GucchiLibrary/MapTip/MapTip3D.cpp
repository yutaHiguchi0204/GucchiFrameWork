/* =====================================================================
//! @param		「MapTip3D」ソース
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */

// ヘッダファイルのインクルード
#include "MapTip3D.h"
#include <cassert>
#include "../3D/ObjectRenderer.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ
MapTip3D::MapTip3D(vector<vector<int>> data, const Vector3& tipSize, wstring* modelFileName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
		DebugSystem::DebugLog(L"No object type. Please configuration \"typeNum\".", true);
		assert(false);
	}

	// ダミーオブジェクト設定
	ObjectRenderer& renderer = ObjectRenderer::GetInstance();
	dummyObject_ = make_unique<Object>();
	renderer.RegisterObject(dummyObject_.get());

	// オブジェクト設定
	ObjectFactory& factory = ObjectFactory::GetInstance();
	int typeNo = 0;
	for (int i = 0; i < static_cast<int>(TipData::TIP_TYPE::TYPE_NUM); i++)
	{
		if (i == static_cast<int>(type[typeNo]))
		{
			// オブジェクト生成・登録
			masterObject_.emplace_back(factory.CreateObjectFromFile(modelFileName[typeNo]));
			typeNo++;
		}
		else
		{
			masterObject_.emplace_back(nullptr);
		}
	}

	// オブジェクトデータに反映
	for (int i = 0; i < static_cast<int>(data_.size()); i++)
	{
		object_.emplace_back();

		for (auto& tip : data_[i])
		{
			object_[i].emplace_back(*masterObject_[tip.GetData()].get());
		}
	}

	// オブジェクトの登録
	for (int i = 0; i < static_cast<int>(object_.size()); i++)
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
// @brief		マップのアクティブ状態の変更
// @param		アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip3D::SetActive(bool active)
{
	dummyObject_->SetActive(active);
}

/*==============================================================
// @brief		マップチップデータの変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、新データ（int）
// @return		なし
===============================================================*/
void MapTip3D::ChangeTip(int noX, int noY, int newData)
{
	data_[noY][noX].SetData(newData);

	// 新しいスプライトデータに書き換える
	object_[noY][noX] = *masterObject_[data_[noY][noX].GetData()].get();
}

/*==============================================================
// @brief		指定したオブジェクトの平行移動設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、平行移動（Vector3）
// @return		なし
===============================================================*/
void MapTip3D::SetObjectTranslate(int noX, int noY, const Vector3& trans)
{
	object_[noY][noX].SetTranslate(trans);
}

/*==============================================================
// @brief		指定したオブジェクトのスケール設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、スケール（Vector3）
// @return		なし
===============================================================*/
void MapTip3D::SetObjectScale(int noX, int noY, const Vector3& scale)
{
	object_[noY][noX].SetScale(scale);
}

/*==============================================================
// @brief		指定したオブジェクトの回転角設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、回転角（Vector3）
// @return		なし
===============================================================*/
void MapTip3D::SetObjectRotate(int noX, int noY, const Vector3& rot)
{
	object_[noY][noX].SetRotate(rot);
}

/*==============================================================
// @brief		指定したオブジェクトのアクティブ状態の変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip3D::SetObjectActive(int noX, int noY, bool active)
{
	object_[noY][noX].SetActive(active);
}

/*==============================================================
// @brief		マップチップとの親子関係構築
// @param		子にしたいオブジェクト（Object*）
// @return		なし
===============================================================*/
void MapTip3D::AddChild(Object* object)
{
	dummyObject_->AddChild(object);
}