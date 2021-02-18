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
		[[nodiscard]] constexpr auto ChunkBuffer() const noexcept -> const Buffer&;
		constexpr void Clear() noexcept;
		constexpr void Fill(std::uint8_t value) noexcept;

		constexpr auto operator <<(std::uint8_t value) noexcept -> ByteChunk&;
		constexpr auto operator <<(std::byte value) noexcept -> ByteChunk&;
		constexpr auto operator <<(char8_t value) noexcept -> ByteChunk&;
		[[nodiscard]] constexpr auto operator [](std::size_t idx) -> std::uint8_t&;
		[[nodiscard]] constexpr auto operator [](std::size_t idx) const -> std::uint8_t;

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
		Buffer chunkBuffer = {};
	};

	constexpr ByteChunk::ByteChunk(const Buffer& buffer) noexcept : chunkBuffer(buffer) { }

	inline ByteChunk::ByteChunk(const std::uint8_t (&buffer)[MaxByteChunkSize]) noexcept
	{
		std::ranges::copy(buffer, this->chunkBuffer.begin());
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
		this->chunkBuffer.at(this->size++) = value;
		return *this;
	}

	constexpr auto ByteChunk::Pop() -> std::uint8_t
	{
		return this->chunkBuffer.at(this->size--);
	}

	constexpr auto ByteChunk::Data() noexcept -> std::uint8_t*
	{
		return this->chunkBuffer.data();
	}

	constexpr auto ByteChunk::Data() const noexcept -> const std::uint8_t*
	{
		return this->chunkBuffer.data();
	}

	constexpr auto ByteChunk::ChunkBuffer() const noexcept -> const Buffer&
	{
		return this->chunkBuffer;
	}

	constexpr void ByteChunk::Clear() noexcept
	{
		this->chunkBuffer.fill(0);
	}

	constexpr void ByteChunk::Fill(const std::uint8_t value) noexcept
	{
		this->chunkBuffer.fill(value);
	}

	constexpr auto ByteChunk::operator<<(const std::uint8_t value) noexcept -> ByteChunk&
	{
		return this->PushBack(value);
	}

	constexpr auto ByteChunk::operator<<(const std::byte value) noexcept -> ByteChunk&
	{
		return this->PushBack(static_cast<std::uint8_t>(value));
	}

	constexpr auto ByteChunk::operator<<(const char8_t value) noexcept -> ByteChunk&
	{
		return this->PushBack(value);
	}

	constexpr auto ByteChunk::operator[](const std::size_t idx) -> std::uint8_t&
	{
		return this->chunkBuffer.at(idx);
	}

	constexpr auto ByteChunk::operator[](const std::size_t idx) const -> std::uint8_t
	{
		return this->chunkBuffer.at(idx);
	}

	constexpr auto ByteChunk::begin() const noexcept -> ConstIterator
	{
		return this->chunkBuffer.begin();
	}

	constexpr auto ByteChunk::end() const noexcept -> ConstIterator
	{
		return this->chunkBuffer.begin() + static_cast<ptrdiff_t>(size);
	}

	constexpr auto ByteChunk::begin() noexcept -> Iterator
	{
		return this->chunkBuffer.begin();
	}

	constexpr auto ByteChunk::end() noexcept -> Iterator
	{
		return this->chunkBuffer.begin() + static_cast<ptrdiff_t>(size);
	}

	constexpr auto ByteChunk::rbegin() const noexcept -> ConstReverseIterator
	{
		return this->chunkBuffer.rbegin();
	}

	constexpr auto ByteChunk::rend() const noexcept -> ConstReverseIterator
	{
		return this->chunkBuffer.rbegin() + static_cast<ptrdiff_t>(size);
	}

	constexpr auto ByteChunk::rbegin() noexcept -> ReverseIterator
	{
		return this->chunkBuffer.rbegin();
	}

	constexpr auto ByteChunk::rend() noexcept -> ReverseIterator
	{
		return this->chunkBuffer.rbegin() + static_cast<std::ptrdiff_t>(size);
	}

	inline auto operator <<(std::ostream& out, const ByteChunk& chunk) -> std::ostream&
	{
		out << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
		for (const auto byte : chunk)
		{
			out << static_cast<std::uint16_t>(byte) << ' ';
		}
		return out;
	}
}
