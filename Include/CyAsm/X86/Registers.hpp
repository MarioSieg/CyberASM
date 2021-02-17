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
	};

	constexpr std::array<Register, 4> Accumulators
	{
		Register::Al,
		Register::Ax,
		Register::Eax,
		Register::Rax
	};

	/// <summary>
	/// Contains the size of all registers in bytes.
	/// </summary>
	constexpr std::array<WordSize, static_cast<std::size_t>(Register::Count)> RegisterSizeTable =
	{
		WordSize::QWord, // rax
		WordSize::DWord, // eax
		WordSize::Word,  // ax
		WordSize::HWord, // ah
		WordSize::HWord, // al

		WordSize::QWord, // rbx
		WordSize::DWord, // ebx
		WordSize::Word,  // bx
		WordSize::HWord, // bh
		WordSize::HWord, // bl

		WordSize::QWord, // rcx
		WordSize::DWord, // ecx
		WordSize::Word,  // cx
		WordSize::HWord, // ch
		WordSize::HWord, // cl

		WordSize::QWord, // rdx
		WordSize::DWord, // edx
		WordSize::Word,  // dx
		WordSize::HWord, // dh
		WordSize::HWord, // dl

		WordSize::QWord, // rsi
		WordSize::DWord, // esi
		WordSize::Word,  // si
		WordSize::HWord, // sil

		WordSize::QWord, // rdi
		WordSize::DWord, // edi
		WordSize::Word,  // di
		WordSize::HWord, // dil

		WordSize::QWord, // rbp
		WordSize::DWord, // ebp
		WordSize::Word,  // bp
		WordSize::HWord, // bpl

		WordSize::QWord, // rsp
		WordSize::DWord, // esp
		WordSize::Word,  // sp
		WordSize::HWord, // spl

		WordSize::QWord, // rip
		WordSize::DWord, // eip
		WordSize::Word,  // ip

		WordSize::QWord, // rflags
		WordSize::DWord, // eflags
		WordSize::Word,  // flags

		WordSize::WordQWord, // st0
		WordSize::WordQWord, // st1
		WordSize::WordQWord, // st2
		WordSize::WordQWord, // st3
		WordSize::WordQWord, // st4
		WordSize::WordQWord, // st5
		WordSize::WordQWord, // st6
		WordSize::WordQWord, // st7

		WordSize::QWord, // mm0
		WordSize::QWord, // mm1
		WordSize::QWord, // mm2
		WordSize::QWord, // mm3
		WordSize::QWord, // mm4
		WordSize::QWord, // mm5
		WordSize::QWord, // mm6
		WordSize::QWord, // mm7

		WordSize::Word, // es
		WordSize::Word, // cs
		WordSize::Word, // ss
		WordSize::Word, // ds
		WordSize::Word, // fs
		WordSize::Word, //gs

		WordSize::OWord, // xmm0
		WordSize::OWord, // xmm1
		WordSize::OWord, // xmm2
		WordSize::OWord, // xmm3
		WordSize::OWord, // xmm4
		WordSize::OWord, // xmm5
		WordSize::OWord, // xmm6
		WordSize::OWord, // xmm7
		WordSize::OWord, // xmm8
		WordSize::OWord, // xmm9
		WordSize::OWord, // xmm10
		WordSize::OWord, // xmm11
		WordSize::OWord, // xmm12
		WordSize::OWord, // xmm13
		WordSize::OWord, // xmm14
		WordSize::OWord, // xmm15
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
