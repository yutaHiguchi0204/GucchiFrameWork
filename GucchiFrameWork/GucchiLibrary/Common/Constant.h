/* =====================================================================
//! @param		定数ヘッダ
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>

// マスター
const int								WINDOW_WIDTH			= 800;															// 画面の幅
const int								WINDOW_HEIGHT			= 600;															// 画面の高さ
const float								FRAME_PER_SECOND		= 60.0f;														// １秒６０フレーム

// ウインドウの場所
#define WINDOW_LEFT(objSizeX)			((objSizeX) / (2))																		// 画面の左端
#define WINDOW_TOP(objSizeY)			((objSizeY) / (2))																		// 画面の上端
#define WINDOW_RIGHT(objSizeX)			((WINDOW_WIDTH) - ((objSizeX) / (2)))													// 画面の右端
#define WINDOW_BOTTOM(objSizeY)			((WINDOW_HEIGHT) - ((objSizeY) / (2)))													// 画面の下端
#define WINDOW_MIDDLE					(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))			// 画面の中心
#define WINDOW_MIDDLE_X					((WINDOW_WIDTH) / (2))																	// 画面のx座標の中心
#define WINDOW_MIDDLE_Y					((WINDOW_HEIGHT) / (2))																	// 画面のy座標の中心

// アンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_LT				= DirectX::SimpleMath::Vector2(0.0f, 0.0f);						// 左上のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_LM				= DirectX::SimpleMath::Vector2(0.0f, 0.5f);						// 左中のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_LB				= DirectX::SimpleMath::Vector2(0.0f, 1.0f);						// 左下のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_MT				= DirectX::SimpleMath::Vector2(0.5f, 0.0f);						// 中上のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_MM				= DirectX::SimpleMath::Vector2(0.5f, 0.5f);						// 中中のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_MB				= DirectX::SimpleMath::Vector2(0.5f, 1.0f);						// 中下のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_RT				= DirectX::SimpleMath::Vector2(1.0f, 0.0f);						// 右上のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_RM				= DirectX::SimpleMath::Vector2(1.0f, 0.5f);						// 右中のアンカーポイント
const DirectX::SimpleMath::Vector2		ANCHOR_RB				= DirectX::SimpleMath::Vector2(1.0f, 1.0f);						// 右下のアンカーポイント

// ハンドル
const std::wstring						FILE_PATH_SPRITE		= L"Resources/SpriteTextures/";									// スプライト画像のファイルハンドル
const std::wstring						FILE_PATH_MODEL			= L"Resources/Models/";											// モデルのファイルハンドル
const std::wstring						FILE_PATH_FONT			= L"Resources/Fonts/";											// フォントのファイルハンドル

// 拡張子
const std::wstring						EXT_PNG					= L".png";														// .pngファイル
const std::wstring						EXT_CMO					= L".cmo";														// .cmoファイル
const std::wstring						EXT_CSO					= L".cso";														// .csoファイル
const std::wstring						EXT_SPRITEFONT			= L".spritefont";												// .spritefontファイル