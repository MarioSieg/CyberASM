#include <cassert>
#include <iostream>

#include "../Include/CyAsm/X86/Instructions.hpp"
#include "../Include/CyAsm/X86/Cas2.hpp"

static void RunAllTestsForX86()
{
	using namespace CyberAsm;
	using namespace X86;

	// Test instruction lookup:

	{
		const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg64, OperandFlags::Imm32>(Instruction::Adc);
		assert(instruction);
		assert(*instruction == 7);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg64Rax, OperandFlags::Imm32>(Instruction::Adc);
		assert(instruction);
		assert(*instruction == 5);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg8, OperandFlags::Reg8>(Instruction::Adc);
		assert(instruction);
		assert(*instruction == 0);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg16Ax, OperandFlags::Imm8>(Instruction::Adc);
		assert(instruction);
		assert(*instruction == 8);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Rbx, Immediate(0xFFFFFFFF));
		assert(instruction);
		assert(*instruction == 7);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Rax, Immediate(0xFFFFFFFF));
		assert(instruction);
		assert(*instruction == 5);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Bpl, Register::Cl);
		assert(instruction);
		assert(*instruction == 0);
		static_cast<void>(instruction);
	}
	{
		const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Ax, Immediate(0xFF));
		assert(instruction);
		assert(*instruction == 8);
		static_cast<void>(instruction);
	}

	// Test assembling for 8-bit:

	// adc al, 22
	{
		const auto machineCode = Cas2Encode<>(Instruction::Adc, Register::Al, Immediate(22));
		assert(machineCode.Size() == 2);
		assert(machineCode[0] == 0x14);
		assert(machineCode[1] == 0x16);
		static_cast<void>(machineCode);
	}

	// adc bl, 0xFF
	{
		const auto machineCode = Cas2Encode<>(Instruction::Adc, Register::Bl, Immediate(0xFF));
		assert(machineCode.Size() == 3);
		assert(machineCode[0] == 0x80);
		assert(machineCode[1] == 0xD3);
		assert(machineCode[2] == 0xFF);
		static_cast<void>(machineCode);
	}

	// adc ch, 0xFF
	{
		const auto machineCode = Cas2Encode<>(Instruction::Adc, Register::Ch, Immediate(0xFF));
		assert(machineCode.Size() == 3);
		assert(machineCode[0] == 0x80);
		assert(machineCode[1] == 0xD5);
		assert(machineCode[2] == 0xFF);
		static_cast<void>(machineCode);
	}

	// adc ah, 0xFF
	{
		const auto machineCode = Cas2Encode<>(Instruction::Adc, Register::Ah, Immediate(0xFF));
		assert(machineCode.Size() == 3);
		assert(machineCode[0] == 0x80);
		assert(machineCode[1] == 0xD4);
		assert(machineCode[2] == 0xFF);
		static_cast<void>(machineCode);
	}
}

auto main(const int argc, const char* const* const argv) -> int
{
	static_cast<void>(argc);
	static_cast<void>(argv);
	std::cout << "Running CyberAsm tests...\n";

	RunAllTestsForX86();

	std::cout << "All tests ok!" << std::endl;

	return 0;
}
