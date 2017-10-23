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
#define WINDOW_LEFT								(0)
#define WINDOW_TOP								(0)
#define WINDOW_RIGHT(objSizeX)					((WINDOW_WIDTH) - (objSizeX))
#define WINDOW_BOTTOM(objSizeY)					((WINDOW_HEIGHT) - (objSizeY))
#define WINDOW_MIDDLE(objSizeX, objSizeY)		(DirectX::SimpleMath::Vector2((WINDOW_WIDTH / 2) - (objSizeX / 2), (WINDOW_HEIGHT / 2) - (objSizeY / 2)))

// ハンドル
const std::wstring FILE_PATH_SPRITE				= L"Resources/SpriteTexture/";			// スプライトハンドル

// 拡張子
const std::wstring EXT_PNG						= L".png";								// pngファイル