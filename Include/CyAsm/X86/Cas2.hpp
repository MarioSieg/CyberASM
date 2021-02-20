#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86
{
	template <Abi Arch = Abi::X86_64>
	[[nodiscard]] constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& operand) -> ByteChunk
	{
		const auto variation = AutoLookupInstruction(instruction, reg, operand).value();

		ByteChunk result = {};

		const auto isAnyOperand64Bit = IsMin64BitRegister(reg) || Is64BitOrLarger(ComputeRequiredBytes(operand.UValue));
		
		// Using 64-bit operand size and the instruction does not default to 64-bit operand size?
		auto requiresRex = isAnyOperand64Bit;

		// Using one of the extended registers (R8 to R15, XMM8 to XMM15, YMM8 to YMM15, CR8 to CR15 and DR8 to DR15)?
		requiresRex |= IsExtendedRegister(reg);

		// Using one of the uniform byte registers SPL, BPL, SIL or DIL ?
		requiresRex |= IsUniformByteRegister(reg);

		// A REX prefix must not be encoded when using one of the high byte registers AH, CH, BH or DH:
		requiresRex &= !IsHighByteRegister(reg);

		// REX
		if (requiresRex) [[likely]]
		{
			// The high 8-bit registers (AH, CH, DH, BH ) are not addressable when a REX prefix is used.
			if (IsHighByteRegister(reg)) [[unlikely]]
			{
				throw std::runtime_error("The high byte registers 'ah', 'bh', 'ch' and 'dh' are not addressable when a REX prefix is used!");
			}

			// Write REX prefix:
			result << PackByteRexPrefix(isAnyOperand64Bit, false, false, false);
		}

		// Opcode
		if (RequiresTwoByteOpCode(instruction, variation)) [[likely]]
		{
			result << TwoByteOpCodePrefix;
		}

		// Opcode
		result << FetchMachineByte(instruction, variation);

		// ModR/M:
		if (!IsAccumulator(reg)) [[likely]]
		{
			const auto modField = ModBitsRegisterAddressing;
			const auto regField = LookupOpCodeExtension(instruction, variation).value_or(0);
			const auto rmField = LookupRegisterId(reg);
			result << PackByteBitsModRmSib(modField, regField, rmField);
		}

		// SIB:
		// None

		// Displacement:
		// None

		// Immediate:
		result << operand;

		return result;
	}
}
