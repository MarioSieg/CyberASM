#include "../../Include/CyAsm/X86/Encoder.hpp"

#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"

namespace CyberAsm::X86
{
	auto Encode(MachineStream& out, const Instruction instruction, std::span<const Operand> operands) -> EncoderResult
	{
		const std::optional<std::size_t> instructionVariation = DetermineInstructionVariation(instruction, operands);
		if (!instructionVariation) [[unlikely]]
		{
			return EncoderResult::NoInstructionVariationFound;
		}

		const std::initializer_list<std::u8string_view>& machineCodeList = MachineCodeTable[static_cast<std::size_t>(instruction)];

		const std::size_t machineCodeIndex = *instructionVariation;
		if (machineCodeIndex >= machineCodeList.size()) [[unlikely]]
		{
			return EncoderResult::InvalidMachineCodeIndex;
		}

		const char8_t* const machineCode = (machineCodeList.begin() + machineCodeIndex)->data();
		out << machineCode;

		WriteOperands(out, operands);

		return EncoderResult::Ok;
	}

	auto WriteOperands(MachineStream& out, const std::span<const Operand> operands) -> std::size_t
	{
		const auto prev = out.Size();

		for (const auto& operand : operands)
		{
			operand.FlushBytes(out);
		}

		return out.Size() - prev;
	}

	auto DetermineInstructionVariation(const Instruction instruction, const std::span<const Operand> operands) -> std::optional<std::size_t>
	{
		const auto index = static_cast<std::size_t>(instruction);

		for (std::size_t i = 0; i < OperandTable[index].size(); ++i)
		{
			const std::initializer_list<OperandFlags::Flags>& flagList = *(OperandTable[index].begin() + i);

			if (flagList.size() != operands.size()) [[unlikely]]
			{
				continue;
			}

			std::size_t validCount = 0;
			for (std::size_t j = 0; j < flagList.size(); ++j)
			{
				OperandFlags::Flags givenFlags = operands[j].Flags();
				switch (givenFlags)
				{
						[[unlikely]]
					case OperandFlags::Reg8Al:
						givenFlags |= OperandFlags::Reg8;
						break;

						[[unlikely]]
					case OperandFlags::Reg16Ax:
						givenFlags |= OperandFlags::Reg16;
						break;

						[[unlikely]]
					case OperandFlags::Reg32Eax:
						givenFlags |= OperandFlags::Reg32;
						break;

						[[unlikely]]
					case OperandFlags::Reg64Rax:
						givenFlags |= OperandFlags::Reg64;
						break;
				}
				const OperandFlags::Flags required = *(flagList.begin() + j);
				validCount += (required & givenFlags) != 0;
			}
			if (validCount == flagList.size())
			{
				return i;
			}
		}

		return std::nullopt;
	}
}
