#pragma once

#include <array>
#include <variant>

namespace CyberAsm
{
	enum class Result: std::size_t
	{
		Ok = 0,
		NoInstructionVariationFound,
		MemoryToMemoryOperands,
		ImmediateToImmediateOperands,
		ToLittleOperands,
		TooManyOperands,
		Count
	};

	constexpr std::array<std::string_view, static_cast<std::size_t>(Result::Count)> ErrorMessageTable =
	{
		"Ok",
		"The specified instruction requires at least one register as operand!",
		"Memory to memory operands are not allowed! ",
		"Immediate to immediate operands are not allowed!",
		"Too many operands for specified instruction!",
		"Too little operands for specified instruction!",
	};

	inline auto operator <<(std::ostream& out, const Result result) -> std::ostream&
	{
		return out << ErrorMessageTable[static_cast<std::size_t>(result)];
	}
}
