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

	constexpr std::array<Register, 4> Accumulators
	{
		Register::Al,
		Register::Ax,
		Register::Eax,
		Register::Rax
	};

	constexpr auto IsAccumulator(const Register reg) noexcept -> bool
	{
		return std::find(Accumulators.begin(), Accumulators.end(), reg) != Accumulators.end();
	}

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
}
