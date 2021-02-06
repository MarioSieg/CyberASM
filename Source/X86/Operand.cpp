#include "../../Include/CyAsm/X86/Operand.hpp"
#include "../../Include/CyAsm/MachineStream.hpp"

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

	Operand::Operand(const Imm64 value) noexcept
	{
		this->data.Imm64 = value;
		this->flags = OperandFlags::Imm64;
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

	auto Operand::FlushBytes(MachineStream& out) const -> std::size_t
	{
		if (OperandFlags::IsExplicitRegister(this->flags)) [[unlikely]]
		{
			return 0;
		}

		const auto prev = out.Size();

		if (OperandFlags::IsRegister(this->flags)) [[likely]]
		{
			out << RegisterIdTable[static_cast<std::size_t>(this->data.Reg)];
		}
		else
		{
			switch (this->flags)
			{
				case OperandFlags::Imm8:
					out << this->data.Imm8.Value;
					break;
				case OperandFlags::Imm16:
					out << this->data.Imm16.Value;
					break;
				case OperandFlags::Imm32:
					out << this->data.Imm32.Value;
					break;
				case OperandFlags::Imm64:
					out << this->data.Imm64.Value;
					break;
			}
		}

		return out.Size() - prev;
	}
}
