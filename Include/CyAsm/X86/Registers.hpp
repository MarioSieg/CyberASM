#pragma once

#include <cstdint>
#include <array>
#include <string_view>

namespace CyberAsm::X86
{
	/// <summary>
	/// Contains all supported registers.
	/// </summary>
	enum class Register: std::size_t
	{
		Rax,
		Eax,
		Ax,
		Ah,
		Al,

		Rbx,
		Ebx,
		Bx,
		Bh,
		Bl,

		Rcx,
		Ecx,
		Cx,
		Ch,
		Cl,

		Rdx,
		Edx,
		Dx,
		Dh,
		Dl,

		Rsi,
		Esi,
		Si,
		Sil,

		Rdi,
		Edi,
		Di,
		Dil,

		Rbp,
		Ebp,
		Bp,
		Bpl,

		Rsp,
		Esp,
		Sp,
		Spl,

		Rip,
		Eip,
		Ip,

		Rflags,
		Eflags,
		Flags,

		St0,
		St1,
		St2,
		St3,
		St4,
		St5,
		St6,
		St7,

		Mm0,
		Mm1,
		Mm2,
		Mm3,
		Mm4,
		Mm5,
		Mm6,
		Mm7,

		Es,
		Cs,
		Ss,
		Ds,
		Fs,
		Gs,

		Xmm0,
		Xmm1,
		Xmm2,
		Xmm3,
		Xmm4,
		Xmm5,
		Xmm6,
		Xmm7,
		Xmm8,
		Xmm9,
		Xmm10,
		Xmm11,
		Xmm12,
		Xmm13,
		Xmm14,
		Xmm15,

		Count
	};

	/// <summary>
	/// Contains the mnemonics of all registers.
	/// </summary>
	constexpr std::array<std::string_view, static_cast<std::size_t>(Register::Count)> RegisterMnemonicTable
	{
		#include "RegisterMnemonicTable.inl"
	};

	/// <summary>
	/// Contains the size of all registers in bytes.
	/// </summary>
	constexpr std::array<WordSize, static_cast<std::size_t>(Register::Count)> RegisterSizeTable =
	{
		#include "RegisterSizeTable.inl"
	};

	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterIdTable =
	{
		#include "RegisterIdTable.inl"
	};

	[[nodiscard]] constexpr auto LookupRegisterId(const Register reg) -> std::uint8_t
	{
		return RegisterIdTable[static_cast<std::size_t>(reg)];
	}

	/// <summary>
	/// Checks if the register is an implicit accumulator GPR.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is an implicit accumulator GPR.</returns>
	constexpr auto IsAccumulator(const Register reg) noexcept -> bool
	{
		return reg == Register::Al || reg == Register::Ax || reg == Register::Eax || reg == Register::Rax;
	}

	/// <summary>
	/// Checks if the register is a high-byte register such as ah, bh, ch or dh.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is a high-byte such as ah, bh, ch and dh.</returns>
	constexpr auto IsHighByteRegister(const Register reg) noexcept -> bool
	{
		return reg == Register::Ah || reg == Register::Bh || reg == Register::Ch || reg == Register::Dh;
	}

	/// <summary>
	/// Checks if the register is a uniform byte register such as spl, bpl, sil or dil.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is a uniform high register such as spl, bpl, sil or dil, else false.</returns>
	constexpr auto IsUniformByteRegister(const Register reg) noexcept -> bool
	{
		return reg == Register::Spl || reg == Register::Bpl || reg == Register::Sil || reg == Register::Dil;
	}

	/// <summary>
	/// Checks if the register is 64 bit or larger.
	/// </summary>
	/// <param name="reg"></param>
	/// <returns></returns>
	constexpr auto IsMin64BitRegister(const Register reg) noexcept -> bool
	{
		return Is64BitOrLarger(RegisterSizeTable[static_cast<std::size_t>(reg)]);
	}

	/// <summary>
	/// Checks if the register is a 64-bit extended register such as:
	/// R8 to R15, XMM8 to XMM15, YMM8 to YMM15, CR8 to CR15 and DR8 to DR15
	/// </summary>
	/// <param name="reg"></param>
	/// <returns></returns>
	constexpr auto IsExtendedRegister(const Register reg) noexcept -> bool
	{
		(void)reg;
		// TODO
		return false;
	}
}
