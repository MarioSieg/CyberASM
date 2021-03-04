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
	constexpr std::uint8_t ModBitsRegisterIndirect				= 0b0000'0000;
	constexpr std::uint8_t ModBitsOneByteSignedDisplace			= 0b0000'0001;
	constexpr std::uint8_t ModBitsFourByteSignedDisplace		= 0b0000'0010;
	constexpr std::uint8_t ModBitsRegisterAddressing			= 0b0000'0011;
	constexpr std::uint8_t SibScaleFactor1						= 0b0000'0000;
	constexpr std::uint8_t SibScaleFactor2						= 0b0000'0001;
	constexpr std::uint8_t SibScaleFactor4						= 0b0000'0010;
	constexpr std::uint8_t SibScaleFactor8						= 0b0000'0011;

	// @formatter:on

	/// <summary>
	/// +---+---+---+---+---+---+---+---+
	/// | 0 | 1 | 0 | 0 | W | R | X | B |
	/// +---+---+---+---+---+---+---+---+
	/// +-------+--------+-------------+
	/// | Field | Length | Description |
	/// +-------+--------+-------------+
	/// |  0100	| 4 bits | Fixed magic bit pattern
	///	|   W	| 1 bit	 | When 1, a 64 - bit operand size is used.Otherwise, when 0, the default operand size is used (which is 32 - bit for most but not all instructions).
	/// |   R	| 1 bit	 | This 1 - bit value is an extension to the MODRM.reg field. See Registers.
	/// |   X	| 1 bit	 | This 1 - bit value is an extension to the SIB.index field. See 64 - bit addressing.
	/// |   B	| 1 bit	 | This 1 - bit value is an extension to the MODRM.rm field or the SIB.base field.See 64 - bit addressing.
	/// +-------+--------+-------------+
	/// </summary>
	/// <param name="w"></param>
	/// <param name="r"></param>
	/// <param name="x"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	constexpr auto PackByteRexPrefix(const bool w, const bool r = false, const bool x = false, const bool b = false) noexcept -> std::uint8_t
	{
		std::uint8_t rex = 0b0100'0000U;
		rex ^= (-static_cast<std::uint8_t>(b) ^ rex) & 1U << 0U;
		rex ^= (-static_cast<std::uint8_t>(x) ^ rex) & 1U << 1U;
		rex ^= (-static_cast<std::uint8_t>(r) ^ rex) & 1U << 2U;
		rex ^= (-static_cast<std::uint8_t>(w) ^ rex) & 1U << 3U;
		return rex;
	}

	// +---+---+---+---+---+---+---+---+
	// | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
	// +---+---+---+---+---+---+---+---+
	constexpr auto PackByteBitsModRmSib(std::uint8_t bs01, std::uint8_t b234, std::uint8_t b567) noexcept -> std::uint8_t
	{
		b567 &= ~0b1111'1000U;
		b234 &= ~0b1111'1000U;
		bs01 &= ~0b1111'1100U;
		b234 <<= 3U;
		bs01 <<= 6U;
		b567 |= b234;
		b567 |= bs01;
		return b567;
	}
}
