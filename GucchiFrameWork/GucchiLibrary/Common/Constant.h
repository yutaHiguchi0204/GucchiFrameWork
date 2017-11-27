/* =====================================================================
//! @param		定数ヘッダ
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <string>

// マスター
const int WINDOW_WIDTH							= 800;																					// 画面の幅
const int WINDOW_HEIGHT							= 600;																					// 画面の高さ

// ウインドウの場所
#define WINDOW_LEFT(objSizeX)					((objSizeX) / (2))																		// 画面の左端
#define WINDOW_TOP(objSizeY)					((objSizeY) / (2))																		// 画面の上端
#define WINDOW_RIGHT(objSizeX)					((WINDOW_WIDTH) - ((objSizeX) / (2)))													// 画面の右端
#define WINDOW_BOTTOM(objSizeY)					((WINDOW_HEIGHT) - ((objSizeY) / (2)))													// 画面の下端
#define WINDOW_MIDDLE							(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))			// 画面の中心

// ハンドル
const std::wstring FILE_PATH_SPRITE				= L"Resources/SpriteTextures/";															// スプライト画像のファイルハンドル
const std::wstring FILE_PATH_MODEL				= L"Resources/Models/";																	// モデルのファイルハンドル
const std::wstring FILE_PATH_FONT				= L"Resources/Fonts/";																	// フォントのファイルハンドル

// 拡張子
const std::wstring EXT_PNG						= L".png";																				// .pngファイル
const std::wstring EXT_CMO						= L".cmo";																				// .cmoファイル
const std::wstring EXT_SPRITEFONT				= L".spritefont";																		// .spritefontファイル