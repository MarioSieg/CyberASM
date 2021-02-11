#include <iostream>

#include "../Include/CyAsm/MachineStream.hpp"
#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Operand.hpp"

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Cyber Assembly\n----------------\n";

	using namespace X86;

	try
	{
		auto assemble = [](auto reg, auto val, auto str)
		{
			MachineStream out = {};
			const Operand operands[] = { Operand(reg), Operand(val) };
			const auto bytes = Encode(out, Instruction::Adc, operands);
			std::cout << std::left << str << " -> "<< std::right << out;
		};
		assemble(Register::Al, Imm8(23), "adcb $23, %al");
		assemble(Register::Ax, Imm16(0x1234), "adcw $0x1234, %ax");
		assemble(Register::Eax, Imm32(0xFF'AA'FF'00), "adcl $0xFF'AA'FF'00, %eax");
		assemble(Register::Esi, Imm32(0xFF'AA'FF'00), "adcl $0xFF'AA'FF'00, %esi");
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}

	return 0;
}
