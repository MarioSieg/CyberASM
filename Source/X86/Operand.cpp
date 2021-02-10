#include "../../Include/CyAsm/X86/Operand.hpp"
#include "../../Include/CyAsm/MachineStream.hpp"

#include <cassert>

namespace CyberAsm::X86
{
	Operand::Operand(const Imm8 value) noexcept
	{
		this->data.Imm8 = value;
		this->flags = OperandFlags::Imm8;
	}

	Operand::Operand(const Imm16 value) noexcept
	{
		this->data.Imm16 = value;
		this->flags = OperandFlags::Imm16;
	}

	Operand::Operand(const Imm32 value) noexcept
	{
		this->data.Imm32 = value;
		this->flags = OperandFlags::Imm32;
	}

	Operand::Operand(const Register value) noexcept
	{
		this->data.Reg = value;
		if (value == Register::Al) [[unlikely]]
		{
			this->flags = OperandFlags::Reg8Al;
		}
		else if (value == Register::Ax) [[unlikely]]
		{
			this->flags = OperandFlags::Reg16Ax;
		}
		else if (value == Register::Eax) [[unlikely]]
		{
			this->flags = OperandFlags::Reg32Eax;
		}
		else if (value == Register::Rax) [[unlikely]]
		{
			this->flags = OperandFlags::Reg64Rax;
		}
		else
		{
			const auto size = RegisterSizeTable[static_cast<std::size_t>(value)];
			assert(size && size <= 64);
			switch (size)
			{
				case 1:
					this->flags = OperandFlags::Reg8;
					break;
				case 2:
					this->flags = OperandFlags::Reg16;
					break;
				case 4:
					this->flags = OperandFlags::Reg32;
					break;
				case 8:
					this->flags = OperandFlags::Reg64;
					break;
			}
		}
	}

	auto Operand::Data() const noexcept -> const OperandData&
	{
		return this->data;
	}

	auto Operand::Flags() const noexcept -> OperandFlags::Flags
	{
		return this->flags;
	}
}
