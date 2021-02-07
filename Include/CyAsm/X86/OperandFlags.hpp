#pragma once

#include <cstdint>
#include <type_traits>

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

			Reg_16_32_64 = Reg16 | Reg32 | Reg64,
			Mem_16_32_64 = Mem16 | Mem32 | Mem64,
			RegMem_16_32_64 = Reg16 | Mem16 | Reg32 | Mem32 | Reg64 | Mem64,
		};

		using Flags = std::underlying_type<Enum>::type;

		static constexpr auto IsRegister(Flags flags) noexcept -> bool;
		static constexpr auto IsExplicitRegister(Flags flags) noexcept -> bool;
		static constexpr auto IsImmediate(Flags flags) noexcept -> bool;
		static constexpr auto IsMemory(Flags flags) noexcept -> bool;
	};

	constexpr auto OperandFlags::IsRegister(const Flags flags) noexcept -> bool
	{
		return flags > 0 && flags <= Reg64Rax;
	}

	constexpr auto OperandFlags::IsExplicitRegister(const Flags flags) noexcept -> bool
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
}
