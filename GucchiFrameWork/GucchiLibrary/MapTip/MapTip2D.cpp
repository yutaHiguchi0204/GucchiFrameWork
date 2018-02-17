/* =====================================================================
//! @param		「MapTip2D」ソース
//! @create		樋口 裕太
//! @date		17/11/30
===================================================================== */

// ヘッダファイルのインクルード
#include "MapTip2D.h"
#include <cassert>
#include "../2D/SpriteRenderer.h"
#include "../System/DebugSystem.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

// コンストラクタ（テクスチャ１つから均等に矩形分割し、読み込む）
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, const wstring& textureName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
		DebugSystem::DebugLog(L"No sprite type. Please configuration \"typeNum\".", true);
		assert(false);
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
		RECT rect = RECT { static_cast<int>(spriteSize.x) * i, 0, static_cast<int>(spriteSize.x) * i + static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y) };

		// スプライト生成・登録
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName, spriteSize, &rect));
	}

	// スプライトデータに反映
	for (int i = 0; i < static_cast<int>(data_.size()); i++)
	{
		sprite_.emplace_back();

		for (auto& tip : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[tip.GetData()].get());
		}
	}

	// スプライトレンダラーに登録
	for (int i = 0; i < static_cast<int>(sprite_.size()); i++)
	{
		for (auto& sprite : sprite_[i])
		{
			renderer.RegisterSprite(&sprite);
		}
	}
}

// コンストラクタ（個々のテクスチャを読み込む）
MapTip2D::MapTip2D(vector<vector<int>> data, const Vector2& spriteSize, wstring* textureName, int typeNum, TipData::TIP_TYPE* type)
	: MapTip(data, typeNum)
{
	if (dataTypeNum_ <= 0)
	{
		DebugSystem::DebugLog(L"No sprite type. Please configuration \"typeNum\".", true);
		assert(false);
	}

	// スプライト設定
	SpriteFactory& factory = SpriteFactory::GetInstance();
	for (int i = 0; i < dataTypeNum_; i++)
	{
		// スプライト生成・登録
		masterSprite_.emplace_back(factory.CreateSpriteFromFile(textureName[i], spriteSize));
	}

	// スプライトデータに反映
	for (int i = 0; i < static_cast<int>(data_.size()); i++)
	{
		sprite_.emplace_back();

		for (auto& tip : data_[i])
		{
			sprite_[i].emplace_back(*masterSprite_[tip.GetData()].get());
		}
	}

	// スプライトレンダラーに登録
	SpriteRenderer& renderer = SpriteRenderer::GetInstance();
	for (int i = 0; i < static_cast<int>(sprite_.size()); i++)
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
// @brief		マップチップデータの変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、新データ（int）
// @return		なし
===============================================================*/
void MapTip2D::ChangeTip(int noX, int noY, int newData)
{
	data_[noY][noX].SetData(newData);

	// 新しいスプライトデータに書き換える
	sprite_[noY][noX] = *masterSprite_[data_[noY][noX].GetData()].get();
}

/*==============================================================
// @brief		マップのアクティブ状態の変更
// @param		アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip2D::SetActive(bool active)
{
	dummySprite_->SetActive(active);
}

/*==============================================================
// @brief		指定したスプライトの位置設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、位置（Vector2）
// @return		なし
===============================================================*/
void MapTip2D::SetSpritePos(int noX, int noY, const Vector2& pos)
{
	sprite_[noY][noX].SetPos(pos);
}

/*==============================================================
// @brief		指定したスプライトのスケール設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、スケール（float）
// @return		なし
===============================================================*/
void MapTip2D::SetSpriteScale(int noX, int noY, float scale)
{
	sprite_[noY][noX].SetScale(scale);
}

/*==============================================================
// @brief		指定したスプライトの回転角設定
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、回転角（float）
// @return		なし
===============================================================*/
void MapTip2D::SetSpriteAngle(int noX, int noY, float angle)
{
	sprite_[noY][noX].SetAngle(angle);
}

/*==============================================================
// @brief		指定したスプライトのアクティブ状態の変更
// @param		変えたいデータの番号x（int）、変えたいデータの番号y（int）、アクティブ状態（bool）
// @return		なし
===============================================================*/
void MapTip2D::SetSpriteActive(int noX, int noY, bool active)
{
	sprite_[noY][noX].SetActive(active);
}

/*==============================================================
// @brief		マップチップとの親子関係構築
// @param		子にしたいスプライト（Sprite*）
// @return		なし
===============================================================*/
void MapTip2D::AddChild(Sprite* sprite)
{
	dummySprite_->AddChild(sprite);
}