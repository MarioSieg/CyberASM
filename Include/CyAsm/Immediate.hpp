#pragma once

#include <cstdint>
#include <array>

namespace CyberAsm
{	
	union Immediate final
	{
		std::uint64_t UValue;
		std::int64_t IValue;
		std::array<std::uint8_t, sizeof(std::uint64_t)> Bytes;

		constexpr Immediate() noexcept = default;
		constexpr explicit Immediate(std::uint64_t value) noexcept;
		constexpr explicit Immediate(const std::array<std::uint8_t, sizeof(std::uint64_t)>& value) noexcept;
		constexpr Immediate(const Immediate& rhs) noexcept;
		constexpr Immediate(Immediate&&) = delete;
		constexpr auto operator =(const Immediate& rhs) noexcept -> Immediate&;
		constexpr auto operator =(Immediate&&) -> Immediate& = delete;
		~Immediate() = default;
	};

	static_assert(sizeof(double) == sizeof(std::uint64_t));
	static_assert(sizeof(Immediate) == 8);

	constexpr Immediate::Immediate(const std::uint64_t value) noexcept : UValue(value)
	{
		
	}

	constexpr Immediate::Immediate(const std::array<std::uint8_t, sizeof(std::uint64_t)>& value) noexcept : Bytes(value)
	{
		
	}

	constexpr Immediate::Immediate(const Immediate& rhs) noexcept : UValue(rhs.UValue)
	{
		
	}

	constexpr auto Immediate::operator=(const Immediate& rhs) noexcept -> Immediate&
	{
		this->UValue = rhs.UValue;
		return *this;
	}
}
