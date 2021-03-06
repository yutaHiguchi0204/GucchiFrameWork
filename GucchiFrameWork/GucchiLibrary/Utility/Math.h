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
	// @content		数学関係
	// @use			主に、SimpleMathでできない計算などをまとめたもの
	*/
	class Math
	{
	public:
		/*
		// @method		SwapInt（static）
		// @content		値を入れ替える
		// @param		値１つ目（int）
		// @param		値２つ目（int）
		*/
		static void SwapInt(int* _1, int* _2)
		{
			// ビット演算（XOR）を用いてスワップ
			*_1 ^= *_2;
			*_2 ^= *_1;
			*_1 ^= *_2;
		}

		/*
		// @method		SwapData（template、static）
		// @content		値を入れ替える
		// @param		値１つ目（T）
		// @param		値２つ目（T）
		*/
		template<class T>
		static void SwapData(T* _1, T* _2)
		{
			// tmpを用いてスワップ
			T tmp = *_1;
			*_1 = *_2;
			*_2 = tmp;
		}

		/*
		// @method		Clamp（template、static）
		// @content		指定した範囲に値を収める
		// @param		値（T）
		// @param		最小値（T）
		// @param		最大値（T）
		*/
		template<class T> static T Clamp(T data, T minimum, T maximum)
		{
			// 最大値のラップ処理
			T tmp = data > maximum ? maximum : data;

			// 最小値のラップ処理
			return tmp < minimum ? minimum : tmp;
		}

		/*
		// @method		Factorial（static）
		// @content		階乗
		// @param		自然数（int）
		// @return		計算結果（int）
		*/
		static int Factorial(int num)
		{
			if (num <= 0)
			{
				return 0;
			}

			int n = num;
			int result = 1;
			while (n != 1)
			{
				result *= n;
				n--;
			}

			return n;
		}

		/*
		// @method		RandomRange（template、static）
		// @content		指定した範囲内でランダムの値を返す
		// @param		最小値（T）
		// @param		最大値（T）
		// @return		乱数値（T）
		*/
		template<class T> static T RandomRange(T min, T max)
		{
			T random = static_cast<T>(std::rand() / static_cast<T>(RAND_MAX));
			random = (max - min) * random + min;

			return random;
		}
	};
}