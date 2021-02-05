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
		Eax,
		Ax,
		Ah,
		Al,

		Ebx,
		Bx,
		Bh,
		Bl,

		Ecx,
		Cx,
		Ch,
		Cl,

		Edx,
		Dx,
		Dh,
		Dl,

		Esi,
		Si,
		Sil,

		Edi,
		Di,
		Dil,

		Ebp,
		Bp,
		Bpl,

		Esp,
		Sp,
		Spl,

		Cs,
		Ds,
		Es,
		Ss,
		Fs,
		Gs,

		Eip,
		Ip,

		Eflags,
		Flags,

		Count
	};

	/// <summary>
	/// Contains the mnemonics of all registers.
	/// </summary>
	constexpr std::array<std::string_view, static_cast<std::size_t>(Register::Count)> RegisterMnemonicTable
	{
		"eax",
		"ax",
		"ah",
		"al",

		"ebx",
		"bx",
		"bh",
		"bl",

		"ecx",
		"cx",
		"ch",
		"cl",

		"edx",
		"dx",
		"dh",
		"dl",

		"esi",
		"si",
		"sil",

		"edi",
		"di",
		"dil",

		"ebp",
		"bp",
		"bpl",

		"esp",
		"sp",
		"spl",

		"cs",
		"ds",
		"es",
		"ss",
		"fs",
		"gs",

		"eip",
		"ip",

		"eflags",
		"flags"
	};

	/// <summary>
	/// Contains the size of all registers in bytes.
	/// </summary>
	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterSizeTable =
	{
		4,	// eax
		2,	// ax
		1,	// ah
		1,	// al

		4,	// ebx
		2,	// bx
		1,	// bh
		1,	// bl

		4,	// ecx
		2,	// cx
		1,	// ch
		1,	// cl

		4,	// edx
		2,	// dx
		1,	// dh
		1,	// dl

		4,	// esi
		2,	// si
		1,	// sil

		4,	// edi
		2,	// di
		1,	// dil

		4,	// ebp
		2,	// bp
		1,	// bpl

		4,	// esp
		2,	// sp
		1,	// spl
			
		2,	// cs
		2,	// ds
		2,	// es
		2,	// ss
		2,	// fs
		2,	// gs

		4,	// eip
		2,	// ip

		4,	// eflags
		2	// flags
	};

	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterIdTable =
	{
		0x0,	// eax
		0x0,	// ax
		0x0,	// ah
		0x0,	// al

		0x3,	// ebx
		0x3,	// bx
		0x3,	// bh
		0x3,	// bl

		0x1,	// ecx
		0x1,	// cx
		0x1,	// ch
		0x1,	// cl

		0x2,	// edx
		0x2,	// dx
		0x2,	// dh
		0x2,	// dl

		0x6,	// esi
		0x6,	// si
		0x6,	// sil

		0x7,	// edi
		0x7,	// di
		0x7,	// dil

		0x0,	// cs
		0x0,	// ds
		0x0,	// es
		0x0,	// ss
		0x0,	// fs
		0x0,	// gs

		0x0,	// eip
		0x0,	// ip

		0x0,	// eflags
		0x0		// flags
	};
}
