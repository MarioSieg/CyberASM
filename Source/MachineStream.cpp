#include "../Include/CyAsm/MachineStream.hpp"

#include <fstream>
#include <execution>

namespace CyberAsm
{
	MachineStream::MachineStream(std::vector<char8_t>&& vector) noexcept : stream(std::move(vector)) { }

	MachineStream::MachineStream(const std::vector<std::byte>& vector)
	{
		this->stream.reserve(vector.size());
		for (const auto value : vector)
		{
			this->stream.push_back(static_cast<char8_t>(value));
		}
	}

	MachineStream::MachineStream(const char8_t* const memory, const std::size_t size) : stream(memory, memory + size) { }

	MachineStream::MachineStream(const std::byte* const memory, const std::size_t size) : MachineStream(reinterpret_cast<const char8_t*>(memory), size) { }

	MachineStream::MachineStream(const std::size_t capacity)
	{
		stream.reserve(capacity);
	}

	auto MachineStream::operator<<(const std::byte value) -> MachineStream&
	{
		this->stream.push_back(static_cast<char8_t>(value));
		return *this;
	}

	auto MachineStream::operator<<(const std::uint8_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::int8_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::uint16_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::int16_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::uint32_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::int32_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::uint64_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const std::int64_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const float value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const double value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const long double value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const char value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const wchar_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const char8_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const char16_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const char32_t value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator<<(const char* value) -> MachineStream&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	auto MachineStream::operator<<(const wchar_t* value) -> MachineStream&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	auto MachineStream::operator<<(const char8_t* value) -> MachineStream&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	auto MachineStream::operator<<(const char16_t* value) -> MachineStream&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	auto MachineStream::operator<<(const char32_t* value) -> MachineStream&
	{
		while (*value) [[likely]]
		{
			*this << *value++;
		}
		return *this;
	}

	auto MachineStream::operator<<(const std::string& value) -> MachineStream&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(const std::string_view value) -> MachineStream&
	{
		this->stream.reserve(this->stream.size() + value.size());
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(const std::u8string_view value) -> MachineStream&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(const std::span<char8_t> value) -> MachineStream&
	{
		this->stream.reserve(this->stream.size() + value.size());
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(std::span<std::byte> value) -> MachineStream&
	{
		this->stream.reserve(this->stream.size() + value.size());
		for (const auto value : value)
		{
			this->stream.push_back(static_cast<char8_t>(value));
		}
		return *this;
	}

	auto MachineStream::operator<<(const std::vector<char8_t>& value) -> MachineStream&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(const std::vector<std::byte>& value) -> MachineStream&
	{
		this->stream.reserve(this->stream.size() + value.size());
		for (const auto value : value)
		{
			this->stream.push_back(static_cast<char8_t>(value));
		}
		return *this;
	}

	auto MachineStream::operator<<(std::initializer_list<char8_t>&& value) -> MachineStream&
	{
		this->stream.insert(this->stream.end(), value.begin(), value.end());
		return *this;
	}

	auto MachineStream::operator<<(const void* const value) -> MachineStream&
	{
		this->Insert(value);
		return *this;
	}

	auto MachineStream::operator[](const std::size_t idx) -> char8_t&
	{
		return this->stream.at(idx);
	}

	auto MachineStream::operator[](const std::size_t idx) const -> char8_t
	{
		return this->stream.at(idx);
	}

	auto MachineStream::operator*() -> char8_t&
	{
		return this->stream.front();
	}

	auto MachineStream::operator*() const -> char8_t
	{
		return this->stream.front();
	}

	auto MachineStream::operator()(const std::filesystem::path& file) -> bool
	{
		std::ofstream fstream(file, std::ios::out | std::ios::binary);
		if (!fstream) [[unlikely]]
		{
			return false;
		}
		fstream.write(reinterpret_cast<const char*>(this->stream.data()), this->stream.size());
		return true;
	}

	auto MachineStream::Stream() const & noexcept -> const std::vector<char8_t>&
	{
		return this->stream;
	}

	auto MachineStream::Stream() & noexcept -> std::vector<char8_t>&
	{
		return this->stream;
	}

	auto MachineStream::Stream() && noexcept -> std::vector<char8_t>&&
	{
		return std::move(this->stream);
	}

	auto MachineStream::CurrentEndianness() const noexcept -> Endianness
	{
		return this->endianness;
	}

	auto MachineStream::SwitchEndianness() -> Endianness
	{
		std::ranges::reverse(this->stream);
		return this->endianness = this->endianness == Endianness::Little ? Endianness::Big : Endianness::Little;
	}

	void MachineStream::Reserve(const std::size_t size)
	{
		this->stream.reserve(size);
	}

	void MachineStream::Clear()
	{
		this->stream.clear();
	}

	void MachineStream::Resize(const std::size_t size)
	{
		this->stream.resize(size);
	}

	auto MachineStream::Size() const noexcept -> std::size_t
	{
		return this->stream.size();
	}

	void MachineStream::InsertPadding(const std::size_t byteSize, const char8_t scalar, const std::size_t needle)
	{
		this->stream.resize(this->stream.size() + byteSize);
		std::fill_n(this->stream.end() - byteSize, byteSize, scalar);
	}

	void MachineStream::InsertPadding(const std::size_t from, const std::size_t to, const char8_t scalar)
	{
		for (auto i = from; i < to; ++i)
		{
			(*this)[i] = scalar;
		}
	}

	auto MachineStream::Insert(const std::vector<char8_t>::const_iterator begin, const std::vector<char8_t>::const_iterator end) -> std::vector<char8_t>&
	{
		this->stream.insert(this->stream.end(), begin, end);
		return this->stream;
	}

	auto MachineStream::begin() const noexcept -> std::vector<char8_t>::const_iterator
	{
		return this->stream.begin();
	}

	auto MachineStream::end() const noexcept -> std::vector<char8_t>::const_iterator
	{
		return this->stream.end();
	}

	auto MachineStream::begin() noexcept -> std::vector<char8_t>::iterator
	{
		return this->stream.begin();
	}

	auto MachineStream::end() noexcept -> std::vector<char8_t>::iterator
	{
		return this->stream.end();
	}

	auto MachineStream::rbegin() const noexcept -> std::vector<char8_t>::const_reverse_iterator
	{
		return this->stream.rbegin();
	}

	auto MachineStream::rend() const noexcept -> std::vector<char8_t>::const_reverse_iterator
	{
		return this->stream.rend();
	}

	auto MachineStream::rbegin() noexcept -> std::vector<char8_t>::reverse_iterator
	{
		return this->stream.rbegin();
	}

	auto MachineStream::rend() noexcept -> std::vector<char8_t>::reverse_iterator
	{
		return this->stream.rend();
	}

	auto MachineStream::Insert(const void* const mem, const std::size_t size) -> std::vector<char8_t>&
	{
		const auto* byte = static_cast<const char8_t*>(mem);
		const auto* const end = static_cast<const char8_t*>(mem) + size - 1;
		while (byte != end)
		{
			*this << *byte++;
		}
		return this->stream;
	}

	auto operator <<(std::ostream& out, const MachineStream& stream) -> std::ostream&
	{
		auto printAscii = [&](const std::size_t i, const std::size_t count = MachineStream::DumpTextLineLimit)
		{
			out << " | ";
			for (std::size_t j = 0; j < count; ++j)
			{
				const auto val = stream[i - (count - 1 - j)];
				out << static_cast<char>(std::isprint(val) ? val : u8'.');
			}
			out << '\n';
		};

		const auto hexLimit = MachineStream::DumpTextLineLimit;

		for (std::size_t i = 0; i < stream.Size(); ++i)
		{
			out << std::setw(2) << std::setfill('0') << std::right << std::hex << std::uppercase;
			const char8_t value = stream[i];
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
				printAscii(i);
			}
		}
		out << std::dec << std::endl;
		return out;
	}

	auto operator <<(std::ofstream& out, const Endianness endianness) -> std::ostream&
	{
		out << (endianness == Endianness::Big ? "BigEndian" : "LittleEndian");
		return out;
	}

	auto MachineStream::Contains(const char8_t target) const -> bool
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target) != this->stream.end();
	}

	auto MachineStream::Find(const char8_t target) -> std::vector<char8_t>::iterator
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target);
	}

	auto MachineStream::Find(const char8_t target) const -> std::vector<char8_t>::const_iterator
	{
		return std::find(std::execution::par_unseq, this->stream.begin(), this->stream.end(), target);
	}

	auto MachineStream::Contains(const std::span<char8_t> sequence) const -> bool
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end()) != this->stream.end();
	}

	auto MachineStream::Find(const std::span<char8_t> sequence) -> std::vector<char8_t>::iterator
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end());
	}

	auto MachineStream::Find(const std::span<char8_t> sequence) const -> std::vector<char8_t>::const_iterator
	{
		return std::search(std::execution::par_unseq, this->stream.begin(), this->stream.end(), sequence.begin(), sequence.end());
	}
}
