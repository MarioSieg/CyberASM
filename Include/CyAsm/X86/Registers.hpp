#pragma once

#include "OperandType.hpp"

#include <cstdint>
#include <array>
#include <string_view>

namespace CyberAsm::X86
{
	/// <summary>
	/// Contains all supported registers.
	/// </summary>
	enum class Register: std::size_t
	{
		Ax,
		Ah,
		Al,

		Bx,
		Bh,
		Bl,

		Cx,
		Ch,
		Cl,

		Dx,
		Dh,
		Dl,

		Si,
		Sil,

		Di,
		Dil,

		Bp,
		Bpl,

		Sp,
		Spl,

		Cs,
		Ds,
		Es,
		Ss,
		Fs,
		Gs,

		Ip,

		Flags,

		Count
	};

	/// <summary>
	/// Contains the mnemonics of all registers.
	/// </summary>
	constexpr std::array<std::string_view, static_cast<std::size_t>(Register::Count)> RegisterMnemonicTable
	{
		"ax",
		"ah",
		"al",

		"bx",
		"bh",
		"bl",

		"cx",
		"ch",
		"cl",

		"dx",
		"dh",
		"dl",

		"si",
		"sil",

		"di",
		"dil",

		"bp",
		"bpl",

		"sp",
		"spl",

		"cs",
		"ds",
		"es",
		"ss",
		"fs",
		"gs",

		"ip",

		"flags"
	};

	/// <summary>
	/// Contains the size of all registers in bytes.
	/// </summary>
	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterSizeTable =
	{
		2, // ax
		1, // ah
		1, // al

		2, // bx
		1, // bh
		1, // bl

		2, // cx
		1, // ch
		1, // cl

		2, // dx
		1, // dh
		1, // dl

		2, // si
		1, // sil

		2, // di
		1, // dil

		2, // bp
		1, // bpl

		2, // sp
		1, // spl

		2, // cs
		2, // ds
		2, // es
		2, // ss
		2, // fs
		2, // gs

		2, // ip
		2 // flags
	};

	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterIdTable =
	{
		0x0, // ax
		0x0, // ah
		0x0, // al

		0x3, // bx
		0x3, // bh
		0x3, // bl

		0x1, // cx
		0x1, // ch
		0x1, // cl

		0x2, // dx
		0x2, // dh
		0x2, // dl

		0x6, // si
		0x6, // sil

		0x7, // di
		0x7, // dil

		0x0, // cs
		0x0, // ds
		0x0, // es
		0x0, // ss
		0x0, // fs
		0x0, // gs

		0x0, // ip
		0x0 // flags
	};

	constexpr std::array<InstructionOperandType, static_cast<std::size_t>(Register::Count)> RegisterMappingTable =
	{
		InstructionOperandType::Reg16Ax,
		InstructionOperandType::Reg8Hi,
		InstructionOperandType::Reg8Al,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8Hi,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8Hi,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16Dx,
		InstructionOperandType::Reg8Hi,
		InstructionOperandType::Reg8Cl,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg8,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16,

		InstructionOperandType::Reg16,
		InstructionOperandType::Reg16
	};
}
