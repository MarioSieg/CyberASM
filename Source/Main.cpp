#include <iostream>
#include "../Include/CyAsm/MachineStream.hpp"
#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Operand.hpp"

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	std::ios::sync_with_stdio(false);
	std::cout << "Cyber Assembly\n----------------\n";

	using namespace X86;

	try
	{
		auto machineStream = MachineStream<TargetArchitecture::X86_64>(100);
		const Operand operands[] = {Operand(Register::Ax), Operand(Imm8(10))};
		const auto res = Encode<TargetArchitecture::X86_64>(machineStream.Stream(), Instruction::Adc, operands);
		std::cout << res << '\n';
		std::cout << machineStream;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}

	return 0;
}
