#pragma once

#include <cstdint>

namespace CyberAsm
{
	enum class FixedSize : std::uint8_t
	{
		/// <summary>
		/// 1 byte, 8 bit
		/// </summary>
		Byte = 1,

		/// <summary>
		/// 2 byte, 16 bit
		/// </summary>
		Word = 2,

		/// <summary>
		/// double word
		/// 4 byte, 32 bit
		/// </summary>
		DWord = 4,

		/// <summary>
		/// quad word
		/// 8 byte, 64 bit
		/// </summary>
		QWord = 8,

		/// <summary>
		/// octa word
		/// 16 byte, 128 bit
		/// double 
		/// </summary>
		OWord = 16,

		/// <summary>
		/// double octa word
		/// 32 byte, 256 bit
		/// </summary>
		DOWord = 32,

		/// <summary>
		/// quad octa word
		/// 64 byte, 512 bit
		/// </summary>
		QOWord = 64,
	};

	template <typename... T>
	struct Overload : T...
	{
		using T::operator()...;
	};

	template <typename... T>
	Overload(T ...) -> Overload<T...>;
}
