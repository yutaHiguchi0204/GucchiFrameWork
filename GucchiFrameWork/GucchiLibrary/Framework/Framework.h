/* =====================================================================
//! @param		「Framework」ヘッダ
//! @create		樋口 裕太
//! @date		17/10/09
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
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