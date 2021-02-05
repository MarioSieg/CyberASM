#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Registers.hpp"
#include "../Include/CyAsm/Utils.hpp"

#include <iostream>
#include <ranges>

namespace CyberAsm::X86
{
	auto Encode(const X86::Instruction instruction, const std::initializer_list<Operand>& operands, MachineStream& out) -> bool
	{
		const auto instructionIndex = static_cast<std::size_t>(instruction);
		const auto& machineVariations = InstructionTable[instructionIndex];

		// TODO: Write instruction:

		for(const auto& operand : operands)
		{
			WriteOperand(operand, out);
		}

		return true;
	}

	auto WriteOperand(const Operand& operand, MachineStream& out) -> std::size_t
	{
		const auto size = out.Size();
		std::visit(Overload {
			[&out](const Imm8 imm)
			{
				out << imm.U;
			},
			[&out](const Imm16 imm)
			{
				out << imm.U;
			},
			[&out](const Register reg)
			{
				out << RegisterIdTable[static_cast<std::size_t>(reg)];
			},
		}, operand.Data());
		return out.Size() - size;
	}

	auto FindInstruction(const X86::Instruction instruction, const std::initializer_list<Operand>& operands) -> std::optional<std::tuple<std::size_t, std::size_t>>
	{
		
	}
}
