#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86
{
	template <Abi Arch = Abi::X86_64>
	[[nodiscard]] constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& operand) -> ByteChunk
	{
		const auto variation = AutoLookupInstruction(instruction, reg, operand).value();

		ByteChunk result = {};

		// REX
		if (RequiresRexPrefix<Arch>(instruction, variation)) [[likely]]
		{
			result << RexW64;
		}

		// Opcode
		if (RequiresTwoByteOpCode(instruction, variation)) [[likely]]
		{
			result << TwoByteOpCodePrefix;
		}

		// Opcode
		result << FetchMachineByte(instruction, variation);

		// ModR/M:
		if (!IsAccumulator(reg)) [[likely]]
		{
			const auto modField = ModBitsRegisterAddressing;
			const auto regField = LookupOpCodeExtension(instruction, variation).value_or(0);
			const auto rmField = LookupRegisterId(reg);
			result << PackByteBits233(modField, regField, rmField);
		}

		// SIB:
		// None

		// Displacement:
		// None

		// Immediate:
		result << operand;

		return result;
	}
}
