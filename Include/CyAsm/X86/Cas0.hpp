#pragma once

#include "../ByteChunk.hpp"
#include "../Result.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"

namespace CyberAsm::X86
{
	template <TargetArchitecture Arch>
	[[nodiscard]]
	constexpr auto Encode0(const Instruction instruction) -> std::variant<ByteChunk, Result>
	{
		const auto index = static_cast<std::size_t>(instruction);

		if (OperandTable[index].size() > 0) [[unlikely]]
		{
			return Result::TooManyOperands;
		}

		ByteChunk result = {};

		if (TwoByteOpCodeTable[index]) [[likely]]
		{
			result.PushBack(TwoByteOpCodePrefix);
		}

		result.PushBack(MachineCodeTable[index]);

		return Result::Ok;
	}
}
