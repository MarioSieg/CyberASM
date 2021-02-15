#pragma once

#include <cstdint>
#include <array>

#include "OperandFlags.hpp"
#include "FeatureFlags.hpp"

namespace CyberAsm::X86
{
	enum class Instruction : std::uint8_t
	{
		// Add with carry
		Adc,

		// Add
		Add,

		// Bitwise and
		And,

		// Bit scan forward
		Bsf,

		// Bit scan reverse
		Bsr,

		// Byte swap
		BSwap,

		// Bit test
		Bt,

		// Bit test and complement
		Btc,

		// Bit test and reset
		Btr,

		// Bit test and set
		Bts,

		// Call procedure
		Call,

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
		},
		// and
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
		// bsf
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{{OperandFlags::Reg_16_32_64, OperandFlags::RegMem_16_32_64}},
		// bsr
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{{OperandFlags::Reg_16_32_64, OperandFlags::RegMem_16_32_64}},
		// bswap
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{{OperandFlags::Reg_16_32_64}},
		// bt
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		},
		// btc
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
		},
		// btr
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		},
		// bts
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::RegMem_16_32_64, OperandFlags::Reg_16_32_64},
			{OperandFlags::RegMem_16_32_64, OperandFlags::Imm8},
		},
		// call
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			// Actually: rel8/16??
			{OperandFlags::Reg8 | OperandFlags::Reg16},
			{OperandFlags::RegMem_16_32},
			{OperandFlags::Reg64 | OperandFlags::Mem64},
			{OperandFlags::Mem_16_32_64},
		},
	};

	constexpr std::array<FeatureFlags::Flags, static_cast<std::size_t>(Instruction::Count)> FeatureFlagTable
	{
		FeatureFlags::None, // adc
		FeatureFlags::None, // add
		FeatureFlags::None, // and
		FeatureFlags::None, // bsf
		FeatureFlags::None, // bsr
		FeatureFlags::None, // bswap
		FeatureFlags::None, // bt
		FeatureFlags::None, // btc
		FeatureFlags::None, // btr
		FeatureFlags::None, // bts
		FeatureFlags::None, // call
	};

	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
		u8"\x10\x11\x12\x13\x14\x15\x80\x81\x83"_mach, // adc
		u8"\x00\x01\x02\x03\x04\x05\x80\x81\x83"_mach, // add
		u8"\x20\x21\x22\x23\x24\x25\x80\x81\x83"_mach, // and
		u8"\xBC"_mach,                                 // bsf
		u8"\xBD"_mach,                                 // bsr
		u8"\xC8"_mach,                                 // bswap
		u8"\xA3\xBA"_mach,                             // bt
		u8"\xBA\xBB"_mach,                             // btc
		u8"\xB3\xBA"_mach,                             // btr
		u8"\xAB\xBA"_mach,                             // bts
		u8"\xE8\xFF\xFF\xFF"_mach,                     // call
	};

	/// <summary>
	/// FF = no extension
	/// AA = indicates that the ModR/M byte contains a register operand and an r/m operand
	/// else the value of the op code extension (values from 0 through 7).
	/// </summary>
	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeExtensionTable
	{
		u8"\xAA\xAA\xAA\xAA\xFF\xFF\x02\x02\x02"_mach, // adc
		u8"\xAA\xAA\xAA\xAA\xFF\xFF\x00\x00\x00"_mach, // add
		u8"\xAA\xAA\xAA\xAA\xFF\xFF\x04\x04\x04"_mach, // and
		u8"\xAA"_mach,                                 // bsf
		u8"\xAA"_mach,                                 // bsr
		u8"\xFF"_mach,                                 // bswap
		u8"\xAA\x4"_mach,                              // bt
		u8"\x07\xAA"_mach,                             // btc
		u8"\xAA\x06"_mach,                             // btr
		u8"\xAA\x05"_mach,                             // bts
		u8"\xFF\x02\x02\x03"_mach,                     // call
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Instruction::Count)> MnemonicTable
	{
		"adc",
		"add",
		"bsf",
		"bsr",
		"bswap",
		"bt",
		"btc",
		"btr",
		"bts",
		"call"
	};

	constexpr std::array<bool, static_cast<std::size_t>(Instruction::Count)> TwoByteOpCodeTable
	{
		false, // adc
		false, // add
		true,  // and
		true,  // bsf
		true,  // bsr
		true,  // bswap
		true,  // bt
		true,  // btc
		true,  // btr
		true,  // bts
		false, // call
	};

	constexpr std::size_t MaxInstructionBytes = 16;

	consteval auto ValidateTables() noexcept -> bool
	{
		for (std::size_t i = 0; i < static_cast<std::size_t>(Instruction::Count); ++i)
		{
			if (OperandTable[i].size() != MachineCodeTable[i].size() || MachineCodeTable[i].size() != MachineCodeExtensionTable[i].size()) [[unlikely]]
			{
				return false;
			}
		}
		return true;
	}

	static_assert(ValidateTables());
}
