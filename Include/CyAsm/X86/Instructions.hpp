#pragma once

#include <cstdint>
#include <optional>
#include <array>
#include <bitset>

#include "OperandFlags.hpp"

namespace CyberAsm
{
	class MachineStream;
}

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

	constexpr std::array<std::initializer_list<std::uint8_t>, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
		// adc
		std::initializer_list<std::uint8_t>
		{
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x80, 0x81, 0x83
		}
	};

	constexpr std::array<bool, static_cast<std::size_t>(Instruction::Count)> TwoByteOpcodeTable
	{
		// adc
		false
	};

	constexpr std::array<std::initializer_list<std::uint8_t>, static_cast<std::size_t>(Instruction::Count)> MachineCodeExtensionTable
	{
		// adc
		std::initializer_list<std::uint8_t>
		{
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2, 0x2, 0x2
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
