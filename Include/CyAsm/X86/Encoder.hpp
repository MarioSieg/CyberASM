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

		extern void WriteOperands(MachineStream& out, std::span<const Operand> operands);

		[[nodiscard]]
		extern auto DetermineInstructionVariation(Instruction instruction, std::span<const Operand> operands) -> std::tuple<std::size_t, Size>;
	}
}
