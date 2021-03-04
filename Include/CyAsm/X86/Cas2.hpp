#pragma once

#include "../ByteChunk.hpp"
#include "../Immediate.hpp"

#include "MachineLanguage.hpp"
#include "Instructions.hpp"
#include "Registers.hpp"

namespace CyberAsm::X86
{
	template <Abi Arch = Abi::X86_64>
	[[nodiscard]]
	constexpr auto Cas2Encode(const Instruction instruction, const Register reg, const Immediate& immediate) -> ByteChunk
	{
		const WordSize registerSize = LookupRegisterSize(reg);
		WordSize immediateSize = ComputeRequiredBytes(immediate.UValue);

		if (immediateSize < registerSize) [[likely]]
		{
			// Extend to 32 bit size (only mov allows imm64)
			// TODO: Check if instruction is mov!
			immediateSize = registerSize == WordSize::QWord ? WordSize::DWord : registerSize;
		}
		else if (immediateSize > registerSize) [[unlikely]]
		{
			throw std::runtime_error("Immediate value is too large for destination register!");
		}
		
		const std::optional<std::size_t> variationOpt = AutoLookupInstruction(instruction, reg, immediateSize);
		if (!variationOpt) [[unlikely]]
		{
			throw std::runtime_error("Found no corresponding instruction for operand types!");
		}

		const std::size_t variation = *variationOpt;

		ByteChunk result = {};

		const bool isAnyOperand64Bit = IsMin64BitRegister(reg) || Is64BitOrLarger(immediateSize);

		// Using 64-bit operand size and the instruction does not default to 64-bit operand size?
		bool requiresRex = isAnyOperand64Bit;

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
		result.WriteFixedImmediate(immediate, immediateSize);

		return result;
	}
}
