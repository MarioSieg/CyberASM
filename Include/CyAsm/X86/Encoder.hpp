#pragma once

#include "EncoderImpl.hpp"
#include "MachineLanguage.hpp"

namespace CyberAsm::X86
{
	template <TargetArchitecture Arch>
	[[nodiscard]] constexpr auto Encode(std::span<std::uint8_t>&& out, std::size_t& needle, const Instruction instruction, const std::span<const Operand> operands) -> Result
	{
		auto put = [&out, &needle](const std::uint8_t value) -> auto&
		{
			return out[needle++] = value;
		};

		if (const auto result = ValidateOperands(operands); result != Result::Ok) [[unlikely]]
		{
			return result;
		}

		InstructionData instr;
		if (const auto result = RetrieveInstructionData(instr, instruction, operands); result != Result::Ok) [[unlikely]]
		{
			return result;
		}

		const OpCodeData opc = RetrieveOpCodes(instruction, instr.VariationIndex);
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
		const auto registerCount = RetrieveRegisters(registerOperands, operands);

		if (registerCount == 0) [[unlikely]]
		{
			return Result::MemoryToMemoryOperands;
		}

		if (registerCount > 1 || !registerOperands[0].IsImplicit)
		{
			const std::uint8_t rmField = registerOperands[0].IsImplicit ? 0 : registerOperands[0].Address;             // 3 bits
			const std::uint8_t regField = opc.Extension.value_or(registerCount > 1 ? registerOperands[1].Address : 0); // 3 bits
			const std::uint8_t modField = mod;                                                                         // 2 bits
			put(PackByteBits233(modField, regField, rmField));
		}

		// TODO: Sib here

		if (const auto immediateData = RetrieveImmediate(operands); immediateData) [[unlikely]]
		{
			const auto& unpacked = *immediateData;
			for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(unpacked.Size); ++i)
			{
				put(static_cast<std::uint8_t>(unpacked.Value >> i * 8 & 0xFF));
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
