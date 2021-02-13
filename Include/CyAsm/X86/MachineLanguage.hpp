#pragma once

#include <cstdint>

#include "../MachineLanguage.hpp"

namespace CyberAsm::X86
{
	// @formatter:off
	
	constexpr std::uint8_t Lock									= 0xF0;
	constexpr std::uint8_t RepNeRepNz							= 0xF2;
	constexpr std::uint8_t RepRepeRepz							= 0xF3;
	constexpr std::uint8_t SegmentOverrideCs					= 0x2E;
	constexpr std::uint8_t SegmentOverrideSs					= 0x36;
	constexpr std::uint8_t SegmentOverrideDs					= 0x3E;
	constexpr std::uint8_t SegmentOverrideEs					= 0x26;
	constexpr std::uint8_t SegmentOverrideFs					= 0x64;
	constexpr std::uint8_t SegmentOverrideGs					= 0x65;
    constexpr std::uint8_t RexW64								= 0x48;
	constexpr std::uint8_t OperandSizeOverride					= 0x66;
	constexpr std::uint8_t AddressSizeOverride					= 0x67;
    constexpr std::uint8_t TwoByteOpCodePrefix					= 0x0F;
	constexpr std::uint8_t ModBitsRegisterIndirect				= 0b00000000;
	constexpr std::uint8_t ModBitsOneByteSignedDisplace			= 0b00000001;
	constexpr std::uint8_t ModBitsFourByteSignedDisplace		= 0b00000010;
	constexpr std::uint8_t ModBitsRegisterAddressing			= 0b00000011;
	constexpr std::uint8_t SibScaleFactor1						= 0b00000000;
	constexpr std::uint8_t SibScaleFactor2						= 0b00000001;
	constexpr std::uint8_t SibScaleFactor4						= 0b00000010;
	constexpr std::uint8_t SibScaleFactor8						= 0b00000011;

	// @formatter:on

	// +---+---+---+---+---+---+---+---+
	// | 0   1   0   0 | w | r | x | b |
	// +---+---+---+---+---+---+---+---+
	constexpr auto PackByteRexPrefix(const bool w, const bool r = false, const bool x = false, const bool b = false) noexcept -> std::uint8_t
	{
		std::uint8_t rex = 0b00000100;
		rex <<= 4U;
		rex ^= (-static_cast<std::uint8_t>(b) ^ rex) & 1U << 0U;
		rex ^= (-static_cast<std::uint8_t>(x) ^ rex) & 1U << 1U;
		rex ^= (-static_cast<std::uint8_t>(r) ^ rex) & 1U << 2U;
		rex ^= (-static_cast<std::uint8_t>(w) ^ rex) & 1U << 3U;
		return rex;
	}

	// +---+---+---+---+---+---+---+---+
	// | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
	// +---+---+---+---+---+---+---+---+
	constexpr auto PackByte233(std::uint8_t bs01, std::uint8_t b234, std::uint8_t b567) noexcept -> std::uint8_t
	{
		b567 &= ~0b1111000U;
		b234 &= ~0b1111000U;
		b234 <<= 3U;
		bs01 &= ~0b11111100U;
		bs01 <<= 6U;
		b567 |= b234;
		b567 |= bs01;
		return b567;
	}

	template <typename T, std::size_t... N>
	[[nodiscard]] constexpr auto EndianSwapImpl(T&& x, std::index_sequence<N...>) -> T
	{
		return (((x >> N * CHAR_BIT & 0xFF) << (sizeof(T) - N - 1) * CHAR_BIT) | ...);
	}

	template <typename T, typename U = std::make_unsigned_t<T>>
	[[nodiscard]] constexpr auto EndianSwap(T&& x) -> U
	{
		return EndianSwapImpl<U>(x, std::make_index_sequence<sizeof(T)>{});
	}
}
