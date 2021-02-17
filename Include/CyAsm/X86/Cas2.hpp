#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"

#include "Mapper.hpp"
#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86
{
	[[nodiscard]]
	constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& operand) -> ByteChunk
	{
		std::array<OperandFlags::Flags, 2> values = {Mapper::MapFlags(reg), Mapper::MapFlags(operand)};
		const auto variation = LookupOptimalInstructionVariation(instruction, values).value();

		ByteChunk result = {};

		if (RequiresTwoByteOpCode(instruction, variation)) [[likely]]
		{
			result << TwoByteOpCodePrefix;
		}

		result << FetchMachineByte(instruction, variation);

		return result;
	}
}
