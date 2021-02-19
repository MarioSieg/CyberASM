#pragma once

#include <string_view>
#include <cstdint>
#include <array>
#include <optional>
#include <span>
#include <stdexcept>

#include "../MachineLanguage.hpp"
#include "MachineLanguage.hpp"
#include "OperandFlags.hpp"
#include "Mapper.hpp"

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
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::AnyGpr16To64},
			{OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8},
			{OperandFlags::AnyGpr16To64, OperandFlags::AnyGprOrMem16To64},
			{OperandFlags::Reg8Al, OperandFlags::Imm8},
			{OperandFlags::ImplicitAkkuGpr16To64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8},
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm8},
		},
		// add
		std::initializer_list<std::initializer_list<OperandFlags::Flags>>
		{
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Reg8},
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::AnyGpr16To64},
			{OperandFlags::Reg8, OperandFlags::Reg8 | OperandFlags::Mem8},
			{OperandFlags::AnyGpr16To64, OperandFlags::AnyGprOrMem16To64},
			{OperandFlags::Reg8Al, OperandFlags::Imm8},
			{OperandFlags::ImplicitAkkuGpr16To64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::Reg8 | OperandFlags::Mem8, OperandFlags::Imm8},
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm16 | OperandFlags::Imm32},
			{OperandFlags::AnyGprOrMem16To64, OperandFlags::Imm8},
		}
	};

	/// <summary>
	/// Contains the machine code for each entry above.
	/// </summary>
	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
		u8"\x10\x11\x12\x13\x14\x15\x80\x81\x83"_mach, // adc
		u8"\x00\x01\x02\x03\x04\x05\x80\x81\x83"_mach, // add
	};

	/// <summary>
	/// Contains op code extensions and two byte escapes.
	/// FF = no extension
	/// 0F = requires to byte op code escape
	/// * = the extension between 0-7 (3 bits for mod/rm byte)
	/// </summary>
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

	constexpr auto FetchMachineByte(const Instruction instr, const std::size_t variation) -> std::uint8_t
	{
		return MachineCodeTable[static_cast<std::size_t>(instr)][variation];
	}

	constexpr auto RequiresTwoByteOpCode(const Instruction instr, const std::size_t variation) -> bool
	{
		return MachineCodeExtensionTable[static_cast<std::size_t>(instr)][variation] == TwoByteOpCodePrefix;
	}

	constexpr auto RequiresOpCodeExtension(const Instruction instr, const std::size_t variation) -> bool
	{
		const auto val = MachineCodeExtensionTable[static_cast<std::size_t>(instr)][variation];
		return val != TwoByteOpCodePrefix && variation != 0xFF;
	}
	
	[[nodiscard]] constexpr auto LookupOptimalInstructionVariation(const Instruction instr, const std::span<const OperandFlags::Flags> values) -> std::optional<std::size_t>
	{
		// @formatter:off
		const auto index = static_cast<std::size_t>(instr);
		const auto& table = OperandTable[index];
		for (std::size_t i = 0; i < table.size(); ++i)
		{
			const auto& variation = *(table.begin() + i);
			if (variation.size() != values.size()) [[unlikely]]
			{
				continue;
			}
			std::size_t validated = 0;
			for (std::size_t j = 0; j < values.size(); ++j)
			{
				auto requested = values[j];
				if (OperandFlags::IsImplicitRegister(requested)) [[unlikely]]
				{
					switch (requested)
					{
							[[unlikely]] case OperandFlags::Reg8Al: requested |= OperandFlags::Reg8; break;
							[[unlikely]] case OperandFlags::Reg16Ax: requested |= OperandFlags::Reg16; break;
							[[unlikely]] case OperandFlags::Reg32Eax: requested |= OperandFlags::Reg32; break;
							[[unlikely]] case OperandFlags::Reg64Rax: requested |= OperandFlags::Reg64; break;
							[[unlikely]] default: throw std::runtime_error("invalid implicit gpr");
					}
				}
				const auto required = *(variation.begin() + j);
				validated += (requested & required) != OperandFlags::None;
			}
			if (validated == values.size()) [[unlikely]]
			{
				return i;
			}
		}
		return std::nullopt;
		// @formatter:on
	}

	template <OperandFlags::Flags... F>
	[[nodiscard]] constexpr auto LookupOptimalInstructionVariation(const Instruction instr) -> std::optional<std::size_t>
	{
		const std::array<const OperandFlags::Flags, sizeof...(F)> collection = {F...};
		return LookupOptimalInstructionVariation(instr, collection);
	}

	template <typename... Ts>
	[[nodiscard]] constexpr auto AutoMapAndLookup(const Instruction instr, Ts&&... args) -> std::optional<std::size_t>
	{
		const std::initializer_list<const OperandFlags::Flags> collection{Mapper::MapFlags(args)...};
		return LookupOptimalInstructionVariation(instr, collection);
	}

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
