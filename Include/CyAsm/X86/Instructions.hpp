#pragma once

#include <cstdint>
#include <array>

#include "OperandFlags.hpp"

namespace CyberAsm::X86
{
	enum class Instruction : std::uint8_t
	{
		Adc,
		Add,

		Count
	};

	constexpr std::array<std::initializer_list<std::initializer_list<OperandFlags::Flags>>, static_cast<std::size_t>(Instruction::Count)> OperandTable
	{
		// adc
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Reg8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
			{OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8},
			{OperandFlags::Reg_16_32_64, OperandFlags::RegMem_16_32_64},
			{OperandFlags::Reg8Al, OperandFlags::Imm8},
			{OperandFlags::Reg_Rax64_Eax32_Ax16, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		},
		// add
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Reg8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
			{OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8},
			{OperandFlags::Reg_16_32_64, OperandFlags::RegMem_16_32_64},
			{OperandFlags::Reg8Al, OperandFlags::Imm8},
			{OperandFlags::Reg_Rax64_Eax32_Ax16, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		}
	};

	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
		u8"\x10\x11\x12\x13\x14\x15\x80\x81\x83"_mach, // adc
		u8"\x00\x01\x02\x03\x04\x05\x80\x81\x83"_mach, // add
	};

	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeExtensionTable
	{
		u8"\xFF\xFF\xFF\xFF\xFF\xFF\x02\x02\x02"_mach, // adc
		u8"\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00"_mach, // add
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Instruction::Count)> MnemonicTable
	{
		"adc",
		"add"
	};

	constexpr std::array<bool, static_cast<std::size_t>(Instruction::Count)> TwoByteOpCodeTable
	{
		false, false
	};

	constexpr std::size_t MaxInstructionBytes = 16;

	consteval auto ValidateTables() noexcept -> bool
	{
		for (std::size_t i = 0; i < static_cast<std::size_t>(Instruction::Count); ++i)
		{
			if (MachineCodeTable[i].size() != MachineCodeExtensionTable[i].size()) [[unlikely]]
			{
				return false;
			}
		}
		return true;
	}

	static_assert(ValidateTables());
}
