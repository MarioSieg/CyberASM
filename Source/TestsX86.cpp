#include <cassert>

#include "../Include/CyAsm/X86/Instructions.hpp"

namespace CyberAsm
{
	void RunAllTestsForX86()
	{
		using namespace X86;

		{
			const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg64, OperandFlags::Imm32>(Instruction::Adc);
			assert(instruction);
			assert(*instruction == 7);
			(void)instruction;
		}
		{
			const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg64Rax, OperandFlags::Imm32>(Instruction::Adc);
			assert(instruction);
			assert(*instruction == 5);
			(void)instruction;
		}
		{
			const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg8, OperandFlags::Reg8>(Instruction::Adc);
			assert(instruction);
			assert(*instruction == 0);
			(void)instruction;
		}
		{
			const auto instruction = LookupOptimalInstructionVariation<OperandFlags::Reg16Ax, OperandFlags::Imm8>(Instruction::Adc);
			assert(instruction);
			assert(*instruction == 8);
			(void)instruction;
		}
		{
			const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Rbx, Immediate(0xFFFFFFFF));
			assert(instruction);
			assert(*instruction == 7);
			(void)instruction;
		}
		{
			const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Rax, Immediate(0xFFFFFFFF));
			assert(instruction);
			assert(*instruction == 5);
			(void)instruction;
		}
		{
			const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Bpl, Register::Cl);
			assert(instruction);
			assert(*instruction == 0);
			(void)instruction;
		}
		{
			const auto instruction = AutoLookupInstruction(Instruction::Adc, Register::Ax, Immediate(0xFF));
			assert(instruction);
			assert(*instruction == 8);
			(void)instruction;
		}
	}
}
