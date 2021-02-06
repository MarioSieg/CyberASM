#pragma once

#include <type_traits>
#include <cstdint>

namespace CyberAsm
{
	template <typename T>
	concept ValidOperand = requires
	{
		std::is_trivial_v<T>;
		sizeof(T) <= 8;
	};

	template <typename T> requires ValidOperand<T>
	struct Imm final
	{
		constexpr Imm(const T value) noexcept;
		
		T Value;
	};

	template <typename T> requires ValidOperand<T>
	constexpr Imm<T>::Imm(const T value) noexcept : Value(value) { }

	using Imm8 = Imm<std::uint8_t>;
	using Imm16 = Imm<std::uint16_t>;
	using Imm32 = Imm<std::uint32_t>;
	using Imm64 = Imm<std::uint64_t>;
}
