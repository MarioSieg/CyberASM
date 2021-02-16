#include <iostream>

#include "../Include/CyAsm/X86/Cas2.hpp"

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Cyber Assembly\n----------------\n";

	using namespace X86;

	try
	{
		ByteChunk chunk = std::get<ByteChunk>(Cas2Encode(Instruction::Adc, Register::Al, Immediate(10)));
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}

	return 0;
}
