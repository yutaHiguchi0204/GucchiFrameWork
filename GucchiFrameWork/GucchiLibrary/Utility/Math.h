/* =====================================================================
//! @param		「Math」ヘッダ（数学ライブラリ）
//! @create		樋口 裕太
//! @date		17/11/16
===================================================================== */
#pragma once

namespace GucchiLibrary
{
	/*
	// @class		Math クラス
	// @content		数学ライブラリ
	// @use			主に、SimpleMathでできない計算などをまとめたもの
	*/
	class Math
	{
	public:
		/*
		// @method		RandomRange（template）
		// @content		指定した範囲内でランダムの値を返す
		// @param		最小値（T）
		// @param		最大値（T）
		*/
		template<class T> static T RandomRange(T min, T max)
		{
			T random = static_cast<T>(std::rand() / static_cast<T>(RAND_MAX));
			random = (max - min) * random + min;

			return random;
		}
	};
}