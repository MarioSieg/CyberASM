#pragma once

#include <span>

#include "Operand.hpp"

namespace CyberAsm
{
	class MachineStream;

	namespace X86
	{
		[[nodiscard]]
		extern auto Encode(MachineStream& out, Instruction instruction, std::span<const Operand> operands) -> std::size_t;
	}
}
