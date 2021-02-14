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

		Ymm0,
		Ymm1,
		Ymm2,
		Ymm3,
		Ymm4,
		Ymm5,
		Ymm6,
		Ymm7,
		Ymm8,
		Ymm9,
		Ymm10,
		Ymm11,
		Ymm12,
		Ymm13,
		Ymm14,
		Ymm15,

		Count
	};

	/// <summary>
	/// Contains the mnemonics of all registers.
	/// </summary>
	constexpr std::array<std::string_view, static_cast<std::size_t>(Register::Count)> RegisterMnemonicTable
	{
		"rax",
		"eax",
		"ax",
		"ah",
		"al",

		"rbx",
		"ebx",
		"bx",
		"bh",
		"bl",

		"rcx",
		"ecx",
		"cx",
		"ch",
		"cl",

		"rdx",
		"edx",
		"dx",
		"dh",
		"dl",

		"rsi",
		"esi",
		"si",
		"sil",

		"rdi",
		"edi",
		"di",
		"dil",

		"rbp",
		"ebp",
		"bp",
		"bpl",

		"rsp",
		"esp",
		"sp",
		"spl",

		"rip",
		"eip",
		"ip",

		"rflags",
		"eflags",
		"flags",

		"st0",
		"st1",
		"st2",
		"st3",
		"st4",
		"st5",
		"st6",
		"st7",

		"mm0",
		"mm1",
		"mm2",
		"mm3",
		"mm4",
		"mm5",
		"mm6",
		"mm7",

		"es",
		"cs",
		"ss",
		"ds",
		"fs",
		"gs",

		"xmm0",
		"xmm1",
		"xmm2",
		"xmm3",
		"xmm4",
		"xmm5",
		"xmm6",
		"xmm7",
		"xmm8",
		"xmm9",
		"xmm10",
		"xmm11",
		"xmm12",
		"xmm13",
		"xmm14",
		"xmm15",

		"ymm0",
		"ymm1",
		"ymm2",
		"ymm3",
		"ymm4",
		"ymm5",
		"ymm6",
		"ymm7",
		"ymm8",
		"ymm9",
		"ymm10",
		"ymm11",
		"ymm12",
		"ymm13",
		"ymm14",
		"ymm15",
	};

	/// <summary>
	/// Contains the size of all registers in bytes.
	/// </summary>
	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterSizeTable =
	{
		8, // rax
		4, // eax
		2, // ax
		1, // ah
		1, // al

		8, // rbx
		4, // ebx
		2, // bx
		1, // bh
		1, // bl

		8, // rcx
		4, // ecx
		2, // cx
		1, // ch
		1, // cl

		8, // rdx
		4, // edx
		2, // dx
		1, // dh
		1, // dl

		8, // rsi
		4, // esi
		2, // si
		1, // sil

		8, // rdi
		4, // edi
		2, // di
		1, // dil

		8, // rbp
		4, // ebp
		2, // bp
		1, // bpl

		8, // rsp
		4, // esp
		2, // sp
		1, // spl

		8, // rip
		4, // eip
		2, // ip

		8, // rflags
		4, // eflags
		2, // flags

		10, // st0
		10, // st1
		10, // st2
		10, // st3
		10, // st4
		10, // st5
		10, // st6
		10, // st7

		8, // mm0
		8, // mm1
		8, // mm2
		8, // mm3
		8, // mm4
		8, // mm5
		8, // mm6
		8, // mm7

		2, // es
		2, // cs
		2, // ss
		2, // ds
		2, // fs
		2, //gs

		16, // xmm0
		16, // xmm1
		16, // xmm2
		16, // xmm3
		16, // xmm4
		16, // xmm5
		16, // xmm6
		16, // xmm7
		16, // xmm8
		16, // xmm9
		16, // xmm10
		16, // xmm11
		16, // xmm12
		16, // xmm13
		16, // xmm14
		16, // xmm15

		32, // ymm0
		32, // ymm1
		32, // ymm2
		32, // ymm3
		32, // ymm4
		32, // ymm5
		32, // ymm6
		32, // ymm7
		32, // ymm8
		32, // ymm9
		32, // ymm10
		32, // ymm11
		32, // ymm12
		32, // ymm13
		32, // ymm14
		32  // ymm15
	};

	constexpr std::array<std::uint8_t, static_cast<std::size_t>(Register::Count)> RegisterIdTable =
	{
		0x0, // rax
		0x0, // eax
		0x0, // ax
		0x0, // ah
		0x0, // al

		0x3, // rbx
		0x3, // ebx
		0x3, // bx
		0x3, // bh
		0x3, // bl

		0x1, // rcx
		0x1, // ecx
		0x1, // cx
		0x1, // ch
		0x1, // cl

		0x2, // rdx
		0x2, // edx
		0x2, // dx
		0x2, // dh
		0x2, // dl

		0x6, // rsi
		0x6, // esi
		0x6, // si
		0x6, // sil

		0x7, // rdi
		0x7, // edi
		0x7, // di
		0x7, // dil

		0x15, // rip
		0x15, // eip
		0x15, // ip

		0x0, // rflags
		0x0, // eflags
		0x0, // flags

		0x30, // st0
		0x31, // st1
		0x32, // st2
		0x33, // st3
		0x34, // st4
		0x35, // st5
		0x36, // st6
		0x37, // st7

		0x40, // mm0
		0x41, // mm1
		0x42, // mm2
		0x43, // mm3
		0x44, // mm4
		0x45, // mm5
		0x46, // mm6
		0x47, // mm7

		0x60, // es
		0x61, // cs
		0x62, // ss
		0x63, // ds
		0x64, // fs
		0x65, // gs

		0x50, // xmm0
		0x51, // xmm1
		0x52, // xmm2
		0x53, // xmm3
		0x54, // xmm4
		0x55, // xmm5
		0x56, // xmm6
		0x57, // xmm7
		0x58, // xmm8
		0x59, // xmm9
		0x5A, // xmm10
		0x5B, // xmm11
		0x5C, // xmm12
		0x5D, // xmm13
		0x5E, // xmm14
		0x5F, // xmm15
	};
}
