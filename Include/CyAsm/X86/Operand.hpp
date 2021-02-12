#pragma once

#include <cassert>

#include "OperandFlags.hpp"
#include "OperandTypes.hpp"
#include "Registers.hpp"

namespace CyberAsm
{
	class MachineStream;

	namespace X86
	{
		union OperandData
		{
			Imm8 Imm8;
			Imm16 Imm16;
			Imm32 Imm32;
			Register Register;
		};

		class [[nodiscard]] Operand final
		{
		public:
			explicit constexpr Operand(Imm8 value) noexcept;
			explicit constexpr Operand(Imm16 value) noexcept;
			explicit constexpr Operand(Imm32 value) noexcept;
			explicit constexpr Operand(Register value) noexcept;

			[[nodiscard]] constexpr auto Unwrap() const noexcept -> const OperandData&;
			[[nodiscard]] constexpr auto Flags() const noexcept -> OperandFlags::Flags;
			[[nodiscard]] constexpr auto IsRegister() const noexcept -> bool;
			[[nodiscard]] constexpr auto IsImplicitRegister() const noexcept -> bool;
			[[nodiscard]] constexpr auto IsImmediate() const noexcept -> bool;
			[[nodiscard]] constexpr auto IsMemory() const noexcept -> bool;
			[[nodiscard]] constexpr auto OperandByteSize() const noexcept -> FixedSize;

		private:
			OperandData data = {Imm8{0x00}};
			OperandFlags::Flags flags = OperandFlags::None;
		};

		constexpr Operand::Operand(const Imm8 value) noexcept
		{
			this->data.Imm8 = value;
			this->flags = OperandFlags::Imm8;
		}

		constexpr Operand::Operand(const Imm16 value) noexcept
		{
			this->data.Imm16 = value;
			this->flags = OperandFlags::Imm16;
		}

		constexpr Operand::Operand(const Imm32 value) noexcept
		{
			this->data.Imm32 = value;
			this->flags = OperandFlags::Imm32;
		}

		constexpr Operand::Operand(const Register value) noexcept
		{
			this->data.Register = value;
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

		constexpr auto Operand::Unwrap() const noexcept -> const OperandData&
		{
			return this->data;
		}

		constexpr auto Operand::Flags() const noexcept -> OperandFlags::Flags
		{
			return this->flags;
		}

		constexpr auto Operand::IsRegister() const noexcept -> bool
		{
			return OperandFlags::IsRegister(this->flags);
		}

		constexpr auto Operand::IsImplicitRegister() const noexcept -> bool
		{
			return OperandFlags::IsImplicitRegister(this->flags);
		}

		constexpr auto Operand::IsImmediate() const noexcept -> bool
		{
			return OperandFlags::IsImmediate(this->flags);
		}

		constexpr auto Operand::IsMemory() const noexcept -> bool
		{
			return OperandFlags::IsMemory(this->flags);
		}

		constexpr auto Operand::OperandByteSize() const noexcept -> FixedSize
		{
			return OperandFlags::OperandByteSize(this->flags);
		}
	}
}
