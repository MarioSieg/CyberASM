#include <iostream>

#include "../Include/CyAsm/MachineStream.hpp"

#include <cassert>

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Cyber Assembly\n----------------\n";
	MachineStream out = {};
	out.Asm(X86::Instruction::Add, {X86::Register::Al, 3_imm8});
	std::cout << out;

	return 0;
}
