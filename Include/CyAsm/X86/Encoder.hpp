#pragma once

#include <span>
#include <optional>
#include <array>

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
		const auto opCode = *(MachineCodeTable[instructionIndex].begin() + variationIndex);
		const auto extension = *(MachineCodeExtensionTable[instructionIndex].begin() + variationIndex);
		return {opCode, extension == -1 ? std::nullopt : std::optional<std::uint8_t>(extension)};
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

	constexpr auto GetRegisterId(const std::span<const Operand> operands) noexcept -> std::optional<RegisterData>
	{
		for (const auto& operand : operands)
		{
			if (operand.IsRegister()) [[likely]]
			{
				const auto index = static_cast<std::size_t>(operand.Unwrap().Register);
				return
				{
					{
						RegisterIdTable[index],
						operand.IsImplicitRegister(),
						operand.OperandByteSize()
					}
				};
			}
		}
		return std::nullopt;
	}

	constexpr auto DetermineInstructionVariation(const Instruction instruction, const std::span<const Operand> operands) -> std::optional<std::tuple<std::size_t, FixedSize>>
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
				return {std::make_tuple(diff, opSize)};
			}
		}

		return std::nullopt;
	}

	constexpr auto GetInstructionData(const Instruction instruction, const std::span<const Operand> operands) -> std::optional<InstructionData>
	{
		const auto instructionIndex = static_cast<std::size_t>(instruction);
		const auto variation = DetermineInstructionVariation(instruction, operands);
		const auto variationIndex = std::get<0>(variation.value());
		const auto maxOpSize = std::get<1>(variation.value());
		const auto twoByte = TwoByteOpCodeTable[instructionIndex];
		if (variationIndex >= MachineCodeTable[instructionIndex].size() || static_cast<std::uint8_t>(maxOpSize) > static_cast<std::uint8_t>(FixedSize::QWord)) [[unlikely]]
		{
			return std::nullopt;
		}
		return {{variationIndex, twoByte, maxOpSize}};
	}

	template <typename... T>
	[[nodiscard]] constexpr auto VariadicArrayConstruct(T&&... values) -> decltype(auto)
	{
		return std::array<std::decay_t<std::common_type_t<T...>>, sizeof...(T)>{std::forward(values)...};
	}

	template <TargetArchitecture Arch>
	constexpr auto Encode(std::span<std::uint8_t>&& out, std::size_t& needle, const Instruction instruction, const std::span<const Operand> operands) -> std::size_t
	{
		const auto sizeBackup = operands.size();

		const InstructionData instr = GetInstructionData(instruction, operands).value();
		const OpCodeData opc = GetOpCodes(instruction, instr.VariationIndex);

		const auto mod = ModBitsRegisterAddressing;

		if constexpr (Arch == TargetArchitecture::X86_64) [[likely]]
		{
			if (instr.MaxOperandSize == FixedSize::QWord) [[likely]]
			{
				out[needle++] = RexW64;
			}
			else if (instr.MaxOperandSize == FixedSize::Word) [[likely]]
			{
				out[needle++] = OperandSizeOverride;
			}
		}

		if (instr.RequiresTwoBytes) [[unlikely]]
		{
			out[needle++] = TwoByteOpCodePrefix;
		}

		out[needle++] = opc.Primary;

		if (const auto reg = GetRegisterId(operands); reg && !(*reg).IsImplicit) [[likely]]
		{
			const auto unpacked = *reg;
			const auto rmField = unpacked.Address; // 3 bits
			const auto regField = opc.Extension.value_or(0); // 3 bits
			const auto modField = mod; // 2 bits
			out[needle++] = PackByte233(modField, regField, rmField);
		}

		// TODO: Sib here

		if (const auto immediateData = GetImmediate(operands); immediateData) [[unlikely]]
		{
			const auto& unpacked = *immediateData;
			for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(unpacked.Size); ++i)
			{
				out[needle++] = static_cast<std::uint8_t>(unpacked.Value >> i * 8 & 0xFF);
			}
		}

		return operands.size() - sizeBackup;
	}


	template <TargetArchitecture Arch>
	inline auto Encode(std::vector<std::uint8_t>& out, const Instruction instruction, const std::span<const Operand> operands) -> std::size_t
	{
		std::array<std::uint8_t, MaxInstructionBytes> temp = {};
		auto&& view = std::span<std::uint8_t>(temp.begin(), temp.end());
		std::size_t needle = 0;
		Encode<Arch>(std::move(view), needle, instruction, operands);
		out.insert(out.end(), temp.begin(), temp.begin() + needle);
		return needle;
	}
}
