#pragma once

#include "MachineLanguage.hpp"
#include "Operand.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <span>

namespace CyberAsm
{
	/// <summary>
	/// Represents machine code.
	/// It uses char8_t as byte type (because a stream byte can be an ASCII character or a value)
	/// The stream can also be loaded and saved to a binary file.
	/// Dumping to an fstream, stringstream or for example std::cout is easily possible.
	/// </summary>
	class [[nodiscard]] MachineStream
	{
	public:
		friend auto operator <<(std::ostream& out, const MachineStream& stream) -> std::ostream&;

		/// <summary>
		/// The maximum values outputted per line, when sent to an std::ostream.
		/// </summary>
		inline static std::size_t DumpTextLineLimit = 8;

		/// <summary>
		/// Create empty stream.
		/// </summary>
		MachineStream() = default;

		/// <summary>
		/// Create stream from data.
		/// </summary>
		/// <param name="vector">Byte array (char8_t) data to use.</param>
		explicit MachineStream(std::vector<char8_t>&& vector) noexcept;

		/// <summary>
		/// Create stream from data.
		/// </summary>
		/// <param name="vector">Byte array data to use.</param>
		explicit MachineStream(const std::vector<std::byte>& vector);

		/// <summary>
		/// Create stream from data.
		/// </summary>
		/// <param name="memory">The memory pointer.</param>
		/// <param name="size">The size of the memory in bytes.</param>
		explicit MachineStream(const char8_t* memory, std::size_t size);

		/// <summary>
		/// Create stream from data.
		/// </summary>
		/// <param name="memory">The memory pointer.</param>
		/// <param name="size">The size of the memory in bytes.</param>
		explicit MachineStream(const std::byte* memory, std::size_t size);

		/// <summary>
		/// Create stream with initial capacity.
		/// </summary>
		/// <param name="capacity">The new capacity.</param>
		explicit MachineStream(std::size_t capacity);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		MachineStream(const MachineStream&) = default;

		/// <summary>
		/// Move constructor.
		/// </summary>
		MachineStream(MachineStream&&) noexcept = default;

		/// <summary>
		/// Copy assignment operator.
		/// </summary>
		auto operator=(const MachineStream&) -> MachineStream& = default;

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		auto operator=(MachineStream&&) -> MachineStream& = default;

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~MachineStream() = default;

		/// <summary>
		/// Converts T to a byte array and stores it in the stream.
		/// T must be a trivial type!
		/// </summary>
		/// <typeparam name="T">The trivial type to convert.</typeparam>
		/// <param name="value">The instance of T.</param>
		/// <returns>A reference to the internal stream.</returns>
		template <typename T> requires std::is_trivial_v<T>
		auto Insert(T value) -> std::vector<char8_t>&;

		/// <summary>
		/// Insert a range of values between two iterators.
		/// </summary>
		/// <param name="begin">The begin iterator.</param>
		/// <param name="end">The end iterator.</param>
		/// <returns>A reference to the internal stream.</returns>
		auto Insert(std::vector<char8_t>::const_iterator begin, std::vector<char8_t>::const_iterator end) -> std::vector<char8_t>&;

		/// <summary>
		/// Insert a raw memory block.
		/// </summary>
		/// <param name="mem">The memory block.</param>
		/// <param name="size">The size of the block in bytes.</param>
		/// <returns>A reference to the internal stream.</returns>
		auto Insert(const void* mem, std::size_t size) -> std::vector<char8_t>&;

		/// <summary>
		/// Iterator.
		/// </summary>
		[[nodiscard]] auto begin() const noexcept -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		[[nodiscard]] auto end() const noexcept -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		auto begin() noexcept -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		auto end() noexcept -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		[[nodiscard]] auto rbegin() const noexcept -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		[[nodiscard]] auto rend() const noexcept -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		auto rbegin() noexcept -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Iterator.
		/// </summary>
		auto rend() noexcept -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Store single byte.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::byte x) -> MachineStream&;

		/// <summary>
		/// Store single byte.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::uint8_t x) -> MachineStream&;

		/// <summary>
		/// Store single byte.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::int8_t x) -> MachineStream&;

		/// <summary>
		/// Store single short.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::uint16_t x) -> MachineStream&;

		/// <summary>
		/// Store single short.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::int16_t x) -> MachineStream&;

		/// <summary>
		/// Store single int.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::uint32_t x) -> MachineStream&;

		/// <summary>
		/// Store single int.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::int32_t x) -> MachineStream&;

		/// <summary>
		/// Store single long.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::uint64_t x) -> MachineStream&;

		/// <summary>
		/// Store single long.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::int64_t x) -> MachineStream&;

		/// <summary>
		/// Store single float.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(float x) -> MachineStream&;

		/// <summary>
		/// Store single double.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(double x) -> MachineStream&;

		/// <summary>
		/// Store single char.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(char x) -> MachineStream&;

		/// <summary>
		/// Store single wide char.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(wchar_t x) -> MachineStream&;

		/// <summary>
		/// Store single unsigned 8-bit char.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(char8_t x) -> MachineStream&;

		/// <summary>
		/// Store single unsigned 16-bit char.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(char16_t x) -> MachineStream&;

		/// <summary>
		/// Store single unsigned 32-bit char.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(char32_t x) -> MachineStream&;

		/// <summary>
		/// Store C string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const char* x) -> MachineStream&;

		/// <summary>
		/// Store C wide string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const wchar_t* x) -> MachineStream&;

		/// <summary>
		/// Store C 8-bit unsigned string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const char8_t* x) -> MachineStream&;

		/// <summary>
		/// Store C 16-bit unsigned string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const char16_t* x) -> MachineStream&;

		/// <summary>
		/// Store C 32-bit unsigned string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const char32_t* x) -> MachineStream&;

		/// <summary>
		/// Store string without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const std::string& x) -> MachineStream&;

		/// <summary>
		/// Store string view without null terminator.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::string_view x) -> MachineStream&;

		/// <summary>
		/// Store machine code view.
		/// Does not reserve, only use for small machine code snippets.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::u8string_view x) -> MachineStream&;

		/// <summary>
		/// Store byte span.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::span<char8_t> x) -> MachineStream&;

		/// <summary>
		/// Store byte span.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::span<std::byte> x) -> MachineStream&;

		/// <summary>
		/// Store byte array.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const std::vector<char8_t>& x) -> MachineStream&;

		/// <summary>
		/// Store byte array.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const std::vector<std::byte>& x) -> MachineStream&;

		/// <summary>
		/// Store initializer list.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(std::initializer_list<char8_t>&& x) -> MachineStream&;

		/// <summary>
		/// Stores a fictitious pointer.
		/// ! Does not store the memory, just the pointer value itself!
		/// Can not use std::uintptr_t because it's just an alias.
		/// </summary>
		/// <returns>The instance itself.</returns>
		auto operator <<(const void* x) -> MachineStream&;

		/// <summary>
		/// Subscript.
		/// </summary>
		/// <param name="idx">Index value.</param>
		/// <returns>Element at index.</returns>
		auto operator [](std::size_t idx) -> char8_t&;


		/// <summary>
		/// Subscript.
		/// </summary>
		/// <param name="idx">Index value.</param>
		/// <returns>Element at index.</returns>
		auto operator [](std::size_t idx) const -> char8_t;

		/// <summary>
		/// Dereference.
		/// </summary>
		/// <returns>The first element in the stream, if any.</returns>
		auto operator *() -> char8_t&;

		/// <summary>
		/// Dereference.
		/// </summary>
		/// <returns>The first element in the stream, if any.</returns>
		auto operator *() const -> char8_t;

		/// <summary>
		/// Saves the whole stream to a binary file.
		/// </summary>
		/// <param name="file">The file path to save to.</param>
		/// <returns>true if succeeded, else false.</returns>
		auto operator ()(const std::filesystem::path& file) -> bool;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>A reference to the internal stream buffer.</returns>
		[[nodiscard]]
		auto Stream() const & noexcept -> const std::vector<char8_t>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>A reference to the internal stream buffer.</returns>
		[[nodiscard]]
		auto Stream() & noexcept -> std::vector<char8_t>&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>A reference to the internal stream buffer.</returns>
		[[nodiscard]]
		auto Stream() && noexcept -> std::vector<char8_t>&&;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The current endianness of the stream.</returns>
		[[nodiscard]]
		auto CurrentEndianness() const noexcept -> Endianness;

		/// <summary>
		/// Switches the current endianness and swaps all bytes accordingly.
		/// </summary>
		/// <returns>The new endianness.</returns>
		auto SwitchEndianness() -> Endianness;

		/// <summary>
		/// Reserves the buffer size.
		/// </summary>
		/// <param name="size">The new size in bytes.</param>
		void Reserve(std::size_t size);

		/// <summary>
		/// Removes all entries from the stream.
		/// Does not modify the capacity.
		/// </summary>
		void Clear();

		/// <summary>
		/// Resizes the stream to the given size.
		/// </summary>
		/// <param name="size">The size the stream should have after resize.</param>
		void Resize(std::size_t size);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>The current size of the stream in bytes and number of entries.</returns>
		[[nodiscard]]
		auto Size() const noexcept -> std::size_t;

		/// <summary>
		/// Inserts padding bytes at the stream end + needle.
		/// </summary>
		/// <param name="byteSize">The amount of bytes to append.</param>
		/// <param name="scalar">The value of each bytes.</param>
		/// <param name="needle">The offset from the current end.</param>
		void InsertPadding(std::size_t byteSize, char8_t scalar = 0, std::size_t needle = 0);

		/// <summary>
		/// Inserts padding bytes between the two indices.
		/// The indices must be in range of the stream size.
		/// </summary>
		/// <param name="from">The start position.</param>
		/// <param name="to">The end position.</param>
		/// <param name="scalar">The value of each byte inserted.</param>
		void InsertPadding(std::size_t from, std::size_t to, char8_t scalar);

		/// <summary>
		/// Searches for the byte in the stream.
		/// </summary>
		/// <param name="target">The byte to search for.</param>
		/// <returns>True if the byte exists, else false.</returns>
		[[nodiscard]]
		auto Contains(char8_t target) const -> bool;

		/// <summary>
		/// Searches for the byte in the stream.
		/// </summary>
		/// <param name="target">The byte to search for.</param>
		/// <returns>The iterator to the byte if found, else the end.</returns>
		[[nodiscard]]
		auto Find(char8_t target) -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Searches for the byte in the stream.
		/// </summary>
		/// <param name="target">The byte to search for.</param>
		/// <returns>The iterator to the byte if found, else the end.</returns>
		[[nodiscard]]
		auto Find(char8_t target) const -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Searches for the sequence in the stream.
		/// </summary>
		/// <param name="sequence">The sequence of bytes to search for.</param>
		/// <returns>The iterator to the byte if found, else the end.</returns>
		[[nodiscard]]
		auto Contains(std::span<char8_t> sequence) const -> bool;

		/// <summary>
		/// Searches for the sequence in the stream.
		/// </summary>
		/// <param name="sequence">The sequence of bytes to search for.</param>
		/// <returns>The iterator to the byte if found, else the end.</returns>
		[[nodiscard]]
		auto Find(std::span<char8_t> sequence) -> std::vector<char8_t>::iterator;

		/// <summary>
		/// Searches for the sequence in the stream.
		/// </summary>
		/// <param name="sequence">The sequence of bytes to search for.</param>
		/// <returns>The iterator to the byte if found, else the end.</returns>
		[[nodiscard]]
		auto Find(std::span<char8_t> sequence) const -> std::vector<char8_t>::const_iterator;

		/// <summary>
		/// Insert x86 assembler in form of an instruction and operand.
		/// </summary>
		/// <param name="instruction"></param>
		/// <param name="ops"></param>
		/// <returns></returns>
		auto Asm(X86::Instruction instruction, const std::initializer_list<Operand>& ops) -> std::span<char8_t>;

	protected:
		std::vector<char8_t> stream = {};
		Endianness endianness = Endianness::Little;
	};

	extern auto operator <<(std::ostream& out, const MachineStream& stream) -> std::ostream&;
	extern auto operator <<(std::ofstream& out, Endianness endianness) -> std::ostream&;

	template <typename T> requires std::is_trivial_v<T>
	inline auto MachineStream::Insert(const T value) -> std::vector<char8_t>&
	{
		static_assert(sizeof(decltype(value)));

		std::array<char8_t, sizeof(decltype(value))> raw = {};
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
