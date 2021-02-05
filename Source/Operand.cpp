#include "../Include/CyAsm/Operand.hpp"
#include "../Include/CyAsm/Utils.hpp"

#include <iomanip>

namespace CyberAsm
{
	auto operator <<(std::ostream& out, const Operand& stream) -> std::ostream&
	{
		std::visit(Overload
		           {
			           [&out](const Imm8 x)
			           {
				           out << "imm8 " << +x.U;
			           },
			           [&out](const Imm16 x)
			           {
				           out << "imm16 " << x.U;
			           },
			           [&out](const X86::Register x)
			           {
				           const auto i = static_cast<std::size_t>(x);
				           out << "reg" << X86::RegisterSizeTable[i] * 8 << ' ' << X86::RegisterMnemonicTable[i] << ' ' << +X86::RegisterIdTable[i];
			           },
		           }, stream.data);
		return out;
	}
}
