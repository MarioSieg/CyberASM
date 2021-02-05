#pragma once

#include "OperandType.hpp"

#include <cstdint>
#include <array>
#include <string_view>

namespace CyberAsm::X86
{
	enum class Instruction : std::uint8_t
	{
		/// <summary>
		/// ASCII adjust after addition
		/// </summary>
		Aaa,

		/// <summary>
		/// ASCII adjust AX before division
		/// </summary>
		Aad,

		/// <summary>
		/// ASCII adjust AX after multiply
		/// </summary>
		Aam,

		/// <summary>
		/// ASCII adjust AX after subtraction
		/// </summary>
		Aas,

		/// <summary>
		/// Addition
		/// </summary>
		Add,

		Count
	};

	/// <summary>
	/// Represents a variation of a instruction.
	/// For example the add instruction has multiple variations:
	/// add reg8, mem8
	/// add reg8, reg8
	/// etc..
	/// </summary>
	struct InstructionVariation final
	{
		/// <summary>
		/// Contains the operand types this variation is specialized for.
		/// </summary>
		std::initializer_list<std::underlying_type<InstructionOperandType::Enum>::type> OperandTypes = {};

		/// <summary>
		/// Contains the machine code as hex values.
		/// </summary>
		std::u8string_view MachineCode = {};

		/// <summary>
		/// Maximal operand size in bytes.
		/// </summary>
		std::uint8_t MaxOperandSize = 0;
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Instruction::Count)> MnemonicTable
	{
		"aaa",
		"aad",
		"aam",
		"aas",
		"add",
	};
	
	using Iot = InstructionOperandType;

	constexpr std::array<std::initializer_list<InstructionVariation>, static_cast<std::size_t>(Instruction::Count)> InstructionTable
	{
		/// <summary>
		/// aaa
		/// </summary>
		std::initializer_list<InstructionVariation>
		{
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8Al, Iot::Reg8Ah},
				.MachineCode = u8"\x37",
				.MaxOperandSize = 1,
			}
		},

		/// <summary>
		/// aad
		/// </summary>
		std::initializer_list<InstructionVariation>
		{
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8Al, Iot::Reg8Ah},
				.MachineCode = u8"\xD5\x0A",
				.MaxOperandSize = 1,
			}
		},

		/// <summary>
		/// aam
		/// </summary>
		std::initializer_list<InstructionVariation>
		{
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8Al, Iot::Reg8Ah},
				.MachineCode = u8"\xD4\x0A",
				.MaxOperandSize = 1,
			}
		},

		/// <summary>
		/// aas
		/// </summary>
		std::initializer_list<InstructionVariation>
		{
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8Al, Iot::Reg8Ah},
				.MachineCode = u8"\x3F",
				.MaxOperandSize = 1,
			}
		},
		
		/// <summary>
		/// add
		/// </summary>
		std::initializer_list<InstructionVariation>
		{
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8, Iot::Reg8},
				.MachineCode = u8"\x00",
				.MaxOperandSize = 1,
			},
			
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8 | Iot::Reg16 | Iot::Mem16 | Iot::Reg32 | Iot::Mem32, Iot::Reg16 | Iot::Reg32},
				.MachineCode = u8"\x01",
				.MaxOperandSize = 4,
			},
			
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8, Iot::Reg8 | Iot::Mem8},
				.MachineCode = u8"\x02",
				.MaxOperandSize = 1,
			},
			
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg16 | Iot::Reg32, Iot::Mem16 | Iot::Mem32},
				.MachineCode = u8"\x03",
				.MaxOperandSize = 4,
			},

			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8Al, Iot::Imm8},
				.MachineCode = u8"\x04",
				.MaxOperandSize = 1,
			},
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg32Eax, Iot::Imm16 | Iot::Imm32},
				.MachineCode = u8"\x05",
				.MaxOperandSize = 4,
			},
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8, Iot::Imm8},
				.MachineCode = u8"\x80",
				.MaxOperandSize = 1,
			},
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8 | Iot::Reg16 | Iot::Mem16 | Iot::Reg32 | Iot::Mem32, Iot::Imm8, Iot::Imm16 | Iot::Imm32},
				.MachineCode = u8"\x81",
				.MaxOperandSize = 4,
			},
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8, Iot::Imm8},
				.MachineCode = u8"\x82",
				.MaxOperandSize = 1,
			},
			InstructionVariation
			{
				.OperandTypes = {Iot::Reg8 | Iot::Mem8, Iot::Imm8},
				.MachineCode = u8"\x83",
				.MaxOperandSize = 1,
			},
		},
	};
}
