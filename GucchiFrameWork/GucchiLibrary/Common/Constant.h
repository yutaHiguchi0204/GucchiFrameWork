/* =====================================================================
//! @param		�萔�w�b�_
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <string>

// �}�X�^�[
const int WINDOW_WIDTH							= 800;
const int WINDOW_HEIGHT							= 600;

// �E�C���h�E�̏ꏊ
#define WINDOW_LEFT(objSizeX)					((objSizeX) / (2))
#define WINDOW_TOP(objSizeY)					((objSizeY) / (2))
#define WINDOW_RIGHT(objSizeX)					((WINDOW_WIDTH) - ((objSizeX) / (2)))
#define WINDOW_BOTTOM(objSizeY)					((WINDOW_HEIGHT) - ((objSizeY) / (2)))
#define WINDOW_MIDDLE							(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))

// �n���h��
const std::wstring FILE_PATH_SPRITE				= L"Resources/SpriteTexture/";			// �X�v���C�g�n���h��

// �g���q
const std::wstring EXT_PNG						= L".png";								// png�t�@�C��