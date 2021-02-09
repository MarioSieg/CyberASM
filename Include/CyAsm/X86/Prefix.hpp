#pragma once

#include <cstdint>

namespace CyberAsm::X86
{
	constexpr std::uint8_t RexW64 = 0x48;
	constexpr std::uint8_t OperandOverride32 = 0x66;
	constexpr std::uint8_t AddressOverride = 0x67;
	constexpr std::uint8_t Lock = 0x0F;
	constexpr std::uint8_t TwoByteOpCodePrefix = 0xF0;
}