#pragma once

#include <cstdint>
#include <type_traits>

namespace CyberAsm::X86
{
	struct FeatureFlags final
	{
		enum Enum : std::uint8_t
		{
			None = 0,
			Mmx = 1 << 0,
			Sse1 = 1 << 1,
			Sse2 = 1 << 2,
			Sse3 = 1 << 3,
			Ssse3 = 1 << 3,
			Sse41 = 1 << 4,
			Sse42 = 1 << 5,
		};

		using Flags = std::underlying_type_t<Enum>;
	};
}
