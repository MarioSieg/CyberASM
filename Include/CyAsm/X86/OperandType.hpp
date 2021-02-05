#pragma once

#include <cstdint>
#include <cstdint>
#include <cstddef>

namespace CyberAsm::X86
{
	struct InstructionOperandType final
	{
		enum Enum : std::uint16_t
		{
			None = 0,
			Imm8 = 1 << 0,
			Mem8 = 1 << 1,
			Reg8 = 1 << 2,
			Reg8Hi = 1 << 3,
			Reg8Al = 1 << 4,
			Reg8Ah = 1 << 5,
			Reg8Cl = 1 << 6,

			Imm16 = 1 << 7,
			Mem16 = 1 << 8,
			Reg16 = 1 << 9,
			Reg16Ax = 1 << 10,
			Reg16Dx = 1 << 11,

			Imm32 = 1 << 12,
			Mem32 = 1 << 13,
			Reg32 = 1 << 14,
			Reg32Eax = 1 << 15,

			Count
		};
	};

	constexpr std::size_t MaxOperands = 4;
}
