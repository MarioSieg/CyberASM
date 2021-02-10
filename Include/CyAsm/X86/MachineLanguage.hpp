#pragma once

#include <cstdint>

// @formatter:off

namespace CyberAsm::X86
{
	constexpr std::uint8_t RexW64								= 0b01001000;
	constexpr std::uint8_t OperandOverride32					= 0b01100110;
	constexpr std::uint8_t AddressOverride						= 0b01100111;
	constexpr std::uint8_t Lock									= 0b00001111;
	constexpr std::uint8_t TwoByteOpCodePrefix					= 0b11110000;

	constexpr std::uint8_t ModBitsRegisterIndirect				= 0b00000000;
	constexpr std::uint8_t ModBitsOneByteSignedDisplace			= 0b00000001;
	constexpr std::uint8_t ModBitsFourByteSignedDisplace		= 0b00000010;
	constexpr std::uint8_t ModBitsRegisterAddressing			= 0b00000011;
}

// @formatter:on
