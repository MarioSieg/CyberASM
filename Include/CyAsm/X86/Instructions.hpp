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
#include "OperandTable.inl"
	};

	/// <summary>
	/// Contains the machine code for each entry above.
	/// </summary>
	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeTable
	{
#include "MachineCodeTable.inl"
	};

	/// <summary>
	/// Contains op code extensions and two byte escapes.
	/// FF = no extension
	/// 0F = requires to byte op code escape
	/// * = the extension between 0-7 (3 bits for mod/rm byte)
	/// </summary>
	constexpr std::array<std::u8string_view, static_cast<std::size_t>(Instruction::Count)> MachineCodeExtensionTable
	{
#include "MachineCodeExtensionTable.inl"
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Instruction::Count)> MnemonicTable
	{
#include "MnemonicTable.inl"
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

	constexpr auto LookupOpCodeExtension(const Instruction instr, const std::size_t variation) -> std::optional<std::uint8_t>
	{
		return RequiresOpCodeExtension(instr, variation) ? MachineCodeExtensionTable[static_cast<std::size_t>(instr)][variation] : 0;
	}

	[[nodiscard]] constexpr auto LookupOptimalInstructionVariation(const Instruction instr, const std::span<const OperandFlags::Flags> operands) -> std::optional<std::size_t>
	{
		// @formatter:off
		const auto index = static_cast<std::size_t>(instr);
		const auto& table = OperandTable[index];
		for (std::size_t i = 0; i < table.size(); ++i)
		{
			const auto& variation = *(table.begin() + i);
			if (variation.size() != operands.size()) [[unlikely]]
			{
				continue;
			}
			std::size_t validated = 0;
			for (std::size_t j = 0; j < operands.size(); ++j)
			{
				auto requested = operands[j];
				if (OperandFlags::IsImplicitRegister(requested)) [[unlikely]]
				{
					switch (requested)
					{
						[[unlikely]] case OperandFlags::Reg8Al:   requested |= OperandFlags::Reg8;  break;
						[[unlikely]] case OperandFlags::Reg16Ax:  requested |= OperandFlags::Reg16; break;
						[[likely]]	 case OperandFlags::Reg32Eax: requested |= OperandFlags::Reg32; break;
						[[likely]]	 case OperandFlags::Reg64Rax: requested |= OperandFlags::Reg64; break;
						[[unlikely]] default: throw std::runtime_error("Invalid implicit GPR! Must be 'al', 'ax', 'eax' or 'rax'!");
					}
				}
				const auto required = *(variation.begin() + j);
				validated += (requested & required) != OperandFlags::None;
			}
			if (validated == operands.size()) [[unlikely]]
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
	[[nodiscard]] constexpr auto AutoLookupInstruction(const Instruction instr, Ts&&... args) -> std::optional<std::size_t>
	{
		const std::initializer_list<const OperandFlags::Flags> collection{Mapper::MapFlags(args)...};
		return LookupOptimalInstructionVariation(instr, collection);
	}

	/// <summary>
	/// A REX prefix must be encoded when:
	///		- using 64 - bit operand size and the instruction does not default to 64 - bit operand size; or
	///		- using one of the extended registers(R8 to R15, XMM8 to XMM15, YMM8 to YMM15, CR8 to CR15and DR8 to DR15); or
	///		- using one of the uniform byte registers SPL, BPL, SIL or DIL.
	///		
	/// A REX prefix must not be encoded when :
	///		- using one of the high byte registers AH, CH, BH or DH.
	///
	///	In all other cases, the REX prefix is ignored. The use of multiple REX prefixes is undefined, although processors seem to use only the last REX prefix.	
	///	Instructions that default to 64 - bit operand size in long mode are :
	///		CALL(near)	ENTER	Jcc
	///		JrCXZ	JMP(near)	LEAVE
	///		LGDT	LIDT	LLDT
	///		LOOP	LOOPcc	LTR
	///		MOV CR(n)	MOV DR(n)	POP reg / mem
	///		POP reg	POP FS	POP GS
	///		POPFQ	PUSH imm8	PUSH imm32
	///		PUSH reg / mem	PUSH reg	PUSH FS
	///		PUSH GS	PUSHFQ	RET(near)
	/// </summary>
	/// <param name="instr">The target instruction.</param>
	/// <param name="variation">The instruction variation.</param>
	/// <returns>True if required, else false.</returns>
	template <Abi Arch>
	[[nodiscard]] constexpr auto RequiresRexPrefix(const Instruction instr, const std::size_t variation) -> bool
	{
		// Is long mode?
		if constexpr (Arch != Abi::X86_64)
		{
			return false;
		}

		const auto& operands = *(OperandTable[static_cast<std::size_t>(instr)].begin() + variation);
		for (const auto flags : operands)
		{
			if (Is64BitOrLarger(OperandFlags::OperandByteSize(flags))) [[likely]]
			{
				return true;
			}
		}

		return false;
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
