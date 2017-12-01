/* =====================================================================
//! @param		「MapTip2D」ソース
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */

// ヘッダファイルのインクルード
#include "MapTip2D.h"
#include <cassert>
#include "../2D/SpriteRenderer.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ（テクスチャ１つから均等に矩形分割し、読み込む）
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring textureName, int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No sprite type. Please configuration \"typeNum\".");
		assert(0);
	}

	// ダミースプライト設定
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	dummySprite_ = make_unique<Sprite>(Vector2::Zero);
	renderer.RegisterSprite(dummySprite_.get());

	// スプライト設定
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// テクスチャの矩形設定
		RECT rect = RECT { (int)spriteSize.x * i, 0, (int)spriteSize.x * i + (int)spriteSize.x, (int)spriteSize.y };

		// スプライト生成・登録
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName, spriteSize, &rect));
	}

	// スプライトデータに反映
	for (int i = 0; i < (int)data_.size(); i++)
	{
		sprite_.emplace_back();

		for (auto& data : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[data.GetData()].get());
		}
	}

	// スプライトレンダラーに登録
	for (int i = 0; i < (int)sprite_.size(); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

// コンストラクタ（個々のテクスチャを読み込む）
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring textureName[], int typeNum, TipData::TIP_TYPE type[])
	: MapTip(data, typeNum, type)
{
	if (dataTypeNum_ <= 0)
	{
		OutputDebugString(L"No sprite type. Please configuration \"typeNum\".");
		assert(0);
	}

	// スプライト設定
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// スプライト生成・登録
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName[i], spriteSize));
	}

	// スプライトデータに反映
	for (int i = 0; i < (int)data_.size(); i++)
	{
		sprite_.emplace_back();

		for (auto& data : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[data.GetData()].get());
		}
	}

	// スプライトレンダラーに登録
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	for (int i = 0; i < (int)sprite_.size(); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

/*==============================================================
// @brief		コンテナデータリセット
// @param		なし
// @return		なし
===============================================================*/
void MapTip2D::ResetData()
{
	sprite_.clear();
	for (auto& data : data_)
	{
		data.clear();
	}
	data_.clear();
	dummySprite_->SetPos(Vector2::Zero);
}

/*==============================================================
// @brief		アクティブ状態の変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip2D::SetActive(int noX, int noY, bool active)
{
	sprite_.at(noY).at(noX).SetActive(active);
}

/*==============================================================
// @brief		マップチップデータの変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、新データ（int）
// @return		なし
===============================================================*/
void MapTip2D::ChangeTip(int noX, int noY, int newData)
{
	data_.at(noY).at(noX).SetData(newData);

	// 新しいスプライトデータに書き換える
	sprite_.at(noY).at(noX) = *masterSprite_.at(data_.at(noY).at(noX).GetData()).get();
}