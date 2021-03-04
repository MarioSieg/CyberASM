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

		R8,
		R8D,
		R8W,
		R8B,

		R9,
		R9D,
		R9W,
		R9B,

		R10,
		R10D,
		R10W,
		R10B,

		R11,
		R11D,
		R11W,
		R11B,

		R12,
		R12D,
		R12W,
		R12B,

		R13,
		R13D,
		R13W,
		R13B,

		R14,
		R14D,
		R14W,
		R14B,

		R15,
		R15D,
		R15W,
		R15B,

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

	[[nodiscard]]
	constexpr auto LookupRegisterId(const Register reg) -> std::uint8_t
	{
		return RegisterIdTable[static_cast<std::size_t>(reg)];
	}

	[[nodiscard]]
	constexpr auto LookupRegisterSize(const Register reg) -> WordSize
	{
		return RegisterSizeTable[static_cast<std::size_t>(reg)];
	}

	/// <summary>
	/// Checks if the register is an implicit accumulator GPR.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is an implicit accumulator GPR.</returns>
	[[nodiscard]]
	constexpr auto IsAccumulator(const Register reg) noexcept -> bool
	{
		return reg == Register::Al || reg == Register::Ax || reg == Register::Eax || reg == Register::Rax;
	}

	/// <summary>
	/// Checks if the register is a high-byte register such as ah, bh, ch or dh.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is a high-byte such as ah, bh, ch and dh.</returns>
	[[nodiscard]]
	constexpr auto IsHighByteRegister(const Register reg) noexcept -> bool
	{
		return reg == Register::Ah || reg == Register::Bh || reg == Register::Ch || reg == Register::Dh;
	}

	/// <summary>
	/// Checks if the register is a uniform byte register such as spl, bpl, sil or dil.
	/// </summary>
	/// <param name="reg">The target register.</param>
	/// <returns>True if the register is a uniform high register such as spl, bpl, sil or dil, else false.</returns>
	[[nodiscard]]
	constexpr auto IsUniformByteRegister(const Register reg) noexcept -> bool
	{
		return reg == Register::Spl || reg == Register::Bpl || reg == Register::Sil || reg == Register::Dil;
	}

	/// <summary>
	/// Checks if the register is 64 bit or larger.
	/// </summary>
	/// <param name="reg"></param>
	/// <returns></returns>
	[[nodiscard]]
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
	[[nodiscard]]
	constexpr auto IsExtendedRegister(const Register reg) noexcept -> bool
	{
		const auto val = static_cast<std::size_t>(reg);
		return
			(val >= static_cast<std::size_t>(Register::R8) &&
			val <= static_cast<std::size_t>(Register::R15B))
			||
			(val >= static_cast<std::size_t>(Register::Xmm0) &&
			val <= static_cast<std::size_t>(Register::Xmm15));
	}
}
