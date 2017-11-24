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
	// @content		���w���C�u����
	// @use			��ɁASimpleMath�łł��Ȃ��v�Z�Ȃǂ��܂Ƃ߂�����
	*/
	class Math
	{
	public:
		/*
		// @method		RandomRange�itemplate�j
		// @content		�w�肵���͈͓��Ń����_���̒l��Ԃ�
		// @param		�ŏ��l�iT�j
		// @param		�ő�l�iT�j
		*/
		template<class T> static T RandomRange(T min, T max)
		{
			T random = static_cast<T>(std::rand() / static_cast<T>(RAND_MAX));
			random = (max - min) * random + min;

			return random;
		}
	};
}