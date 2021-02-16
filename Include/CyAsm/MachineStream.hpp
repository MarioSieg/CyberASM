#pragma once

#include <filesystem>
#include <execution>
#include <optional>
#include <string>
#include <fstream>
#include <vector>
#include <span>
#include <bitset>

#include "ByteChunk.hpp"
#include "MachineLanguage.hpp"

namespace CyberAsm
{
	/// <summary>
	/// Represents machine code.
	/// It uses std::uint8_t as byte type (because a stream byte can be an ASCII character or a value)
	/// The stream can also be loaded and saved to a binary file.
	/// Dumping the contents to an fstream, std::stringstream or std::cout is easily possible.
	/// </summary>
	template <TargetArchitecture Arch = TargetArchitecture::X86_64>
	class [[nodiscard]] MachineStream final
	{
	public:
		using StreamBuffer = std::vector<std::uint8_t>;
		using Iterator = StreamBuffer::iterator;
		using ConstIterator = StreamBuffer::const_iterator;
		using ReverseIterator = StreamBuffer::reverse_iterator;
		using ConstReverseIterator = StreamBuffer::const_reverse_iterator;
		
		MachineStream() noexcept;
		explicit MachineStream(StreamBuffer&& vector) noexcept;
		explicit MachineStream(const std::vector<std::byte>& vector);
		explicit MachineStream(const std::uint8_t* memory, std::size_t size);
		explicit MachineStream(const std::byte* memory, std::size_t size);
		explicit MachineStream(std::size_t capacity);
		MachineStream(const MachineStream&) = default;
		MachineStream(MachineStream&&) noexcept = default;
		auto operator=(const MachineStream&) -> MachineStream& = default;
		auto operator=(MachineStream&&) noexcept -> MachineStream& = default;
		~MachineStream() = default;

		template <typename... Ts> requires std::is_trivial_v<Ts...>
		auto Insert(Ts&&... value) -> StreamBuffer&;
		auto Insert(ConstIterator begin, ConstIterator end) ->StreamBuffer&;
		auto Insert(const void* mem, std::size_t size) ->StreamBuffer&;

		[[nodiscard]] auto begin() const noexcept -> ConstIterator;
		[[nodiscard]] auto end() const noexcept -> ConstIterator;
		[[nodiscard]] auto begin() noexcept -> Iterator;
		[[nodiscard]] auto end() noexcept -> Iterator;
		[[nodiscard]] auto rbegin() const noexcept -> ConstReverseIterator;
		[[nodiscard]] auto rend() const noexcept -> ConstReverseIterator;
		[[nodiscard]] auto rbegin() noexcept -> ReverseIterator;
		[[nodiscard]] auto rend() noexcept -> ReverseIterator;

		auto operator <<(std::byte value) -> MachineStream&;
		auto operator <<(std::uint8_t value) -> MachineStream&;
		auto operator <<(std::int8_t value) -> MachineStream&;
		auto operator <<(std::uint16_t value) -> MachineStream&;
		auto operator <<(std::int16_t value) -> MachineStream&;
		auto operator <<(std::uint32_t value) -> MachineStream&;
		auto operator <<(std::int32_t value) -> MachineStream&;
		auto operator <<(std::uint64_t value) -> MachineStream&;
		auto operator <<(std::int64_t value) -> MachineStream&;
		auto operator <<(float value) -> MachineStream&;
		auto operator <<(double value) -> MachineStream&;
		auto operator <<(long double value) -> MachineStream&;
		auto operator <<(char value) -> MachineStream&;
		auto operator <<(wchar_t value) -> MachineStream&;
		auto operator <<(char16_t value) -> MachineStream&;
		auto operator <<(char32_t value) -> MachineStream&;
		auto operator <<(const char* value) -> MachineStream&;
		auto operator <<(const wchar_t* value) -> MachineStream&;
		auto operator <<(const std::uint8_t* value) -> MachineStream&;
		auto operator <<(const char16_t* value) -> MachineStream&;
		auto operator <<(const char32_t* value) -> MachineStream&;
		auto operator <<(const std::string& value) -> MachineStream&;
		auto operator <<(std::string_view value) -> MachineStream&;
		auto operator <<(std::u8string_view value) -> MachineStream&;
		auto operator <<(std::span<std::uint8_t> value) -> MachineStream&;
		auto operator <<(std::span<std::byte> value) -> MachineStream&;
		auto operator <<(const std::vector<std::uint8_t>& value) -> MachineStream&;
		auto operator <<(const std::vector<std::byte>& value) -> MachineStream&;
		auto operator <<(std::initializer_list<std::uint8_t>&& value) -> MachineStream&;
		auto operator <<(std::bitset<8> byteBits) -> MachineStream&;
		auto operator <<(const void* value) -> MachineStream&;
		auto operator <<(const ByteChunk& chunk) -> MachineStream&;
		auto operator [](std::size_t idx) -> std::uint8_t&;
		auto operator [](std::size_t idx) const -> std::uint8_t;
		auto operator *() -> std::uint8_t&;
		auto operator *() const -> std::uint8_t;
		auto operator ()(const std::filesystem::path& file) -> bool;
		auto operator ==(const MachineStream& rhs) const -> bool;
		auto operator !=(const MachineStream& rhs) const -> bool;
		auto operator ==(std::u8string_view rhs) const -> bool;
		auto operator !=(std::u8string_view rhs) const -> bool;

		[[nodiscard]] auto Stream() const & noexcept -> const std::vector<std::uint8_t>&;
		[[nodiscard]] auto Stream() & noexcept -> std::vector<std::uint8_t>&;
		[[nodiscard]] auto Stream() && noexcept -> std::vector<std::uint8_t>&&;
		void Reserve(std::size_t size);
		void Clear();
		void Resize(std::size_t size);
		[[nodiscard]] auto Size() const noexcept -> std::size_t;
		void InsertPadding(std::size_t byteSize, std::uint8_t scalar = 0, std::size_t needle = 0);
		void InsertPadding(std::size_t from, std::size_t to, std::uint8_t scalar);
		[[nodiscard]] auto Contains(std::uint8_t target) const -> bool;
		[[nodiscard]] auto Find(std::uint8_t target) -> std::vector<std::uint8_t>::iterator;
		[[nodiscard]] auto Find(std::uint8_t target) const -> std::vector<std::uint8_t>::const_iterator;
		[[nodiscard]] auto Contains(std::span<std::uint8_t> sequence) const -> bool;
		[[nodiscard]] auto Find(std::span<std::uint8_t> sequence) -> std::vector<std::uint8_t>::iterator;
		[[nodiscard]] auto Find(std::span<std::uint8_t> sequence) const -> std::vector<std::uint8_t>::const_iterator;

		std::size_t DumpTextLineLimit = 8;

	private:
		StreamBuffer stream = {};
	};

	extern auto operator <<(std::ostream& out, const MachineStream<TargetArchitecture::X86_64>& stream) -> std::ostream&;
	extern auto operator <<(std::ofstream& out, Endianness endianness) -> std::ostream&;

	template <TargetArchitecture Arch>
	template <typename... Ts> requires std::is_trivial_v<Ts...>
	inline auto MachineStream<Arch>::Insert(Ts&&... value) -> StreamBuffer&
	{
		static_assert(sizeof value);
		std::array<std::uint8_t, sizeof value> raw = {};
		BytePack<decltype(value), Endianness::Little>(raw, value);
		this->stream.insert(this->stream.end(), raw.begin(), raw.end());
		(this->Insert<Ts...>(value), ...);
		return this->stream;
	}

	template <TargetArchitecture Arch>
	inline MachineStream<Arch>::MachineStream() noexcept = default;

	template <TargetArchitecture Arch>
	MachineStream<Arch>::MachineStream(StreamBuffer&& vector) noexcept : stream(std::move(vector)) { }

	template <TargetArchitecture Arch>
	MachineStream<Arch>::MachineStream(const std::vector<std::byte>& vector)
	{
		this->stream.reserve(vector.size());
		for (const auto value : vector)
		{
			this->stream.push_back(static_cast<std::uint8_t>(value));
		}
	}

	template <TargetArchitecture Arch>
	inline MachineStream<Arch>::MachineStream(const std::uint8_t* const memory, const std::size_t size) : stream(memory, memory + size) {}

	template <TargetArchitecture Arch>
	inline MachineStream<Arch>::MachineStream(const std::byte* const memory, const std::size_t size) : MachineStream(reinterpret_cast<const std::uint8_t*>(memory), size) { }

	template <TargetArchitecture Arch>
	inline MachineStream<Arch>::MachineStream(const std::size_t capacity)
	{
		stream.reserve(capacity);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::byte value) -> MachineStream<Arch>&
	{
		this->stream.push_back(static_cast<std::uint8_t>(value));
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::uint8_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::int8_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::uint16_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::int16_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::uint32_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::int32_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::uint64_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::int64_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const float value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const double value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const long double value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const wchar_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char16_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char32_t value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char* value) -> MachineStream<Arch>&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const wchar_t* value) -> MachineStream<Arch>&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::uint8_t* value) -> MachineStream<Arch>&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char16_t* value) -> MachineStream<Arch>&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const char32_t* value) -> MachineStream<Arch>&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::string& value) -> MachineStream<Arch>&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::string_view value) -> MachineStream<Arch>&
	{
		this->stream.reserve(this->stream.size() + value.size());
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::u8string_view value) -> MachineStream<Arch>&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::span<std::uint8_t> value) -> MachineStream<Arch>&
	{
		this->stream.reserve(this->stream.size() + value.size());
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(std::span<std::byte> value) -> MachineStream<Arch>&
	{
		this->stream.reserve(this->stream.size() + value.size());
		for (const auto v : value)
		{
			this->stream.push_back(static_cast<std::uint8_t>(v));
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::vector<std::uint8_t>& value) -> MachineStream<Arch>&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const std::vector<std::byte>& value) -> MachineStream<Arch>&
	{
		this->stream.reserve(this->stream.size() + value.size());
		for (const auto v : value)
		{
			this->stream.push_back(static_cast<std::uint8_t>(v));
		}
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(std::initializer_list<std::uint8_t>&& value) -> MachineStream<Arch>&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(std::bitset<8> byteBits) -> MachineStream<Arch>&
	{
		this->stream.push_back(static_cast<std::uint8_t>(byteBits.to_ulong()));
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const void* const value) -> MachineStream<Arch>&
	{
		this->Insert(value);
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator<<(const ByteChunk& chunk) -> MachineStream&
	{
		this->stream.insert(this->stream.end(), chunk.begin(), chunk.end());
		return *this;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator[](const std::size_t idx) -> std::uint8_t&
	{
		return this->stream.at(idx);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator[](const std::size_t idx) const -> std::uint8_t
	{
		return this->stream.at(idx);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator*() -> std::uint8_t&
	{
		return this->stream.front();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator*() const -> std::uint8_t
	{
		return this->stream.front();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator()(const std::filesystem::path& file) -> bool
	{
		std::ofstream fstream(file, std::ios::out | std::ios::binary);
		if (!fstream) [[unlikely]]
		{
			return false;
		}
		fstream.write(reinterpret_cast<const char*>(this->stream.data()), this->stream.size());
		return true;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator==(const MachineStream& rhs) const -> bool
	{
		return this->stream == rhs.stream;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator!=(const MachineStream& rhs) const -> bool
	{
		return !(*this == rhs);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator==(const std::u8string_view rhs) const -> bool
	{
		return this->stream.size() != rhs.size() ? false : std::equal(this->stream.begin(), this->stream.end(), rhs.begin());
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::operator!=(const std::u8string_view rhs) const -> bool
	{
		return !(*this == rhs);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Stream() const & noexcept -> const std::vector<std::uint8_t>&
	{
		return this->stream;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Stream() & noexcept -> std::vector<std::uint8_t>&
	{
		return this->stream;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Stream() && noexcept -> std::vector<std::uint8_t>&&
	{
		return std::move(this->stream);
	}

	template <TargetArchitecture Arch>
	inline void MachineStream<Arch>::Reserve(const std::size_t size)
	{
		this->stream.reserve(size);
	}

	template <TargetArchitecture Arch>
	inline void MachineStream<Arch>::Clear()
	{
		this->stream.clear();
	}

	template <TargetArchitecture Arch>
	inline void MachineStream<Arch>::Resize(const std::size_t size)
	{
		this->stream.resize(size);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Size() const noexcept -> std::size_t
	{
		return this->stream.size();
	}

	template <TargetArchitecture Arch>
	inline void MachineStream<Arch>::InsertPadding(const std::size_t byteSize, const std::uint8_t scalar, const std::size_t needle)
	{
		this->stream.resize(this->stream.size() + byteSize);
		std::fill_n(this->stream.end() - byteSize, byteSize, scalar);
	}

	template <TargetArchitecture Arch>
	inline void MachineStream<Arch>::InsertPadding(const std::size_t from, const std::size_t to, const std::uint8_t scalar)
	{
		for (auto i = from; i < to; ++i)
		{
			(*this)[i] = scalar;
		}
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Insert(const std::vector<std::uint8_t>::const_iterator begin, const std::vector<std::uint8_t>::const_iterator end) -> StreamBuffer&
	{
		this->stream.insert(this->stream.end(), begin, end);
		return this->stream;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::begin() const noexcept -> ConstIterator
	{
		return this->stream.begin();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::end() const noexcept -> ConstIterator
	{
		return this->stream.end();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::begin() noexcept -> Iterator
	{
		return this->stream.begin();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::end() noexcept -> Iterator
	{
		return this->stream.end();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::rbegin() const noexcept -> ConstReverseIterator
	{
		return this->stream.rbegin();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::rend() const noexcept -> ConstReverseIterator
	{
		return this->stream.rend();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::rbegin() noexcept ->ReverseIterator
	{
		return this->stream.rbegin();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::rend() noexcept -> ReverseIterator
	{
		return this->stream.rend();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Insert(const void* const mem, const std::size_t size) -> StreamBuffer&
	{
		const auto* byte = static_cast<const std::uint8_t*>(mem);
		const auto* const end = static_cast<const std::uint8_t*>(mem) + size - 1;
		while (byte != end)
		{
			*this << *byte++;
		}
		return this->stream;
	}

	inline auto operator <<(std::ostream& out, const MachineStream<TargetArchitecture::X86_64>& stream) -> std::ostream&
	{
		auto printAscii = [&](const std::size_t i, const std::size_t count)
		{
			out << " | ";
			for (std::size_t j = 0; j < count; ++j)
			{
				const auto val = stream[i - (count - 1 - j)];
				out << static_cast<char>(std::isprint(val) ? val : u8'.');
			}
			out << '\n';
		};

		const auto hexLimit = stream.DumpTextLineLimit;

		for (std::size_t i = 0; i < stream.Size(); ++i)
		{
			out << std::setw(2) << std::setfill('0') << std::right << std::hex << std::uppercase;
			const std::uint8_t value = stream[i];
			if (value == 0) [[unlikely]]
			{
				out << "00 ";
			}
			else
			{
				out << +value << ' ';
			}
			if ((i + 1) % hexLimit == 0) [[unlikely]]
			{
				printAscii(i, hexLimit);
			}
		}
		out << std::dec << std::endl;
		return out;
	}

	inline auto operator <<(std::ofstream& out, const Endianness endianness) -> std::ostream&
	{
		out << (endianness == Endianness::Big ? "BigEndian" : "LittleEndian");
		return out;
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Contains(const std::uint8_t target) const -> bool
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target) != this->stream.end();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Find(const std::uint8_t target) -> std::vector<std::uint8_t>::iterator
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Find(const std::uint8_t target) const -> std::vector<std::uint8_t>::const_iterator
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target);
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Contains(const std::span<std::uint8_t> sequence) const -> bool
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end()) != this->stream.end();
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Find(const std::span<std::uint8_t> sequence) -> std::vector<std::uint8_t>::iterator
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end());
	}

	template <TargetArchitecture Arch>
	inline auto MachineStream<Arch>::Find(const std::span<std::uint8_t> sequence) const -> std::vector<std::uint8_t>::const_iterator
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end());
	}
}
