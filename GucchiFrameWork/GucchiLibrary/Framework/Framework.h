/* =====================================================================
//! @param		�uFramework�v�w�b�_
//! @create		��� �T��
//! @date		17/10/09
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "../Common/DeviceResources.h"

namespace GucchiLibrary
{
	class Framework : public IDeviceNotify
	{
	public:
		Framework();
		virtual ~Framework();
	};
}