#include <iostream>
#include <cassert>

#include "../Include/CyAsm/X86/Instructions.hpp"

using namespace CyberAsm;
using namespace X86;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Running CyberAsm tests...\n";

	const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg64, OperandFlags::Imm32>(Instruction::Adc);
	assert(instruction);
	assert(*instruction == 7);

	std::cout << "All tests ok!" << std::endl;

	return 0;
}
