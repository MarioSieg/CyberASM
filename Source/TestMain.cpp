#include <iostream>

namespace CyberAsm
{
	extern void RunAllTestsForX86();
}

auto main(const int argc, const char* const* const argv) -> int
{
	(void)argc;
	(void)argv;
	std::cout << "Running CyberAsm tests...\n";

	CyberAsm::RunAllTestsForX86();

	std::cout << "All tests ok!" << std::endl;

	return 0;
}
