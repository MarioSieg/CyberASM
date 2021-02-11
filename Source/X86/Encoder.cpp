#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Encoder.hpp"
#include "../../Include/CyAsm/X86/Instructions.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"
#include "../../Include/CyAsm/X86/MachineLanguage.hpp"

namespace CyberAsm::X86
{
    static inline void GetInstructionData(const Instruction instruction, const std::span<const Operand> operands, std::size_t& variationIndex, FixedSize& maxOpSize, bool& twoByte)
    {
        const auto instructionIndex = static_cast<std::size_t>(instruction);
        const auto variation = DetermineInstructionVariation(instruction, operands);
        variationIndex = std::get<0>(variation);
        maxOpSize = std::get<1>(variation);
        twoByte = TwoByteOpcodeTable[instructionIndex];
        if(variationIndex >= MachineCodeTable[instructionIndex].size() || static_cast<std::uint8_t>(maxOpSize) > static_cast<std::uint8_t>(FixedSize::QWord)) [[unlikely]]
        {
            throw std::runtime_error("invalid variation index or size!");
        }
    }

    static inline void GetOpCodes(const Instruction instruction, const std::size_t variationIndex, std::uint8_t& opCode, std::uint8_t& opCodeEx)
    {
        const auto instructionIndex = static_cast<std::size_t>(instruction);
        opCode = *(MachineCodeTable[instructionIndex].begin() + variationIndex);
        opCodeEx = *(MachineCodeExtensionTable[instructionIndex].begin() + variationIndex);
    }

	auto Encode(MachineStream& out, const Instruction instruction, const std::span<const Operand> operands) -> std::size_t
	{
        const auto sizeBackup = operands.size();

        std::size_t variationIndex;
        FixedSize maxOperandSize;
        bool isTwoByteInstruction;
        GetInstructionData(instruction, operands, variationIndex, maxOperandSize, isTwoByteInstruction);

        std::uint8_t opCode, opCodeEx;
        GetOpCodes(instruction, variationIndex, opCode, opCodeEx);

		const std::uint8_t mod = ModBitsRegisterAddressing;
		const std::uint8_t imm = 0xFF;
		const std::uint8_t reg = RegisterIdTable[static_cast<std::size_t>(Register::Eax)];

        if (maxOperandSize == FixedSize::QWord) [[unlikely]]
		{
			out << RexW64;
		}

        if (isTwoByteInstruction) [[unlikely]]
		{
			out << TwoByteOpCodePrefix;
		}

		out << opCode;

		const union ModRm
		{
			struct
			{
				std::uint8_t Rm : 3;
				std::uint8_t Reg : 3;
				std::uint8_t Mod : 2;
			} Bits;
			std::uint8_t Packed;
			static_assert(sizeof Bits == 1);
		} modRm = { .Bits = {.Rm = reg, .Reg = opCodeEx, .Mod = mod} };

		out << modRm.Packed;

		const union Sib
		{
			struct
			{
				std::uint8_t Scale : 2;
				std::uint8_t Index : 3;
				std::uint8_t Base : 3;
			} Bits;
			std::uint8_t Packed;

			static_assert(sizeof Bits == 1);
		} sib = { .Bits = {0, 0, 0} };

		if (sib.Packed) [[likely]]
		{
			out << sib.Packed;
		}
		out << imm;

        return operands.size() - sizeBackup;
	}

	auto DetermineInstructionVariation(const Instruction instruction, const std::span<const Operand> operands) -> std::tuple<std::size_t, FixedSize>
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

			// If all operands are the same, it's a match <3
			// So we return the index in the variation list:
			if (validCount == flagList.size()) [[unlikely]]
			{
				// Compute the index by the pointer difference between the current item and the start pointer.
				const auto diff = static_cast<std::size_t>(static_cast<std::ptrdiff_t>(&flagList - OperandTable[index].begin()));
				return std::make_tuple(diff, opSize);
			}
		}

		throw std::runtime_error("no matching instruction found!");
	}
}
