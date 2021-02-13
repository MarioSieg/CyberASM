#pragma once

#include <array>
#include <algorithm>

namespace CyberAsm
{
	enum class TargetArchitecture
	{
		X86_16,
		X86_32,
		X86_64,
		ARM_64
	};

	/// <summary>
	/// Represents an endianness.
	/// Big-Endian = most significant byte is stored at the smallest memory address
	/// Little-Endian = most significant byte is stored at the largest memory address
	/// </summary>
	enum class Endianness
	{
		Little,
		Big
	};

	/// <summary>
	/// Converts a trivial object into a byte array.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="out"></param>
	/// <param name="in"></param>
	/// <returns></returns>
	template <typename T, Endianness E = Endianness::Little> requires std::is_trivial_v<T>
	constexpr void BytePack(std::array<std::uint8_t, sizeof(T)>& out, const T& in)
	{
		union
		{
			T Instance;
			std::array<std::uint8_t, sizeof(T)> Bytes;
		} castor = {in};

		if constexpr (sizeof(T) == 1)
		{
			out[0] = castor.Bytes[0];
			return;
		}
		else if constexpr (E == Endianness::Little)
		{
			std::copy(castor.Bytes.begin(), castor.Bytes.end(), out.begin());
		}
		else
		{
			std::reverse_copy(castor.Bytes.begin(), castor.Bytes.end(), out.begin());
		}
	}
}
