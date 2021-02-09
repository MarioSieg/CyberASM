#pragma once

#include "MachineLanguage.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <span>

namespace CyberAsm
{
	/// <summary>
	/// Represents machine code.
	/// It uses std::uint8_t as byte type (because a stream byte can be an ASCII character or a value)
	/// The stream can also be loaded and saved to a binary file.
	/// Dumping the contents to an fstream, stringstream or std::cout is easily possible.
	/// </summary>
	class [[nodiscard]] MachineStream final
	{
	public:
		friend auto operator <<(std::ostream& out, const MachineStream& stream) -> std::ostream&;
		inline static std::size_t DumpTextLineLimit = 8;

		MachineStream() = default;
		explicit MachineStream(std::vector<std::uint8_t>&& vector) noexcept;
		explicit MachineStream(const std::vector<std::byte>& vector);
		explicit MachineStream(const std::uint8_t* memory, std::size_t size);
		explicit MachineStream(const std::byte* memory, std::size_t size);
		explicit MachineStream(std::size_t capacity);

		MachineStream(const MachineStream&) = default;
		MachineStream(MachineStream&&) noexcept = default;

		auto operator=(const MachineStream&) -> MachineStream& = default;
		auto operator=(MachineStream&&) -> MachineStream& = default;

		virtual ~MachineStream() = default;

		template <typename T> requires std::is_trivial_v<T>
		auto Insert(T value) -> std::vector<std::uint8_t>&;
		auto Insert(std::vector<std::uint8_t>::const_iterator begin, std::vector<std::uint8_t>::const_iterator end) -> std::vector<std::uint8_t>&;
		auto Insert(const void* mem, std::size_t size) -> std::vector<std::uint8_t>&;

		[[nodiscard]] auto begin() const noexcept -> std::vector<std::uint8_t>::const_iterator;
		[[nodiscard]] auto end() const noexcept -> std::vector<std::uint8_t>::const_iterator;
		auto begin() noexcept -> std::vector<std::uint8_t>::iterator;
		auto end() noexcept -> std::vector<std::uint8_t>::iterator;
		[[nodiscard]] auto rbegin() const noexcept -> std::vector<std::uint8_t>::const_reverse_iterator;
		[[nodiscard]] auto rend() const noexcept -> std::vector<std::uint8_t>::const_reverse_iterator;
		auto rbegin() noexcept -> std::vector<std::uint8_t>::reverse_iterator;
		auto rend() noexcept -> std::vector<std::uint8_t>::reverse_iterator;

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
		auto operator <<(const void* value) -> MachineStream&;

		auto operator [](std::size_t idx) -> std::uint8_t&;
		auto operator [](std::size_t idx) const -> std::uint8_t;
		auto operator *() -> std::uint8_t&;
		auto operator *() const -> std::uint8_t;
		auto operator ()(const std::filesystem::path& file) -> bool;

		[[nodiscard]] auto Stream() const & noexcept -> const std::vector<std::uint8_t>&;
		[[nodiscard]] auto Stream() & noexcept -> std::vector<std::uint8_t>&;
		[[nodiscard]] auto Stream() && noexcept -> std::vector<std::uint8_t>&&;

		[[nodiscard]] auto CurrentEndianness() const noexcept -> Endianness;
		[[nodiscard]] auto SwitchEndianness() -> Endianness;

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

	private:
		std::vector<std::uint8_t> stream = {};
		Endianness endianness = Endianness::Little;
	};

	extern auto operator <<(std::ostream& out, const MachineStream& stream) -> std::ostream&;
	extern auto operator <<(std::ofstream& out, Endianness endianness) -> std::ostream&;

	template <typename T> requires std::is_trivial_v<T>
	inline auto MachineStream::Insert(const T value) -> std::vector<std::uint8_t>&
	{
		static_assert(sizeof value);

		std::array<std::uint8_t, sizeof value> raw = {};
		if (this->endianness == Endianness::Little) [[likely]]
		{
			BytePack<decltype(value), Endianness::Little>(raw, value);
		}
		else
		{
			BytePack<decltype(value), Endianness::Big>(raw, value);
		}
		this->stream.insert(this->stream.end(), raw.begin(), raw.end());
		return this->stream;
	}
}
