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
	// デフォルトカメラを設定
	camera_ = make_unique<DefaultCamera>(WINDOW_WIDTH, WINDOW_HEIGHT);
	objectFactory_.SetCamera(camera_.get());

	skyDome_ = objectFactory_.CreateObjectFromFile(L"skyDome");

	// オブジェクトの登録
	objectRenderer_.RegisterObject(skyDome_.get());

	// データ取得
	wstring wstr[2] = { L"block", L"block2" };
	TipData::TIP_TYPE type[2] = { TipData::TIP_TYPE::NONE, TipData::TIP_TYPE::SOLID };
	vector<vector<int>> data = CSVFileDirector::LoadCSVFile(L"test");
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
	// カメラの更新
	camera_->Update();
}

/*==============================================================
// @brief		描画処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Draw()
{
	
}

/*==============================================================
// @brief		終了処理
// @param		なし
// @return		なし
===============================================================*/
void PlayScene::Finalize()
{
	
}