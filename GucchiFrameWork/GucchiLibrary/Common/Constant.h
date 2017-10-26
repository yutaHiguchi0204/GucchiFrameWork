/* =====================================================================
//! @param		定数ヘッダ
//! @create		樋口 裕太
//! @date		17/10/11
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <string>

// マスター
const int WINDOW_WIDTH							= 800;
const int WINDOW_HEIGHT							= 600;

// ウインドウの場所
#define WINDOW_LEFT(objSizeX)					((objSizeX) / (2))
#define WINDOW_TOP(objSizeY)					((objSizeY) / (2))
#define WINDOW_RIGHT(objSizeX)					((WINDOW_WIDTH) - ((objSizeX) / (2)))
#define WINDOW_BOTTOM(objSizeY)					((WINDOW_HEIGHT) - ((objSizeY) / (2)))
#define WINDOW_MIDDLE							(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))

// ハンドル
const std::wstring FILE_PATH_SPRITE				= L"Resources/SpriteTexture/";			// スプライトハンドル

// 拡張子
const std::wstring EXT_PNG						= L".png";								// pngファイル