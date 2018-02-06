/* =====================================================================
//! @param		�萔�w�b�_
//! @create		��� �T��
//! @date		17/10/11
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>

// �}�X�^�[
const int								WINDOW_WIDTH			= 800;															// ��ʂ̕�
const int								WINDOW_HEIGHT			= 600;															// ��ʂ̍���
const float								FRAME_PER_SECOND		= 60.0f;														// �P�b�U�O�t���[��

// �E�C���h�E�̏ꏊ
#define WINDOW_LEFT(objSizeX)			((objSizeX) / (2))																		// ��ʂ̍��[
#define WINDOW_TOP(objSizeY)			((objSizeY) / (2))																		// ��ʂ̏�[
#define WINDOW_RIGHT(objSizeX)			((WINDOW_WIDTH) - ((objSizeX) / (2)))													// ��ʂ̉E�[
#define WINDOW_BOTTOM(objSizeY)			((WINDOW_HEIGHT) - ((objSizeY) / (2)))													// ��ʂ̉��[
#define WINDOW_MIDDLE					(DirectX::SimpleMath::Vector2(((WINDOW_WIDTH) / (2)), ((WINDOW_HEIGHT) / (2))))			// ��ʂ̒��S
#define WINDOW_MIDDLE_X					((WINDOW_WIDTH) / (2))																	// ��ʂ�x���W�̒��S
#define WINDOW_MIDDLE_Y					((WINDOW_HEIGHT) / (2))																	// ��ʂ�y���W�̒��S

// �A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_LT				= DirectX::SimpleMath::Vector2(0.0f, 0.0f);						// ����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_LM				= DirectX::SimpleMath::Vector2(0.0f, 0.5f);						// �����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_LB				= DirectX::SimpleMath::Vector2(0.0f, 1.0f);						// �����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_MT				= DirectX::SimpleMath::Vector2(0.5f, 0.0f);						// ����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_MM				= DirectX::SimpleMath::Vector2(0.5f, 0.5f);						// �����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_MB				= DirectX::SimpleMath::Vector2(0.5f, 1.0f);						// �����̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_RT				= DirectX::SimpleMath::Vector2(1.0f, 0.0f);						// �E��̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_RM				= DirectX::SimpleMath::Vector2(1.0f, 0.5f);						// �E���̃A���J�[�|�C���g
const DirectX::SimpleMath::Vector2		ANCHOR_RB				= DirectX::SimpleMath::Vector2(1.0f, 1.0f);						// �E���̃A���J�[�|�C���g

// �n���h��
const std::wstring						FILE_PATH_SPRITE		= L"Resources/SpriteTextures/";									// �X�v���C�g�摜�̃t�@�C���n���h��
const std::wstring						FILE_PATH_MODEL			= L"Resources/Models/";											// ���f���̃t�@�C���n���h��
const std::wstring						FILE_PATH_FONT			= L"Resources/Fonts/";											// �t�H���g�̃t�@�C���n���h��

// �g���q
const std::wstring						EXT_PNG					= L".png";														// .png�t�@�C��
const std::wstring						EXT_CMO					= L".cmo";														// .cmo�t�@�C��
const std::wstring						EXT_CSO					= L".cso";														// .cso�t�@�C��
const std::wstring						EXT_SPRITEFONT			= L".spritefont";												// .spritefont�t�@�C��