#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Encoder.hpp"
#include "../../Include/CyAsm/X86/Instructions.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"

namespace CyberAsm::X86
{
	void Encode(MachineStream& out, const Instruction instruction, std::span<const Operand> operands)
	{
		const auto instructionIndex = static_cast<std::size_t>(instruction);

		// First get the instruction variation, which is determined by the operands:
		const std::tuple<std::size_t, Size> variation = DetermineInstructionVariation(instruction, operands);

		const std::size_t variationIndex = std::get<0>(variation);
		const Size maxOpSize = std::get<1>(variation);

		// Next get the list of the machine codes for each variation:
		const std::initializer_list<std::u8string_view>& machineCodeList = MachineCodeTable[instructionIndex];

		// If we got a weird machine code index which is too large, return error. (Should not happen, but let's be safe!)
		if (variationIndex >= machineCodeList.size()) [[unlikely]]
		{
			throw std::runtime_error("invalid instruction variation index!");
		}

		if (maxOpSize == Size::B8) [[likely]]
		{
			out << static_cast<char8_t>(PrefixType::RexW64);
		}
		else if (maxOpSize == Size::B4) [[likely]]
		{
			out << static_cast<char8_t>(PrefixType::AddressOverride);
		}

		// Get the machine code literal at the index of the variation.
		const char8_t* const machineCode = (machineCodeList.begin() + variationIndex)->data();

		// Write the machine code into the stream.
		out << machineCode;

		// Now write all operands into the stream.
		WriteOperands(out, operands);
	}

	void WriteOperands(MachineStream& out, const std::span<const Operand> operands)
	{
		// Write all bytes for each operand into the machine stream.
		for (const auto& operand : operands)
		{
			operand.FlushBytes(out);
		}
	}

	auto DetermineInstructionVariation(const Instruction instruction, const std::span<const Operand> operands) -> std::tuple<std::size_t, Size>
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
			auto opSize = Size::B1;

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
					opSize = static_cast<Size>(std::max(static_cast<std::uint8_t>(opSize), static_cast<std::uint8_t>(OperandFlags::OperandByteSize(givenFlags))));
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
