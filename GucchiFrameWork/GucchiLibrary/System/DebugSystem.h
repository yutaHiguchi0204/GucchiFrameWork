/* =====================================================================
//! @param		�uDebugSystem�v�w�b�_�iDebug�r���h���ɍs�������j
//! @create		��� �T��
//! @date		18/02/06
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <sstream>
#include <string>
#include "../Common/DebugSwitch.h"
#include "../Common/DeviceResources.h"

namespace GucchiLibrary
{
	/*
	// @class		DebugSystem �N���X
	// @content		�f�o�b�O�r���h�p�N���X
	*/
	class DebugSystem
	{
	public:
		/*
		// @method		IsDebugMode�istatic�j
		// @content		�f�o�b�O���[�h���ǂ���
		// @return		�f�o�b�O���[�h���ǂ����ibool�j
		*/
		static bool IsDebugMode()
		{
#if defined(MODE_DEBUG)
			return true;
#endif
			return false;
		}

		/*
		// @method		DebugLog�istatic�j
		// @content		���O�\��
		// @param		���b�Z�[�W�iwchar_t*�j
		// @param		�G���[���O���ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		*/
		static void DebugLog(wchar_t* message, bool error = false)
		{
#if defined(MODE_DEBUG)
			// ���O���b�Z�[�W
			std::wstringstream log;

			log << L"\n";
			log << L"**************************************************\n";
			if (error) log << L"Error!: ";
			log << message << L"\n";
			log << L"**************************************************\n";
			log << L"\n";

			OutputDebugStringW(log.str().c_str());
#endif
		}

		/*
		// @method		DebugLog�istatic�j
		// @content		���O�\��
		// @param		���b�Z�[�W�iwstring�j
		// @param		�G���[���O���ǂ����ibool�j	�F	�f�t�H���g�ifalse�j
		*/
		static void DebugLog(std::wstring message, bool error = false)
		{
			DebugLog(message.c_str(), error);
		}

		/*
		// @method		RasterizerToWireFrame�istatic�j
		// @content		���X�^���C�U�ɂ���ĕ`�悳���v���~�e�B�u�����C���[�t���[���ɂ���
		*/
		static void RasterizerToWireFrame()
		{
			DeviceResources& deviceResources = DeviceResources::GetInstance();
			ID3D11Device* device = deviceResources.GetD3DDevice();
			ID3D11DeviceContext* context = deviceResources.GetD3DDeviceContext();

			// ���X�^���C�U�ݒ�
			D3D11_RASTERIZER_DESC rdc;
			ZeroMemory(&rdc, sizeof(rdc));
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_WIREFRAME;

			// ���X�^���C�U�X�e�[�g�̍쐬
			ID3D11RasterizerState* rasterizer = nullptr;
			device->CreateRasterizerState(&rdc, &rasterizer);

			// ���X�^���C�U�X�e�[�g��ݒ�
			context->RSSetState(rasterizer);
		}
	};
}
