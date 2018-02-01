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
	class ActionManager
	{
	public:
		// コンストラクタ
		ActionManager() = default;

		// デストラクタ
		virtual ~ActionManager() = default;
	};

	/*
	// @class		MoveTo クラス
	// @content		線形移動（絶対移動）
	*/
	class MoveTo : public ActionManager
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		移動アクション
		// @param		スプライト（Sprite*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector2）
		// @return		補間値（Vector2）
		*/
		static Vector2 Action(Sprite* sprite, float time, const Vector2& pos);

		/*
		// @method		Action
		// @content		移動アクション
		// @param		オブジェクト（Object*）
		// @param		移動にかける時間（float）
		// @param		終点（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& trans);
	};

	/*
	// @class		MoveBy クラス
	// @content		線形移動（相対移動）
	*/
	class MoveBy : public ActionManager
	{
	private:
		using Vector2 = DirectX::SimpleMath::Vector2;
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		移動アクション
		// @param		スプライト（Sprite*）
		// @param		移動にかける時間（float）
		// @param		移動距離（Vector2）
		// @return		補間値（Vector2）
		*/
		static Vector2 Action(Sprite* sprite, float time, const Vector2& distance);
		
		/*
		// @method		Action
		// @content		移動アクション
		// @param		オブジェクト（Object*）
		// @param		移動にかける時間（float）
		// @param		移動距離（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& distance);
	};

	/*
	// @class		ScaleTo クラス
	// @content		スケール変化（絶対変化）
	*/
	class ScaleTo : public ActionManager
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		スケール変化アクション
		// @param		スプライト（Sprite*）
		// @param		変化にかける時間（float）
		// @param		スケール値（float）
		// @return		補間値（float）
		*/
		static float Action(Sprite* sprite, float time, float scale);

		/*
		// @method		Action
		// @content		スケール変化アクション
		// @param		オブジェクト（Object*）
		// @param		変化にかける時間（float）
		// @param		スケール値（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& scale);
	};

	/*
	// @class		ScaleBy クラス
	// @content		スケール変化（相対移動）
	*/
	class ScaleBy : public ActionManager
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		スケール変化アクション
		// @param		スプライト（Sprite*）
		// @param		変化にかける時間（float）
		// @param		現在のスケールからの倍率（float）
		// @return		補間値（float）
		*/
		static float Action(Sprite* sprite, float time, const float scale);

		/*
		// @method		Action
		// @content		スケール変化アクション
		// @param		オブジェクト（Object*）
		// @param		変化にかける時間（float）
		// @param		現在のスケールからの倍率（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& scale);
	};

	/*
	// @class		RotateTo クラス
	// @content		回転運動（絶対回転）
	*/
	class RotateTo : public ActionManager
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		回転アクション
		// @param		スプライト（Sprite*）
		// @param		回転にかける時間（float）
		// @param		回転角（float）
		// @return		補間値（float）
		*/
		static float Action(Sprite* sprite, float time, float angle);

		/*
		// @method		Action
		// @content		回転アクション
		// @param		オブジェクト（Object*）
		// @param		回転にかける時間（float）
		// @param		回転角（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& rot);
	};

	/*
	// @class		RotateBy クラス
	// @content		回転運動（相対回転）
	*/
	class RotateBy : public ActionManager
	{
	private:
		using Vector3 = DirectX::SimpleMath::Vector3;

	public:
		/*
		// @method		Action
		// @content		回転アクション
		// @param		スプライト（Sprite*）
		// @param		回転にかける時間（float）
		// @param		現在の角度からの回転角（float）
		// @return		補間値（float）
		*/
		static float Action(Sprite* sprite, float time, float angle);

		/*
		// @method		Action
		// @content		回転アクション
		// @param		オブジェクト（Object*）
		// @param		回転にかける時間（float）
		// @param		現在の角度からの回転角（Vector3）
		// @return		補間値（Vector3）
		*/
		static Vector3 Action(Object* object, float time, const Vector3& rot);
	};
}