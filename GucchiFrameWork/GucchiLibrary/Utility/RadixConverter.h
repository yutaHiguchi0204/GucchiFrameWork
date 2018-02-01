/* =====================================================================
//! @param		「RadixConverter」ヘッダ（基数変換ライブラリ）
//! @create		樋口 裕太
//! @date		18/02/01
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <string>

namespace GucchiLibrary
{
	/*
	// @class		RadixConverter クラス
	// @content		基数変換
	*/
	class RadixConverter
	{
	public:
		static const int RADIX_2 = 2;		// ２進数指定
		static const int RADIX_8 = 8;		// ８進数指定
		static const int RADIX_16 = 16;		// １６進数指定
		static const int RADIX_0 = 0;		// そのまま指定

	public:
		/*
		// @method		RadixBinary（static）
		// @content		１０進数から２進数へ基数変換（桁指定、string）
		// @param		値（DWORD）
		// @param		桁（int）
		// @return		２進数（string）
		*/
		static std::string RadixBinary(DWORD data, int digit)
		{
			std::string ret;

			// 桁数分繰り返す
			for (int i = 0; i < digit; i++)
			{
				// １ビット分取り出して右シフト
				int bit = data >> i & 1;

				// 値を加える
				ret += std::to_string(bit);
			}

			return ret;
		}

		/*
		// @method		Radix10To2（static）
		// @content		１０進数から２進数へ基数変換
		// @param		値（int）
		// @return		２進数（long）
		*/
		static long Radix10To2(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_2);
		}

		/*
		// @method		Radix10To8（static）
		// @content		１０進数から８進数へ基数変換
		// @param		値（int）
		// @return		８進数（long）
		*/
		static long Radix10To8(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_8);
		}

		/*
		// @method		Radix10To16（static）
		// @content		１０進数から１６進数へ基数変換
		// @param		値（int）
		// @return		１６進数（long）
		*/
		static long Radix10To16(int data)
		{
			return std::strtol(std::to_string(data).c_str(), nullptr, RADIX_16);
		}

		/*
		// @method		RadixTo2（static）
		// @content		ｎ進数から２進数へ基数変換
		// @param		値（string）
		// @return		２進数（long）
		*/
		static long RadixTo2(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_2);
		}

		/*
		// @method		RadixTo8（static）
		// @content		ｎ進数から８進数へ基数変換
		// @param		値（string）
		// @return		８進数（long）
		*/
		static long RadixTo8(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_8);
		}

		/*
		// @method		RadixTo10（static）
		// @content		ｎ進数から１０進数へ基数変換
		// @param		値（string）
		// @return		１０進数（long）
		*/
		static long RadixTo10(std::string data)
		{
			return std::strtod(data.c_str(), nullptr);
		}

		/*
		// @method		RadixTo16（static）
		// @content		ｎ進数から１６進数へ基数変換
		// @param		値（string）
		// @return		１６進数（long）
		*/
		static long RadixTo16(std::string data)
		{
			long radix10 = std::strtod(data.c_str(), nullptr);

			return std::strtol(std::to_string(radix10).c_str(), nullptr, RADIX_16);
		}
	};
}