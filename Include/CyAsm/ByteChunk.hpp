#pragma once

#include <cstdint>
#include <array>
#include <algorithm>

namespace CyberAsm
{
	class ByteChunk final
	{
	public:
		static constexpr std::size_t MaxByteChunkSize = 16;
		
		using Buffer = std::array<std::uint8_t, MaxByteChunkSize>;

		constexpr ByteChunk() noexcept = default;
		explicit constexpr ByteChunk(const Buffer& buffer) noexcept;
		explicit ByteChunk(const std::uint8_t (&buffer)[MaxByteChunkSize]) noexcept;
		constexpr ByteChunk(const ByteChunk&) noexcept = default;
		constexpr ByteChunk(ByteChunk&&) noexcept = default;
		constexpr auto operator =(const ByteChunk&) noexcept = default;
		constexpr auto operator =(ByteChunk&&) noexcept = default;
		~ByteChunk() = default;

		[[nodiscard]] static constexpr auto Capacity() noexcept -> std::size_t;
		[[nodiscard]] constexpr auto Size() const noexcept -> std::size_t;
		constexpr auto PushBack(std::uint8_t value) -> ByteChunk&;
		constexpr void Clear() noexcept;
		constexpr void Fill(std::uint8_t value) noexcept;

	private:
		std::size_t size = 0;
		std::array<std::uint8_t, MaxByteChunkSize> buffer = {};
	};

	constexpr ByteChunk::ByteChunk(const Buffer& buffer) noexcept : buffer(buffer)
	{
		
	}

	inline ByteChunk::ByteChunk(const std::uint8_t(&buffer)[MaxByteChunkSize]) noexcept
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
	
	constexpr void ByteChunk::Clear() noexcept
	{
		this->buffer.fill(0);
	}

	constexpr void ByteChunk::Fill(std::uint8_t value) noexcept
	{
		this->buffer.fill(value);
	}
}
