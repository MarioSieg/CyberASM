#pragma once

#include "Instructions.hpp"
#include "../MachineStream.hpp"
#include "../Operand.hpp"

#include <optional>

namespace CyberAsm::X86
{
	extern auto Encode(const X86::Instruction instruction, const std::initializer_list<Operand>& operands, MachineStream& out) -> bool;
	extern auto WriteOperand(const Operand& operand, MachineStream& out) -> std::size_t;
}
