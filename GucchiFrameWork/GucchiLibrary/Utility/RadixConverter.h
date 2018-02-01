/* =====================================================================
//! @param		�uRadixConverter�v�w�b�_�i��ϊ����C�u�����j
//! @create		��� �T��
//! @date		18/02/01
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		RadixConverter �N���X
	// @content		��ϊ�
	*/
	class RadixConverter
	{
	public:
		static const int RADIX_2 = 2;		// �Q�i���w��
		static const int RADIX_8 = 8;		// �W�i���w��
		static const int RADIX_16 = 16;		// �P�U�i���w��
		static const int RADIX_0 = 0;		// ���̂܂܎w��

	public:
		/*
		// @method		RadixBinary�istatic�j
		// @content		�P�O�i������Q�i���֊�ϊ��i���w��Astring�j
		// @param		�l�iDWORD�j
		// @param		���iint�j
		// @return		�Q�i���istring�j
		*/
		static std::string RadixBinary(DWORD data, int digit)
		{
			std::string ret;

			// �������J��Ԃ�
			for (int i = 0; i < digit; i++)
			{
				// �P�r�b�g�����o���ĉE�V�t�g
				int bit = data >> i & 1;

				// �l��������
				ret += std::to_string(bit);
			}

			return ret;
		}

		/*
		// @method		Radix10To2�istatic�j
		// @content		�P�O�i������Q�i���֊�ϊ�
		// @param		�l�iint�j
		// @return		�Q�i���ilong�j
		*/
		static long Radix10To2(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_2);
		}

		/*
		// @method		Radix10To8�istatic�j
		// @content		�P�O�i������W�i���֊�ϊ�
		// @param		�l�iint�j
		// @return		�W�i���ilong�j
		*/
		static long Radix10To8(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_8);
		}

		/*
		// @method		Radix10To16�istatic�j
		// @content		�P�O�i������P�U�i���֊�ϊ�
		// @param		�l�iint�j
		// @return		�P�U�i���ilong�j
		*/
		static long Radix10To16(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_16);
		}

		/*
		// @method		RadixTo2�istatic�j
		// @content		���i������Q�i���֊�ϊ�
		// @param		�l�istring�j
		// @return		�Q�i���ilong�j
		*/
		static long RadixTo2(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_2);
		}

		/*
		// @method		RadixTo8�istatic�j
		// @content		���i������W�i���֊�ϊ�
		// @param		�l�istring�j
		// @return		�W�i���ilong�j
		*/
		static long RadixTo8(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_8);
		}

		/*
		// @method		RadixTo10�istatic�j
		// @content		���i������P�O�i���֊�ϊ�
		// @param		�l�istring�j
		// @return		�P�O�i���ilong�j
		*/
		static long RadixTo10(std::string data)
		{
			return std::strtod(data.c_str(), nullptr);
		}

		/*
		// @method		RadixTo16�istatic�j
		// @content		���i������P�U�i���֊�ϊ�
		// @param		�l�istring�j
		// @return		�P�U�i���ilong�j
		*/
		static long RadixTo16(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_16);
		}
	};
}