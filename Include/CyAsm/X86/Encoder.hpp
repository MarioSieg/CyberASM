#pragma once

#include <string_view>
#include <cstdint>
#include <optional>
#include <span>

namespace CyberAsm
{
	class MachineStream;

	namespace X86
	{
		class Operand;
		enum class Instruction : std::uint8_t;

		enum class EncoderResult
		{
			Ok = 0,
			NoInstructionVariationFound,
			InvalidMachineCodeIndex
		};

		[[nodiscard]]
		extern auto Encode(MachineStream& out, Instruction instruction, std::span<const Operand> operands) -> EncoderResult;

        extern void WriteOperands(MachineStream& out, std::span<const Operand> operands);

        [[nodiscard]]
		extern auto DetermineInstructionVariation(Instruction instruction, std::span<const Operand> operands) -> std::optional<std::size_t>;
	}
}
