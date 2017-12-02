/* =====================================================================
//! @param		「Action」ヘッダ（移動関係ライブラリ）
//! @create		樋口 裕太
//! @date		17/12/02
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../2D/Sprite.h"
#include "../3D/Object.h"

namespace GucchiLibrary
{
	/*
	// @class		Action クラス
	// @content		移動関係の共通クラス
	*/
	class Action
	{
	protected:
		DirectX::SimpleMath::Vector2 startPosV2;			// 始点（スプライト用）
		DirectX::SimpleMath::Vector3 startPosV3;			// 始点（オブジェクト用）

	public:
		Action() {}
		virtual ~Action() {}
	};

	/*
	// @class		MoveTo クラス
	// @content		線形移動（絶対移動）
	*/
	class MoveTo : public Action
	{
	public:
		/*
		// @method		Action
		// @content		移動アクション
		// @param		スプライト（Sprite*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector2）
		*/
		static void Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& pos);

		/*
		// @method		Action
		// @content		移動アクション
		// @param		オブジェクト（Object*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector3）
		*/
		static void Action(Object* object, float time, const DirectX::SimpleMath::Vector3& pos);
	};

	/*
	// @class		MoveBy クラス
	// @content		線形移動（相対移動）
	*/
	class MoveBy : public Action
	{
	public:
		/*
		// @method		Action
		// @content		移動アクション
		// @param		スプライト（Sprite*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector2）
		*/
		static void Action(Sprite* sprite, float time, const DirectX::SimpleMath::Vector2& distance);
		
		/*
		// @method		Action
		// @content		移動アクション
		// @param		オブジェクト（Object*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector3）
		*/
		static void Action(Object* object, float time, const DirectX::SimpleMath::Vector3& distance);
	};
}