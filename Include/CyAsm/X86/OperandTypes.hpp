#pragma once

#include <type_traits>
#include <cstdint>

namespace CyberAsm
{
	template <typename T>
	concept ValidOperand = requires
	{
		std::is_trivial_v<T>;
		std::is_integral_v<T>;
		sizeof(T) <= 4;
	};

	template <typename T> requires ValidOperand<T>
	struct Imm final
	{
		explicit constexpr Imm(T value) noexcept;
		constexpr Imm(const Imm&) noexcept = default;
		constexpr Imm(Imm&&) noexcept = default;
		constexpr auto operator =(const Imm&) noexcept -> Imm& = default;
		constexpr auto operator =(Imm&&) noexcept -> Imm& = default;
		~Imm() = default;

		T Value;
	};

	template <typename T> requires ValidOperand<T>
	constexpr Imm<T>::Imm(const T value) noexcept : Value(value) { }

	using Imm8 = Imm<std::uint8_t>;
	using Imm16 = Imm<std::uint16_t>;
	using Imm32 = Imm<std::uint32_t>;
}
