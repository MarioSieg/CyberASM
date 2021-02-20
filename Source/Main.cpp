#include <iostream>

#include "../Include/CyAsm/X86/Cas2.hpp"

using namespace CyberAsm;

auto main(const int argc, const char* const* const argv) -> int
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	std::cout << "Cyber Assembly\n----------------\n";

	using namespace X86;

	try
	{
		const ByteChunk chunk = Cas2Encode<>(Instruction::Adc, Register::Spl, Immediate(5));
		std::cout << chunk;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}

	return 0;
}
