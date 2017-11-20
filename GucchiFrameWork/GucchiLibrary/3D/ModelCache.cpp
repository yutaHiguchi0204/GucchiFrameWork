/* =====================================================================
//! @param		「ModelCache」ソース
//! @create		樋口 裕太
//! @date		17/11/15
===================================================================== */

// ヘッダファイルのインクルード
#include "ModelCache.h"
#include "../Common/Constant.h"
#include "../Common/DeviceResources.h"

// 名前空間
using namespace DirectX;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		モデル読み込み
// @param		ファイル名（wstring）、エフェクトファクトリ（EffectFactory*）
// @return		モデル（Model*）
===============================================================*/
Model* ModelCache::LoadModel(const wstring cmoFileName, EffectFactory* factory)
{
	// すでに読み込み済みなら読み込まない
	if (models_.count(cmoFileName) == 0)
	{
		// デバイス準備
		DeviceResources& deviceResources = DeviceResources::GetInstance();

		// モデル準備
		unique_ptr<Model> model = make_unique<Model>();

		// フルパス作成
		wstring fullPath = FILE_PATH_MODEL + cmoFileName + EXT_CMO;

		// モデル作成
		model = Model::CreateFromCMO(deviceResources.GetD3DDevice(), fullPath.c_str(), *factory);

		// モデル格納
		models_[cmoFileName] = std::move(model);
	}

	return models_[cmoFileName].get();
}