#pragma once

#include "OperandFlags.hpp"
#include "Prefix.hpp"

#include <cstdint>
#include <string_view>
#include <array>

namespace CyberAsm::X86
{
	enum class Instruction : std::uint8_t
	{
		Adc,

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
			{OperandFlags::Reg64Rax, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		},
	};

	constexpr std::array<std::initializer_list<std::u8string_view>, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
		// adc
		std::initializer_list<std::u8string_view>
		{
			u8"\x10", u8"\x11", u8"\x12", u8"\x13", u8"\x14", u8"\x15", u8"\x80", u8"\x81", u8"\x83"
		}
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Instruction::Count)> MnemonicTable
	{
		"adc"
	};

	consteval auto ValidateTables() noexcept -> bool
	{
		for (std::size_t i = 0; i < static_cast<std::size_t>(Instruction::Count); ++i)
		{
			if (OperandTable[i].size() != MachineCodeTable[i].size()) [[unlikely]]
			{
				return false;
			}
		}
		return true;
	}

	constexpr auto AreTablesValidated = ValidateTables();
	static_assert(AreTablesValidated);
}
