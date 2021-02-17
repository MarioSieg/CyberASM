#pragma once

#include <cstdint>
#include <type_traits>

#include "../Utils.hpp"

namespace CyberAsm::X86
{
	struct OperandFlags final
	{
		enum Enum : std::uint32_t
		{
			None = 0,

			Reg8 = 1 << 1,
			Reg16 = 1 << 2,
			Reg32 = 1 << 3,
			Reg64 = 1 << 4,

			Reg8Al = 1 << 5,
			Reg16Ax = 1 << 6,
			Reg32Eax = 1 << 7,
			Reg64Rax = 1 << 8,

			Mem8 = 1 << 9,
			Mem16 = 1 << 10,
			Mem32 = 1 << 11,
			Mem64 = 1 << 12,

			Imm8 = 1 << 13,
			Imm16 = 1 << 14,
			Imm32 = 1 << 15,
			Imm64 = 1 << 16,

			AnyGpr = Reg8 | Reg8Al | Reg16 | Reg16Ax | Reg32 | Reg32Eax | Reg64 | Reg64Rax,
			AnyMem = Mem8 | Mem16 | Mem32 | Mem64,
			AnyImm = Imm8 | Imm16 | Imm32 | Imm64,
			AnyImplicitAkkuGpr = Reg8Al | Reg16Ax | Reg32Eax | Reg64Rax,
			AnyGpr16To64 = Reg16 | Reg16Ax | Reg32 | Reg32Eax | Reg64 | Reg64Rax,
			AnyMem16To64 = Mem16 | Mem32 | Mem64,
			AnyGprOrMem16To64 = Reg16 | Reg16Ax | Mem16 | Reg32 | Reg32Eax | Mem32 | Reg64 | Reg64Rax | Mem64,
			ImplicitAkkuGpr16To64 = Reg64Rax | Reg32Eax | Reg16Ax
		};

		using Flags = std::underlying_type<Enum>::type;

		[[nodiscard]] static constexpr auto IsExplicitRegister(Flags flags) noexcept -> bool;
		[[nodiscard]] static constexpr auto IsImplicitRegister(Flags flags) noexcept -> bool;
		[[nodiscard]] static constexpr auto IsImmediate(Flags flags) noexcept -> bool;
		[[nodiscard]] static constexpr auto IsMemory(Flags flags) noexcept -> bool;
		[[nodiscard]] static constexpr auto OperandByteSize(Flags flags) noexcept -> FixedSize;
	};

	constexpr auto OperandFlags::IsExplicitRegister(const Flags flags) noexcept -> bool
	{
		return flags > 0 && flags <= Reg64Rax;
	}

	constexpr auto OperandFlags::IsImplicitRegister(const Flags flags) noexcept -> bool
	{
		return flags >= Reg8Al && flags <= Reg64Rax;
	}

	constexpr auto OperandFlags::IsImmediate(const Flags flags) noexcept -> bool
	{
		return flags >= Imm8 && flags <= Imm64;
	}

	constexpr auto OperandFlags::IsMemory(const Flags flags) noexcept -> bool
	{
		return flags >= Mem8 && flags <= Mem64;
	}

	constexpr auto OperandFlags::OperandByteSize(const Flags flags) noexcept -> FixedSize
	{
		if (flags == Reg64Rax || flags & Reg64 || flags & Mem64 || flags & Imm64) [[likely]]
		{
			return FixedSize::QWord;
		}
		if (flags == Reg32Eax || flags & Reg32 || flags & Mem32 || flags & Imm32) [[likely]]
		{
			return FixedSize::DWord;
		}
		if (flags == Reg16Ax || flags & Reg16 || flags & Mem16 || flags & Imm16) [[unlikely]]
		{
			return FixedSize::Word;
		}
		return FixedSize::Byte;
	}
}
