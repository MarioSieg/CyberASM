#include "../../Include/CyAsm/X86/Encoder.hpp"

#include "../../Include/CyAsm/MachineStream.hpp"
#include "../../Include/CyAsm/X86/Operand.hpp"

namespace CyberAsm::X86
{
	void Encode(MachineStream& out, const Instruction instruction, std::span<const Operand> operands)
	{
		WriteOperands(out, operands);
	}

	auto WriteOperands(MachineStream& out, const std::span<const Operand> operands) -> std::size_t
	{
		const auto prev = out.Size();

		for (const auto& operand : operands)
		{
			operand.FlushBytes(out);
		}

		return out.Size() - prev;
	}
}
