#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Encoder.hpp"
#include "../../Include/CyAsm/X86/Instructions.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"

namespace CyberAsm::X86
{
	auto Encode(MachineStream& out, const Instruction instruction, std::span<const Operand> operands) -> EncoderResult
	{
        // First get the instruction variation, which is determined by the operands:
		const std::optional<std::size_t> instructionVariation = DetermineInstructionVariation(instruction, operands);

        // If no corresponding instruction was found, return error.
		if (!instructionVariation) [[unlikely]]
		{
			return EncoderResult::NoInstructionVariationFound;
		}

        // Next get the list of the machine codes for each variation:
		const std::initializer_list<std::u8string_view>& machineCodeList = MachineCodeTable[static_cast<std::size_t>(instruction)];

        // If we got a weird machine code index which is too large, return error. (Should not happen, but let's be safe!)
        if (*instructionVariation >= machineCodeList.size()) [[unlikely]]
		{
			return EncoderResult::InvalidMachineCodeIndex;
		}

        // Get the machine code literal at the index of the variation.
        const char8_t* const machineCode = (machineCodeList.begin() + *instructionVariation)->data();

        // Write the machine code into the stream.
		out << machineCode;

        // Now write all operands into the stream.
		WriteOperands(out, operands);

		return EncoderResult::Ok;
	}

    void WriteOperands(MachineStream& out, const std::span<const Operand> operands)
	{
        // Write all bytes for each operand into the machine stream.
		for (const auto& operand : operands)
		{
			operand.FlushBytes(out);
		}
	}

	auto DetermineInstructionVariation(const Instruction instruction, const std::span<const Operand> operands) -> std::optional<std::size_t>
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

            // Compare each passed operand flag with the variation.
			for (std::size_t j = 0; j < flagList.size(); ++j)
			{
                // The passed operand flags:
				OperandFlags::Flags givenFlags = operands[j].Flags();

                // If we have implicit registers, we need to add extra register flags, because the implicit registers are included.
                OperandFlags::Flags additionalFlags = OperandFlags::None;
				switch (givenFlags)
				{
                    [[unlikely]] case OperandFlags::Reg8Al:     additionalFlags = OperandFlags::Reg8;  break;
                    [[unlikely]] case OperandFlags::Reg16Ax:    additionalFlags = OperandFlags::Reg16; break;
                    [[unlikely]] case OperandFlags::Reg32Eax:   additionalFlags = OperandFlags::Reg32; break;
                    [[unlikely]] case OperandFlags::Reg64Rax:   additionalFlags= OperandFlags::Reg64; break;
				}
                givenFlags |= additionalFlags;

                // The gived flags which are required by the instruction.
				const OperandFlags::Flags required = *(flagList.begin() + j);

                // If the operand flags are set inside the given flag, increment the valid counter.
				validCount += (required & givenFlags) != 0;
			}

            // If all operands were the same, it's a match <3
            // So we return the index in the variation list:
            if (validCount == flagList.size()) [[unlikely]]
			{
                // Compute the index by the pointer difference between the current item and the start pointer.
                return static_cast<std::size_t>(static_cast<std::ptrdiff_t>(&flagList - OperandTable[index].begin()));
			}
		}

		return std::nullopt;
	}
}
