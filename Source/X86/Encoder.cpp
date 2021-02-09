#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Encoder.hpp"
#include "../../Include/CyAsm/X86/Instructions.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"

namespace CyberAsm::X86
{
	auto Encode(const Instruction instruction, const std::span<const Operand> operands) -> EncodedInstruction
	{		
		const auto instructionIndex = static_cast<std::size_t>(instruction);
		const std::tuple<std::size_t, FixedSize> variation = DetermineInstructionVariation(instruction, operands);
		const std::size_t variationIndex = std::get<0>(variation);
		const FixedSize operandSize = std::get<1>(variation);
		const std::initializer_list<std::uint8_t>& machineCodeList = MachineCodeTable[instructionIndex];
		const bool twoByteOp = TwoByteOpcodeTable[instructionIndex];
		const std::uint8_t opCode = *(machineCodeList.begin() + variationIndex);

		EncodedInstruction encoded = {};
		auto& bits = encoded.Fields;
		bits.Prefix = (operandSize == FixedSize::B8 ? RexW64 : 0) & 0xFF;
		bits.OpCode &= 0x00'00'00U;
		bits.OpCode |= ((twoByteOp ? 0x0FU : opCode) & 0xFFU) << 8U & 0xFF'FF'FFU;
		bits.OpCode |= (twoByteOp ? opCode : 0x00U) & 0xFFU & 0xFF'FF'FFU;
		return encoded;
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
			auto opSize = FixedSize::B1;

			// Compare each passed operand flag with the variation.
			for (std::size_t j = 0; j < flagList.size(); ++j)
			{
				// The passed operand flags:
				OperandFlags::Flags givenFlags = operands[j].Flags();

				// If we have implicit registers, we need to add extra register flags, because the implicit registers are included.
				OperandFlags::Flags additionalFlags = OperandFlags::None;
				switch (givenFlags)
				{
						[[unlikely]] case OperandFlags::Reg8Al: additionalFlags = OperandFlags::Reg8;
						break;
						[[unlikely]] case OperandFlags::Reg16Ax: additionalFlags = OperandFlags::Reg16;
						break;
						[[unlikely]] case OperandFlags::Reg32Eax: additionalFlags = OperandFlags::Reg32;
						break;
						[[unlikely]] case OperandFlags::Reg64Rax: additionalFlags = OperandFlags::Reg64;
						break;
				}
				givenFlags |= additionalFlags;

				// The given flags which are required by the instruction.
				const OperandFlags::Flags required = *(flagList.begin() + j);

				// If the operand flags are set inside the given flag, increment the valid counter and add the operand size.
				if (required & givenFlags) [[unlikely]]
				{
					++validCount;
					opSize = static_cast<FixedSize>(std::max(static_cast<std::uint8_t>(opSize), static_cast<std::uint8_t>(OperandFlags::OperandByteSize(givenFlags))));
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
