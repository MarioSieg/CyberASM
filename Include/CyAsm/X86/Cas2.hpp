#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"
#include "../Result.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"


namespace CyberAsm::X86
{
	[[nodiscard]]
	constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& operand) -> std::variant<ByteChunk, Result>
	{
		const auto index = static_cast<std::size_t>(instruction);
		const auto subIndex = LookupOptimalInstructionVariation<OperandFlags::AnyGpr, OperandFlags::AnyImm>(instruction);
		const auto& operandList = OperandTable[index];

		ByteChunk result = {};

		if (TwoByteOpCodeTable[index]) [[likely]]
		{
			result.PushBack(TwoByteOpCodePrefix);
		}

		result.PushBack(MachineCodeTable[index][0]);

		return result;
	}
}
