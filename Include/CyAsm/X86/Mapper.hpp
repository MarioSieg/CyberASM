#pragma once

#include <stdexcept>

#include "../Immediate.hpp"
#include "../MachineLanguage.hpp"
#include "OperandFlags.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86::Mapper
{
	constexpr auto MapFlags(const Immediate& imm) -> OperandFlags::Flags
	{
		switch (ComputeRequiredBytes(imm.UValue))
		{
				[[unlikely]] case WordSize::HWord: return OperandFlags::Imm8;
				[[unlikely]] case WordSize::Word: return OperandFlags::Imm16;
				[[likely]] case WordSize::DWord: return OperandFlags::Imm32;
				[[likely]] case WordSize::QWord: return OperandFlags::Imm64;
				[[unlikely]] default: throw std::runtime_error("not implemented");
		}
	}

	constexpr auto MapFlags(const WordSize immSize) -> OperandFlags::Flags
	{
		switch (immSize)
		{
				[[unlikely]] case WordSize::HWord: return OperandFlags::Imm8;
				[[unlikely]] case WordSize::Word: return OperandFlags::Imm16;
				[[likely]] case WordSize::DWord: return OperandFlags::Imm32;
				[[likely]] case WordSize::QWord: return OperandFlags::Imm64;
				[[unlikely]] default: throw std::runtime_error("not implemented");
		}
	}

	constexpr auto MapFlags(const Register register_) -> OperandFlags::Flags
	{
		// @formatter:off
		// Check if register is accumulator:
		if(IsAccumulator(register_)) [[unlikely]]
		{
			switch (RegisterSizeTable[static_cast<std::size_t>(register_)])
			{
				[[unlikely]] case WordSize::HWord: return OperandFlags::Reg8Al;
				[[unlikely]] case WordSize::Word:  return OperandFlags::Reg16Ax;
				[[likely]]	 case WordSize::DWord: return OperandFlags::Reg32Eax;
				[[likely]]   case WordSize::QWord: return OperandFlags::Reg64Rax;
				[[unlikely]] default: throw std::runtime_error("not implemented");
			}
		}

		// Else lookup size and convert it:
		switch (RegisterSizeTable[static_cast<std::size_t>(register_)])
		{
				[[unlikely]] case WordSize::HWord: return OperandFlags::Reg8;
				[[unlikely]] case WordSize::Word:  return OperandFlags::Reg16;
				[[likely]]   case WordSize::DWord: return OperandFlags::Reg32;
				[[likely]]   case WordSize::QWord: return OperandFlags::Reg64;
				[[unlikely]] default: throw std::runtime_error("not implemented");
		}
		// @formatter:on
	}
}
