#pragma once

#include <variant>
#include <cstdint>

#include "X86/Registers.hpp"

namespace CyberAsm
{
	union Imm8
	{
		std::uint8_t U;
		std::int8_t I;
	};

	union Imm16
	{
		std::uint16_t U;
		std::int16_t I;
	};

	/// <summary>
	/// Represents an operand for an instruction.
	/// </summary>
	class Operand final
	{
		friend auto operator <<(std::ostream& out, const Operand& stream) -> std::ostream&;
	public:
		// @formatter:off
		/// <summary>
		/// Type safe union which contains each possible immediate value.
		/// </summary>
		using Union = std::variant
		<
			Imm8,
			Imm16,
			X86::Register
		>;
		// @formatter:on

		/// <summary>
		/// Create empty instance.
		/// </summary>
		constexpr Operand() = default;

		/// <summary>
		/// Create from data.
		/// </summary>
		/// <param name="data">The variant with data.</param>
		constexpr Operand(const Union& data) noexcept;

		/// <summary>
		/// Create with register as data.
		/// </summary>
		/// <param name="reg">The register.</param>
		constexpr Operand(X86::Register reg) noexcept;

		/// <summary>
		/// Create with 8-bit immediate value as data.
		/// </summary>
		/// <param name="imm">The immediate value.</param>
		constexpr Operand(Imm8 imm) noexcept;

		/// <summary>
		/// Create with 16-bit immediate value as data.
		/// </summary>
		/// <param name="imm">The immediate value.</param>
		constexpr Operand(Imm16 imm) noexcept;

		/// <summary>
		/// Copy constructor.
		/// </summary>
		constexpr Operand(const Operand&) noexcept = default;

		/// <summary>
		/// Move constructor.
		/// </summary>
		constexpr Operand(Operand&&) noexcept = default;

		/// <summary>
		/// Copy assignment operator.
		/// </summary>
		auto operator=(const Operand&) noexcept -> Operand& = default;

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		auto operator=(Operand&&) noexcept -> Operand& = default;

		/// <summary>
		/// Destructor.
		/// </summary>
		~Operand() = default;

		/// <summary>
		/// Get data.
		/// </summary>
		/// <returns>The variant containing the data.</returns>
		[[nodiscard]]
		constexpr auto Data() const noexcept -> const Union&;

		/// <summary>
		/// Get data.
		/// </summary>
		/// <returns>The variant containing the data.</returns>
		[[nodiscard]]
		constexpr auto Data() noexcept -> Union&;

		/// <summary>
		/// Implicit conversion operand to union data.
		/// </summary>
		constexpr operator Union&() noexcept;

		/// <summary>
		/// Implicit conversion operand to union data.
		/// </summary>
		constexpr operator const Union&() const noexcept;

		/// <summary>
		/// Type checks.
		/// </summary>
		/// <returns>True if an immediate value is stored.</returns>
		[[nodiscard]]
		constexpr auto IsImmediate() const noexcept -> bool;

		/// <summary>
		/// Type checks.
		/// </summary>
		/// <returns>True if an 8-bit immediate value is stored.</returns>
		[[nodiscard]]
		constexpr auto IsImm8() const noexcept -> bool;

		/// <summary>
		/// Type checks.
		/// </summary>
		/// <returns>True if an 16-bit immediate value is stored.</returns>
		[[nodiscard]]
		constexpr auto IsImm16() const noexcept -> bool;

		/// <summary>
		/// Type checks.
		/// </summary>
		/// <returns>True if a register is stored (x86 or arm).</returns>
		[[nodiscard]]
		constexpr auto IsRegister() const noexcept -> bool;

		/// <summary>
		/// Type checks.
		/// </summary>
		/// <returns>True if a x86 register is stored.</returns>
		[[nodiscard]]
		constexpr auto IsX86Register() const noexcept -> bool;

	private:
		Union data = {};
	};

	extern auto operator <<(std::ostream& out, const Operand& stream) -> std::ostream&;

	constexpr Operand::Operand(const Union& data) noexcept : data(data) {}

	constexpr Operand::Operand(const X86::Register reg) noexcept : data(reg) { }

	constexpr Operand::Operand(const Imm8 imm) noexcept : data(imm) { }

	constexpr Operand::Operand(const Imm16 imm) noexcept : data(imm) { }

	constexpr auto Operand::Data() const noexcept -> const Union&
	{
		return this->data;
	}

	constexpr auto Operand::Data() noexcept -> Union&
	{
		return this->data;
	}

	constexpr Operand::operator Operand::Union&() noexcept
	{
		return this->data;
	}

	constexpr Operand::operator const Operand::Union&() const noexcept
	{
		return this->data;
	}

	constexpr auto Operand::IsImmediate() const noexcept -> bool
	{
		return !this->IsRegister();
	}

	constexpr auto Operand::IsImm8() const noexcept -> bool
	{
		return std::holds_alternative<Imm8>(this->data);
	}

	constexpr auto Operand::IsImm16() const noexcept -> bool
	{
		return std::holds_alternative<Imm16>(this->data);
	}

	constexpr auto Operand::IsRegister() const noexcept -> bool
	{
		return std::holds_alternative<X86::Register>(this->data);
	}

	constexpr auto Operand::IsX86Register() const noexcept -> bool
	{
		return std::holds_alternative<X86::Register>(this->data);
	}
	 
	constexpr auto operator ""_imm8(const unsigned long long int value) noexcept -> Imm8
	{
		return Imm8
		{
			.U = static_cast<std::uint8_t>(value)
		};
	}

	constexpr auto operator ""_imm16(const unsigned long long int value) noexcept -> Imm16
	{
		return Imm16
		{
			.U = static_cast<std::uint16_t>(value)
		};
	}
}
