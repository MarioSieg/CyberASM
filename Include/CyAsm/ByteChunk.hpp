#pragma once

#include <cstdint>
#include <array>
#include <algorithm>
#include <iomanip>
#include <ostream>

namespace CyberAsm
{
	/// <summary>
	/// Represents a small, variable sized byte array based on a fixed std::array.
	/// </summary>
	class ByteChunk final
	{
	public:
		static constexpr std::size_t MaxByteChunkSize = 16;

		using Buffer = std::array<std::uint8_t, MaxByteChunkSize>;
		using Iterator = Buffer::iterator;
		using ConstIterator = Buffer::const_iterator;
		using ReverseIterator = Buffer::reverse_iterator;
		using ConstReverseIterator = Buffer::const_reverse_iterator;

		constexpr ByteChunk() noexcept = default;
		explicit constexpr ByteChunk(const Buffer& buffer) noexcept;
		explicit ByteChunk(const std::uint8_t (&buffer)[MaxByteChunkSize]) noexcept;
		constexpr ByteChunk(const ByteChunk&) noexcept = default;
		constexpr ByteChunk(ByteChunk&&) noexcept = default;
		constexpr auto operator =(const ByteChunk&) noexcept -> ByteChunk& = default;
		constexpr auto operator =(ByteChunk&&) noexcept -> ByteChunk& = default;
		~ByteChunk() = default;

		[[nodiscard]] static constexpr auto Capacity() noexcept -> std::size_t;
		[[nodiscard]] constexpr auto Size() const noexcept -> std::size_t;
		constexpr auto PushBack(std::uint8_t value) -> ByteChunk&;
		constexpr auto Pop() -> std::uint8_t;
		[[nodiscard]] constexpr auto Data() noexcept -> std::uint8_t*;
		[[nodiscard]] constexpr auto Data() const noexcept -> const std::uint8_t*;
		[[nodiscard]] constexpr auto ValueBuffer() const noexcept -> const Buffer&;
		constexpr void Clear() noexcept;
		constexpr void Fill(std::uint8_t value) noexcept;

		[[nodiscard]] constexpr auto operator[](std::size_t idx) -> std::uint8_t&;
		[[nodiscard]] constexpr auto operator[](std::size_t idx) const -> std::uint8_t;

		[[nodiscard]] constexpr auto begin() const noexcept -> ConstIterator;
		[[nodiscard]] constexpr auto end() const noexcept -> ConstIterator;
		[[nodiscard]] constexpr auto begin() noexcept -> Iterator;
		[[nodiscard]] constexpr auto end() noexcept -> Iterator;
		[[nodiscard]] constexpr auto rbegin() const noexcept -> ConstReverseIterator;
		[[nodiscard]] constexpr auto rend() const noexcept -> ConstReverseIterator;
		[[nodiscard]] constexpr auto rbegin() noexcept -> ReverseIterator;
		[[nodiscard]] constexpr auto rend() noexcept -> ReverseIterator;

	private:
		std::size_t size = 0;
		Buffer buffer = {};
	};

	constexpr ByteChunk::ByteChunk(const Buffer& buffer) noexcept : buffer(buffer) { }

	inline ByteChunk::ByteChunk(const std::uint8_t (&buffer)[MaxByteChunkSize]) noexcept
	{
		std::ranges::copy(buffer, this->buffer.begin());
	}

	constexpr auto ByteChunk::Capacity() noexcept -> std::size_t
	{
		return MaxByteChunkSize;
	}

	constexpr auto ByteChunk::Size() const noexcept -> std::size_t
	{
		return this->size;
	}

	constexpr auto ByteChunk::PushBack(const std::uint8_t value) -> ByteChunk&
	{
		this->buffer.at(this->size++) = value;
		return *this;
	}

	constexpr auto ByteChunk::Pop() -> std::uint8_t
	{
		return this->buffer.at(this->size--);
	}

	constexpr auto ByteChunk::Data() noexcept -> std::uint8_t*
	{
		return this->buffer.data();
	}

	constexpr auto ByteChunk::Data() const noexcept -> const std::uint8_t*
	{
		return this->buffer.data();
	}

	constexpr auto ByteChunk::ValueBuffer() const noexcept -> const Buffer&
	{
		return this->buffer;
	}

	constexpr void ByteChunk::Clear() noexcept
	{
		this->buffer.fill(0);
	}

	constexpr void ByteChunk::Fill(const std::uint8_t value) noexcept
	{
		this->buffer.fill(value);
	}

	constexpr auto ByteChunk::operator[](const std::size_t idx) -> std::uint8_t&
	{
		return this->buffer.at(idx);
	}

	constexpr auto ByteChunk::operator[](const std::size_t idx) const -> std::uint8_t
	{
		return this->buffer.at(idx);
	}

	constexpr auto ByteChunk::begin() const noexcept -> ConstIterator
	{
		return this->buffer.begin();
	}

	constexpr auto ByteChunk::end() const noexcept -> ConstIterator
	{
		return this->buffer.begin() + size;
	}

	constexpr auto ByteChunk::begin() noexcept -> Iterator
	{
		return this->buffer.begin();
	}

	constexpr auto ByteChunk::end() noexcept -> Iterator
	{
		return this->buffer.begin() + size;
	}

	constexpr auto ByteChunk::rbegin() const noexcept -> ConstReverseIterator
	{
		return this->buffer.rbegin();
	}

	constexpr auto ByteChunk::rend() const noexcept -> ConstReverseIterator
	{
		return this->buffer.rbegin() + size;
	}

	constexpr auto ByteChunk::rbegin() noexcept -> ReverseIterator
	{
		return this->buffer.rbegin();
	}

	constexpr auto ByteChunk::rend() noexcept -> ReverseIterator
	{
		return this->buffer.rbegin() + size;
	}

	inline auto operator <<(std::ostream& out, const ByteChunk& chunk) -> std::ostream&
	{
		out << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
		for (const auto byte : chunk)
		{
			out << byte << ' ';
		}
		return out;
	}
}
