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
		// @method		DebugLog�istatic�j
		// @content		���O�\��
		// @param		���b�Z�[�W�iwchar_t*�j
		*/
		static void DebugLog(wchar_t* message)
		{
#if defined(MODE_DEBUG)
			// ���O���b�Z�[�W
			std::wstringstream log;

			log << L"\n";
			log << L"**************************************************\n";
			log << L"Error: " << message << L"\n";
			log << L"**************************************************\n";
			log << L"\n";

			OutputDebugStringW(log.str().c_str());
#endif
		}

		/*
		// @method		DebugLog�istatic�j
		// @content		���O�\��
		// @param		���b�Z�[�W�iwstring�j
		*/
		static void DebugLog(std::wstring message)
		{
			DebugLog(message.c_str());
		}
	};
}