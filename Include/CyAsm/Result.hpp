#pragma once

#include <array>
#include <string_view>

namespace CyberAsm
{
	enum class Result: std::size_t
	{
		Ok = 0,
		NoInstructionVariationFound,
		MemoryToMemoryOperands,
		ImmediateToImmediateOperands,

		Count
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Result::Count)> ErrorMessageTable =
	{
		"Ok",
		"The instruction requires at least one register as operand! Please check the operand types!",
		"Memory to memory operands are not allowed! Please check the operand types!",
		"Immediate to immediate operands are not allowed! Please check the operand types!"
	};

	inline auto operator <<(std::ostream& out, const Result result) -> std::ostream&
	{
		return out << ErrorMessageTable[static_cast<std::size_t>(result)];
	}
}
