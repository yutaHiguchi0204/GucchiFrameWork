/* =====================================================================
//! @param		�uMath�v�w�b�_�i���w���C�u�����j
//! @create		��� �T��
//! @date		17/11/16
===================================================================== */
#pragma once

namespace GucchiLibrary
{
	/*
	// @class		Math �N���X
	// @content		���w�֌W
	// @use			��ɁASimpleMath�łł��Ȃ��v�Z�Ȃǂ��܂Ƃ߂�����
	*/
	class Math
	{
	public:
		/*
		// @method		SwapInt�istatic�j
		// @content		�l�����ւ���
		// @param		�l�P�ځiint�j
		// @param		�l�Q�ځiint�j
		*/
		static void SwapInt(int* _1, int* _2)
		{
			// �r�b�g���Z�iXOR�j��p���ăX���b�v
			*_1 ^= *_2;
			*_2 ^= *_1;
			*_1 ^= *_2;
		}

		/*
		// @method		SwapData�itemplate�Astatic�j
		// @content		�l�����ւ���
		// @param		�l�P�ځiT�j
		// @param		�l�Q�ځiT�j
		*/
		template<class T>
		static void SwapData(T* _1, T* _2)
		{
			// tmp��p���ăX���b�v
			T tmp = *_1;
			*_1 = *_2;
			*_2 = tmp;
		}

		/*
		// @method		Clamp�itemplate�Astatic�j
		// @content		�w�肵���͈͂ɒl�����߂�
		// @param		�l�iT�j
		// @param		�ŏ��l�iT�j
		// @param		�ő�l�iT�j
		*/
		template<class T> static T Clamp(T data, T minimum, T maximum)
		{
			// �ő�l�̃��b�v����
			T tmp = data > maximum ? maximum : data;

			// �ŏ��l�̃��b�v����
			return tmp < minimum ? minimum : tmp;
		}

		/*
		// @method		Factorial�istatic�j
		// @content		�K��
		// @param		���R���iint�j
		// @return		�v�Z���ʁiint�j
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
		// @method		RandomRange�itemplate�Astatic�j
		// @content		�w�肵���͈͓��Ń����_���̒l��Ԃ�
		// @param		�ŏ��l�iT�j
		// @param		�ő�l�iT�j
		// @return		�����l�iT�j
		*/
		template<class T> static T RandomRange(T min, T max)
		{
			T random = static_cast<T>(std::rand() / static_cast<T>(RAND_MAX));
			random = (max - min) * random + min;

			return random;
		}
	};
}