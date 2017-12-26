/* =====================================================================
//! @param		���������[�N���o�p
//! @create		��� �T��
//! @date		17/12/26
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/DebugSwitch.h"

// �f�o�b�O���[�h�łȂ���Ό��o���Ȃ�
#if defined(MODE_DEBUG)

	// �w�b�_�t�@�C���̃C���N���[�h
	#include <crtdbg.h>

	// �}�N����`
	#define _CRTDBG_MAP_ALLOC
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

	namespace GucchiLibrary
	{
		/*
		// @method		SetUpMemoryLeakDetector�iglobal�j
		// @content		���������[�N���o��̃Z�b�g�A�b�v
		*/
		inline void SetUpMemoryLeakDetector()
		{
			_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
		}
	}

#endif