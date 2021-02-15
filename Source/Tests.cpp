#include <cassert>
#include <iostream>
#include <tuple>

#include "../Include/CyAsm/MachineStream.hpp"
#include "../Include/CyAsm/MachineLanguage.hpp"
#include "../Include/CyAsm/X86/Encoder.hpp"
#include "../Include/CyAsm/X86/Operand.hpp"

using namespace CyberAsm;
using namespace X86;

auto main() -> int
{
	std::ios::sync_with_stdio(false);
	
	static constexpr std::array<std::u8string_view, 22> CorrectMachineCode
	{
		u8"\x14\x05"_mach,			// adc al, 5
		u8"\x80\xD4\x05"_mach,		// adc ah, 5
		u8"\x10\xE0"_mach,			// adc al, ah
		u8"\x10\xFC"_mach,			// adc ah, bh
		u8"\x10\xCB"_mach,			// adc bl, cl
		u8"\x40\x10\xC6"_mach,		// adc sil, al
		u8"\x66\x83\xD0\x0A"_mach,	// adc ax, 10
		u8"\x66\x83\xD3\x04"_mach,	// adc bx, 4
		u8"\x66\x11\xD8"_mach,		// adc ax, bx
		u8"\x66\x11\xC6"_mach,		// adc si, ax
		u8"\x66\x11\xDF"_mach,		// adc di, bx
		u8"\x83\xD0\x0A"_mach,		// adc eax, 10
		u8"\x83\xD3\x04"_mach,		// adc ebx, 4
		u8"\x11\xD8"_mach,			// adc eax, ebx
		u8"\x11\xC6"_mach,			// adc esi, eax
		u8"\x11\xDF"_mach,			// adc edi, ebx
		u8"\x48\x83\xD0\x0A"_mach,	// adc rax, 10
		u8"\x48\x83\xD3\x04"_mach,	// adc rbx, 4
		u8"\x48\x11\xD8"_mach,		// adc rax, rbx
		u8"\x48\x11\xC6"_mach,		// adc rsi, rax
		u8"\x48\x11\xDF"_mach,		// adc rdi, rbx
		u8"\x48\x11\xE4"_mach,		// adc rsp, rsp
	};

	static const std::array<std::array<Operand, 2>, 22> Operands
	{
		std::array<Operand, 2>{ Operand(Register::Al), Operand(Imm8(5)) },
		std::array<Operand, 2>{ Operand(Register::Ah), Operand(Imm8(5)) },
		std::array<Operand, 2>{ Operand(Register::Al), Operand(Register::Ah) },
		std::array<Operand, 2>{ Operand(Register::Ah), Operand(Register::Bh) },
		std::array<Operand, 2>{ Operand(Register::Bl), Operand(Register::Cl) },
		std::array<Operand, 2>{ Operand(Register::Sil), Operand(Register::Al) },
		std::array<Operand, 2>{ Operand(Register::Ax), Operand(Imm8(10)) },
		std::array<Operand, 2>{ Operand(Register::Bx), Operand(Imm8(4)) },
		std::array<Operand, 2>{ Operand(Register::Ax), Operand(Register::Bx) },
		std::array<Operand, 2>{ Operand(Register::Si), Operand(Register::Ax) },
		std::array<Operand, 2>{ Operand(Register::Di), Operand(Register::Bx) },
		std::array<Operand, 2>{ Operand(Register::Eax), Operand(Imm8(10)) },
		std::array<Operand, 2>{ Operand(Register::Ebx), Operand(Imm8(4)) },
		std::array<Operand, 2>{ Operand(Register::Eax), Operand(Register::Ebx) },
		std::array<Operand, 2>{ Operand(Register::Esi), Operand(Register::Eax) },
		std::array<Operand, 2>{ Operand(Register::Edi), Operand(Register::Ebx) },
		std::array<Operand, 2>{ Operand(Register::Rax), Operand(Imm8(10)) },
		std::array<Operand, 2>{ Operand(Register::Rbx), Operand(Imm8(4)) },
		std::array<Operand, 2>{ Operand(Register::Rax), Operand(Register::Rbx) },
		std::array<Operand, 2>{ Operand(Register::Rsi), Operand(Register::Rax) },
		std::array<Operand, 2>{ Operand(Register::Rdi), Operand(Register::Rbx) },
		std::array<Operand, 2>{ Operand(Register::Rsp), Operand(Register::Rsp) }
	};

	assert(CorrectMachineCode.size() == Operands.size());

	std::size_t passed = 0, failed = 0;
	
	for(std::size_t i = 0; i < Operands.size(); ++i)
	{
		const auto& ops = Operands[i];
		const auto& mach = CorrectMachineCode[i];
		MachineStream<TargetArchitecture::X86_64> stream = {};
		const auto result = Encode<TargetArchitecture::X86_64>(stream.Stream(), Instruction::Adc, ops);
		const auto ok = stream == mach;
		const auto isFailed = mach.size() != stream.Size() || !ok;
		if (isFailed)
		{
			std::cout << "test " << i << ": " << ops[0] << ", " << ops[1] << " -> " << result;
			std::cout << " -> " << " Correct: " << mach.size() << " == Stream: " << stream.Size() << " -> " << std::boolalpha << (mach.size() == stream.Size());
			std::cout << " -> " << std::boolalpha << ok << " -> Correct ";
			for (const char8_t byte : mach)
			{
				std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<std::uint16_t>(byte) << ' ';
			}
			std::cout << " -> Stream: " << stream;
		}
		if (isFailed) [[unlikely]]
		{
			++failed;
		}
		else
		{
			++passed;
		}
	}

	std::cout << "Tests passed: " << passed << "\nTests failed: " << failed << std::endl;
	
	return 0;
}