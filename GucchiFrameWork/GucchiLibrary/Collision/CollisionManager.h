/* =====================================================================
//! @param		「CollisionManager」ヘッダ
//! @create		樋口 裕太
//! @date		17/11/29
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "../Common/SingletonDirector.h"

namespace GucchiLibrary
{
	/*
	// @class		CollisionManager クラス
	// @content		当たり判定チェック用
	*/
	class CollisionManager : public SingletonDirector<CollisionManager>
	{
	public:
		/*
		// @content		当たり判定をチェックする方向
		// @mode		OWN		：　自身の場所
		// @mode		LEFT	：　左側
		// @mode		RIGHT	：　右側
		// @mode		TOP		：　上側
		// @mode		BOTTOM	：　下側
		*/
		enum class COLLISION
		{
			OWN,
			LEFT,
			RIGHT,
			TOP,
			BOTTOM
		};

	private:
		friend class SingletonDirector<CollisionManager>;

		CollisionManager() {}

	public:
		/*
		// @method		CheckCollisionMapTip
		// @content		指定した場所のマップチップをチェック
		*/
		//bool CheckCollisionMapTip()
	};
}