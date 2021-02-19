#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86
{
	[[nodiscard]]
	constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& operand) -> ByteChunk
	{
		const auto variation = AutoMapAndLookup(instruction, reg, operand).value();

		ByteChunk result = {};

		if (RequiresTwoByteOpCode(instruction, variation)) [[likely]]
		{
			result << TwoByteOpCodePrefix;
		}

		result << FetchMachineByte(instruction, variation);

		return result;
	}
}
