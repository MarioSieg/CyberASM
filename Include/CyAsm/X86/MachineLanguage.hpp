#pragma once

#include <cstdint>

// @formatter:off

namespace CyberAsm::X86
{
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
}

// @formatter:on
