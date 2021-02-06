#pragma once

#include <cstdint>
#include <span>

namespace CyberAsm
{
	class MachineStream;
	
	namespace X86
	{
		class Operand;
		enum class Instruction : std::uint8_t;

		extern void Encode(MachineStream& out, Instruction instruction, std::span<const Operand> operands);
		extern auto WriteOperands(MachineStream& out, std::span<const Operand> operands) -> std::size_t;
	}
}