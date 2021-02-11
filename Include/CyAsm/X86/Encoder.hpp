#pragma once

#include "Operand.hpp"

#include <span>

namespace CyberAsm
{
	class MachineStream;

	namespace X86
	{
		[[nodiscard]]
		extern auto Encode(MachineStream& out, Instruction instruction, std::span<const Operand> operands) -> std::size_t;

		[[nodiscard]]
		extern auto DetermineInstructionVariation(Instruction instruction, std::span<const Operand> operands) -> std::tuple<std::size_t, FixedSize>;
	}
}
