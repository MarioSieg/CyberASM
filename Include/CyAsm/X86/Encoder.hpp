#pragma once

#include "Instructions.hpp"
#include "../MachineStream.hpp"
#include "../Operand.hpp"

#include <optional>

namespace CyberAsm::X86
{
	extern auto Encode(X86::Instruction instruction, const std::initializer_list<Operand>& operands, MachineStream& out) -> bool;
	extern auto WriteOperand(const Operand& operand, MachineStream& out) -> std::size_t;
	extern auto FindInstruction(X86::Instruction instruction, const std::initializer_list<Operand>& operands)->std::optional<std::tuple<std::size_t, std::size_t>>;
}
