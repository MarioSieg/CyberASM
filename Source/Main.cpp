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

	const Operand operands[] = {Operand(Register::Eax), Operand(Imm8(5))};

	try
	{
		const EncodedInstruction instr = Encode(Instruction::Adc, operands);
		for(const auto byte : instr.Packed)
		{
			std::cout << std::hex << std::uppercase << static_cast<std::uint16_t>(byte) << ' ';
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}


	std::cout << out;

	return 0;
}
