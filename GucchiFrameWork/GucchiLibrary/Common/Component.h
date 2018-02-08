/* =====================================================================
//! @param		「Component」ヘッダ
//! @create		樋口 裕太
//! @date		18/02/08
===================================================================== */
#pragma once

namespace GucchiLibrary
{
	class Element;

	/*
	// @class		Component クラス
	// @content		コンポーネントクラス
	*/
	class Component
	{
	public:
		// コンストラクタ
		Component() = default;
		
		// デストラクタ
		virtual ~Component() = default;

		/*
		// @method		Update
		// @content		更新処理
		*/
		virtual void Update(Element* element) = 0;
	};
}