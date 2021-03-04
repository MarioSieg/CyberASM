#pragma once

#include <array>
#include <algorithm>
#include <climits>

#include "Utils.hpp"

namespace CyberAsm
{
	enum class Abi
	{
		X86_16,
		X86_32,
		X86_64,
		ARM_64
	};

	constexpr auto operator""_mach(const char8_t* const str, const std::size_t count) noexcept -> std::u8string_view
	{
		return {str, count};
	}

	template <typename... T>
	[[nodiscard]] constexpr auto VaridadicArrayConstruct(T&&... values) noexcept -> decltype(auto)
	{
		return std::array<std::decay_t<std::common_type_t<T...>>, sizeof...(T)>{std::forward(values)...};
	}

	template <typename T, std::size_t... N>
	[[nodiscard]] constexpr auto EndianSwapImpl(T&& x, std::index_sequence<N...>) noexcept -> T
	{
		return (((x >> N * CHAR_BIT & 0xFFU) << (sizeof(T) - N - 1U) * CHAR_BIT) | ...);
	}

	template <typename T, typename U = std::make_unsigned_t<T>>
	[[nodiscard]] constexpr auto EndianSwap(T&& x) noexcept -> U
	{
		return EndianSwapImpl<U>(x, std::make_index_sequence<sizeof(T)>{});
	}

	/// <summary>
	/// Calculate the minimal storage size in bytes a value would need.
	/// Useful to calculate the required storage for immediate values:
	/// mov rax, 0xFF <- Result = 1
	/// mov rax, 0xFFFF <- Result = 2
	/// mov rax, 0xFFFF'FFFF <- Result = 4
	/// mov rax, 0xFFFFFFFF'FFFFFFFF <- Result = 8
	/// etc..
	/// </summary>
	/// <param name="value">The value to check. </param>
	/// <returns></returns>
	constexpr auto ComputeRequiredBytes(std::uint64_t value) noexcept -> WordSize
	{
		// Count required bytes:
		std::uint8_t bytes = 0;
		do
		{
			value >>= UINT64_C(8);
			++bytes;
		}
		while (value);

		// Round up to next power of 2:
		return RoundUpToNextPowerOf2(static_cast<WordSize>(bytes));
	}

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
		if constexpr (E == Endianness::Little)
		{
			std::copy(castor.Bytes.begin(), castor.Bytes.end(), out.begin());
		}
		else
		{
			std::reverse_copy(castor.Bytes.begin(), castor.Bytes.end(), out.begin());
		}
	}
}
