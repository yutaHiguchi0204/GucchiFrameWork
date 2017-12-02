/* =====================================================================
//! @param		「SceneManager」ソース
//! @create		樋口 裕太
//! @date		17/10/30
===================================================================== */

// ヘッダファイルのインクルード
#include "PlayScene.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiLibrary;
using namespace std;

// メンバ関数の定義

/*==============================================================
// @brief		初期化処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Initialize()
{
	// 全シーン共通初期化処理
	IScene::CommonInitialize();

	// データ取得
	wstring wstr[2] = { L"block", L"block2" };
	TipData::TIP_TYPE type[2] = { TipData::TIP_TYPE::NONE, TipData::TIP_TYPE::SOLID };
	vector<vector<int>> data = CSVFileManager::LoadCSVFile(L"test");
	stage_ = make_unique<MapTip3D>(data, Vector3::One, wstr, 2, type);
	stage_->SetTranslate(Vector3(-2.f, 0.f, -2.f));
}

/*==============================================================
// @brief		更新処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Update()
{
	// 全シーン共通更新処理
	IScene::CommonUpdate();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Draw()
{
	// 全シーン共通描画処理
	IScene::CommonDraw();
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Finalize()
{
	// 全シーン共通終了処理
	IScene::CommonFinalize();
}