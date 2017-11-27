/* =====================================================================
//! @param		�萔�w�b�_
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <string>

// �}�X�^�[
const int WINDOW_WIDTH							= 800;																					// ��ʂ̕�
const int WINDOW_HEIGHT							= 600;																					// ��ʂ̍���

// �E�C���h�E�̏ꏊ
#define WINDOW_LEFT(objSizeX)					((objSizeX) / (2))																		// ��ʂ̍��[
#define WINDOW_TOP(objSizeY)					((objSizeY) / (2))																		// ��ʂ̏�[
#define WINDOW_RIGHT(objSizeX)					((WINDOW_WIDTH) - ((objSizeX) / (2)))													// ��ʂ̉E�[
#define WINDOW_BOTTOM(objSizeY)					((WINDOW_HEIGHT) - ((objSizeY) / (2)))													// ��ʂ̉��[
#define WINDOW_MIDDLE							(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))			// ��ʂ̒��S

// �n���h��
const std::wstring FILE_PATH_SPRITE				= L"Resources/SpriteTextures/";															// �X�v���C�g�摜�̃t�@�C���n���h��
const std::wstring FILE_PATH_MODEL				= L"Resources/Models/";																	// ���f���̃t�@�C���n���h��
const std::wstring FILE_PATH_FONT				= L"Resources/Fonts/";																	// �t�H���g�̃t�@�C���n���h��

// �g���q
const std::wstring EXT_PNG						= L".png";																				// .png�t�@�C��
const std::wstring EXT_CMO						= L".cmo";																				// .cmo�t�@�C��
const std::wstring EXT_SPRITEFONT				= L".spritefont";																		// .spritefont�t�@�C��