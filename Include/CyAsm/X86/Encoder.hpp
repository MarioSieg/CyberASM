#pragma once

#include <span>
#include <optional>
#include <array>

#include "../Result.hpp"
#include "Instructions.hpp"
#include "MachineLanguage.hpp"
#include "Operand.hpp"

namespace CyberAsm::X86
{
	struct InstructionData final
	{
		std::size_t VariationIndex = 0;
		bool RequiresTwoBytes = false;
		FixedSize MaxOperandSize = FixedSize::Byte;
	};

	struct OpCodeData final
	{
		std::uint8_t Primary = 0;
		std::optional<std::uint8_t> Extension = 0;
	};

	struct ImmediateData final
	{
		std::uint32_t Value = 0;
		FixedSize Size = FixedSize::Byte;
	};

	struct RegisterData final
	{
		std::uint8_t Address = 0;
		bool IsImplicit = false;
		FixedSize Size = FixedSize::Byte;
	};

	constexpr auto GetOpCodes(const Instruction instruction, const std::size_t variationIndex) -> OpCodeData
	{
		const auto instructionIndex = static_cast<std::size_t>(instruction);
		const char8_t opCode = MachineCodeTable[instructionIndex][variationIndex];
		const char8_t extension = MachineCodeExtensionTable[instructionIndex][variationIndex];
		return {opCode, extension == u8'\xFF' ? std::nullopt : std::optional<std::uint8_t>(extension)};
	}

	constexpr auto GetImmediate(const std::span<const Operand> operands) noexcept -> std::optional<ImmediateData>
	{
		for (const auto& operand : operands)
		{
			if (operand.IsImmediate()) [[unlikely]]
			{
				return
				{
					{
						operand.Unwrap().Imm32.Value,
						operand.OperandByteSize()
					}
				};

			}
		}
		return std::nullopt;
	}

	constexpr auto GetRegisters(std::array<RegisterData, 3>& out, const std::span<const Operand> operands) noexcept -> std::size_t
	{
		std::size_t needle = 0;
		for (std::size_t i = 0; i < out.size() && i < operands.size(); ++i)
		{
			const auto& operand = operands[i];
			if (operand.IsExplicitRegister()) [[likely]]
			{
				const auto index = static_cast<std::size_t>(operand.Unwrap().Register);
				out[needle++] =
				{
					RegisterIdTable[index],
					operand.IsImplicitRegister(),
					operand.OperandByteSize()
				};
			}
		}
		return needle;
	}

	constexpr auto GetInstructionData(InstructionData& out, const Instruction instruction, const std::span<const Operand> operands) -> Result
	{
		auto determineInstructionVariation = [=](std::size_t& needle, FixedSize& size) -> Result
		{
			// The index of the instruction for all the lookup tables.
			const auto index = static_cast<std::size_t>(instruction);

			// Search for each instruction variation for the specified index.
			for (const std::initializer_list<OperandFlags::Flags>& flagList : OperandTable[index])
			{
				// If the operand count does not match, it won't work. Search the next one.
				if (flagList.size() != operands.size()) [[unlikely]]
				{
					continue;
				}

				// Count of valid operands. If it's the same as the total operand count, all are valid!
				// It's a match <3
				std::size_t validCount = 0;

				// Max byte size of operands.
				auto opSize = FixedSize::Byte;

				// Compare each passed operand flag with the variation.
				for (std::size_t j = 0; j < flagList.size(); ++j)
				{
					// The passed operand flags:
					OperandFlags::Flags givenFlags = operands[j].Flags();

					// If we have implicit registers, we need to add extra register flags, because the implicit registers are included.
					OperandFlags::Flags additionalFlags = OperandFlags::None;
					switch (givenFlags)
					{
							[[unlikely]]
						case OperandFlags::Reg8Al:
							additionalFlags = OperandFlags::Reg8;
							break;

							[[unlikely]]
						case OperandFlags::Reg16Ax:
							additionalFlags = OperandFlags::Reg16;
							break;

							[[likely]]
						case OperandFlags::Reg32Eax:
							additionalFlags = OperandFlags::Reg32;
							break;

							[[likely]]
						case OperandFlags::Reg64Rax:
							additionalFlags = OperandFlags::Reg64;
							break;
					}
					givenFlags |= additionalFlags;

					// The given flags which are required by the instruction.
					const OperandFlags::Flags required = *(flagList.begin() + j);

					// If the operand flags are set inside the given flag, increment the valid counter and add the operand size.
					if (required & givenFlags) [[unlikely]]
					{
						++validCount;
						const auto x = OperandFlags::OperandByteSize(givenFlags);
						opSize = static_cast<FixedSize>(std::max(static_cast<std::uint8_t>(opSize), static_cast<std::uint8_t>(x)));
					}
				}

				// If all operands are the same
				// we return the index in the variation list:
				if (validCount == flagList.size()) [[unlikely]]
				{
					// Compute the index by the pointer difference between the current item and the start pointer.
					const auto diff = static_cast<std::size_t>(static_cast<std::ptrdiff_t>(&flagList - OperandTable[index].begin()));
					needle = diff;
					size = opSize;
					return Result::Ok;
				}
			}

			return Result::NoInstructionVariationFound;
		};

		const auto instructionIndex = static_cast<std::size_t>(instruction);
		std::size_t variationIndex = 0;
		auto maxOpSize = FixedSize::Byte;
		if (const auto result = determineInstructionVariation(variationIndex, maxOpSize); result != Result::Ok) [[unlikely]]
		{
			return result;
		}
		const auto twoByte = TwoByteOpCodeTable[instructionIndex];
		out = {variationIndex, twoByte, maxOpSize};
		return Result::Ok;
	}

	constexpr auto ValidateOperands(const std::span<const Operand> operands) noexcept -> Result
	{
		std::size_t immOps = 0, memOps = 0;
		for (const auto op : operands)
		{
			if (op.IsImmediate()) [[unlikely]]
			{
				++immOps;
			}
			if (op.IsMemory()) [[unlikely]]
			{
				++memOps;
			}
		}
		return immOps == operands.size() ? Result::ImmediateToImmediateOperands : memOps == operands.size() ? Result::MemoryToMemoryOperands : Result::Ok;
	}

	template <TargetArchitecture Arch>
	[[nodiscard]] constexpr auto Encode(std::span<std::uint8_t>&& out, std::size_t& needle, const Instruction instruction, const std::span<const Operand> operands) -> Result
	{
		auto put = [&out, &needle](const std::uint8_t value) -> auto&
		{
			out[needle++] = value;
			return out;
		};

		if (const auto result = ValidateOperands(operands); result != Result::Ok) [[unlikely]]
		{
			return result;
		}

		InstructionData instr;
		if (const auto result = GetInstructionData(instr, instruction, operands); result != Result::Ok) [[unlikely]]
		{
			return result;
		}

		const OpCodeData opc = GetOpCodes(instruction, instr.VariationIndex);
		const auto mod = ModBitsRegisterAddressing;

		if constexpr (Arch == TargetArchitecture::X86_64) [[likely]]
		{
			if (instr.MaxOperandSize == FixedSize::QWord) [[likely]]
			{
				put(RexW64);
			}
			else if (instr.MaxOperandSize == FixedSize::Word) [[likely]]
			{
				put(OperandSizeOverride);
			}
		}

		if (instr.RequiresTwoBytes) [[unlikely]]
		{
			put(TwoByteOpCodePrefix);
		}

		put(opc.Primary);

		std::array<RegisterData, 3> registerOperands = {};
		const auto registerCount = GetRegisters(registerOperands, operands);

		if (registerCount == 0) [[unlikely]]
		{
			return Result::MemoryToMemoryOperands;
		}
		
		if (registerCount >= 1) [[likely]]
		{
			const std::uint8_t rmField = registerOperands[0].Address;                                                                            // 3 bits
			const std::uint8_t regField = opc.Extension.value_or(registerOperands[registerCount > 1 ? 1 : 0].Address); // 3 bits
			const std::uint8_t modField = mod;                                                                                                   // 2 bits
			put(PackByteBits233(modField, regField, rmField));
		}

		// TODO: Sib here

		if (const auto immediateData = GetImmediate(operands); immediateData) [[unlikely]]
		{
			const auto& unpacked = *immediateData;
			for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(unpacked.Size); ++i)
			{
				put(static_cast<std::uint8_t>(unpacked.Value >> i * CHAR_BIT & 0xFF));
			}
		}

		return Result::Ok;
	}

	template <TargetArchitecture Arch>
	[[nodiscard]] inline auto Encode(std::vector<std::uint8_t>& out, const Instruction instruction, const std::span<const Operand> operands) -> Result
	{
		std::array<std::uint8_t, MaxInstructionBytes> temp = {};
		std::size_t needle = 0;
		if (const auto result = Encode<Arch>(std::span<std::uint8_t>(temp.begin(), temp.end()), needle, instruction, operands); result != Result::Ok) [[unlikely]]
		{
			return result;
		}
		out.insert(out.end(), temp.begin(), temp.begin() + needle);
		return Result::Ok;
	}
}
