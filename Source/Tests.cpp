#include <iostream>

#include "../Include/CyAsm/MachineStream.hpp"
#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Operand.hpp"

using namespace CyberAsm;
using namespace X86;

auto main(const int argc, const char* const* const argv) -> int
{
	std::cout << "Running CyberAsm tests...\n";
	std::cout << "Running tests for x86...\n";

	struct TestSubject
	{
		Instruction Instruction;
		std::array<Operand, 2> Operands;
	};

	constexpr auto TestSubjectCount = 2;

	static constexpr std::array<std::u8string_view, TestSubjectCount> CorrectMachineCode
	{
		u8"\x14\x05"_mach,
		u8"\x10\xD8"_mach,
	};

	static constexpr std::array<TestSubject, TestSubjectCount> TestData
	{
		TestSubject{Instruction::Adc, {Operand(Register::Al), Operand(Imm8(5))}},
		TestSubject{Instruction::Adc, {Operand(Register::Al), Operand(Register::Bl)}}
	};

	assert(CorrectMachineCode.size() == TestData.size());

	for (std::size_t i = 0; i < TestData.size(); ++i)
	{
		std::cout << "Test " << i + 1 << "...";
		const auto& machineCode = CorrectMachineCode[i];
		const auto& testData = TestData[i];
		MachineStream<TargetArchitecture::X86_64> stream = {};
		const auto result = Encode<TargetArchitecture::X86_64>(stream.Stream(), testData.Instruction, testData.Operands);
		const auto failed = result != Result::Ok || machineCode != stream;
		if (failed) [[unlikely]]
		{
			std::cout << "\n!!Failed!!\n";
			std::cout << "Result: " << result << '\n';
			std::cout << "Required length: " << machineCode.size() << ", Current length: " << stream.Size() << '\n';
			std::cout << "Should be: \n";
			for (const char8_t value : machineCode)
			{
				std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<std::uint16_t>(value) << ' ';
			}
			std::cout << "\nCurrently is: \n";
			for (const char8_t value : stream)
			{
				std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<std::uint16_t>(value) << ' ';
			}
			std::cout << "\n:(" << std::endl;
		}
		assert(result == Result::Ok);
		assert(machineCode == stream);
		if (!failed) [[likely]]
		{
			std::cout << " OK!\n";
		}
	}

	return 0;
}
