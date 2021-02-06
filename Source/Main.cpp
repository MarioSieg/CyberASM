#include <iostream>

#include "../Include/CyAsm/MachineStream.hpp"
#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Operand.hpp"

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Cyber Assembly\n----------------\n";
	MachineStream out = {};

	using namespace X86;

	const Operand operands[] = {Operand(Register::Al), Operand(Imm8(3))};
	Encode(out, Instruction::Adc, operands);

	std::cout << out;

	return 0;
}
