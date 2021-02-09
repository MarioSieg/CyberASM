#pragma once

#include "Operand.hpp"

#include <span>

namespace CyberAsm
{
	class MachineStream;

	namespace X86
	{	

		[[nodiscard]]
		extern auto Encode(Instruction instruction, std::span<const Operand> operands) -> EncodedInstruction;

		extern void WriteOperands(std::span<const Operand> operands);

		[[nodiscard]]
		extern auto DetermineInstructionVariation(Instruction instruction, std::span<const Operand> operands) -> std::tuple<std::size_t, FixedSize>;
	}
}
