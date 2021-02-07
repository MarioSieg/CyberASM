#pragma once

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
			Imm64 Imm64;
			Register Reg;
		};

		class [[nodiscard]] Operand final
		{
		public:
			Operand(Imm8 value) noexcept;
			Operand(Imm16 value) noexcept;
			Operand(Imm32 value) noexcept;
			Operand(Imm64 value) noexcept;
			Operand(Register value) noexcept;

			[[nodiscard]] auto Data() const noexcept -> const OperandData&;

			[[nodiscard]] auto Flags() const noexcept -> OperandFlags::Flags;

			auto FlushBytes(MachineStream& out) const -> std::size_t;

		private:
			OperandData data = {Imm8{0x00}};
			OperandFlags::Flags flags = OperandFlags::None;
		};
	}
}
