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

	const Operand operands[] = {Operand(Register::Rax), Register::Rdi};
	const auto result = Encode(out, Instruction::Adc, operands);

	if (result != EncoderResult::Ok) [[unlikely]]
	{
		if (result == EncoderResult::InvalidMachineCodeIndex)
		{
			std::cerr << "invalid machine code index!";
		}
		else if (result == EncoderResult::NoInstructionVariationFound)
		{
			std::cerr << "no instruction variation found!";
		}
		return -1;
	}

	std::cout << out;

	return 0;
}
