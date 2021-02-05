#pragma once

#include <fstream>
#include <type_traits>
#include <filesystem>
#include <string>

namespace CyberAsm
{
	template <typename F> requires std::is_invocable_v<F, std::string&&, const std::size_t>
	[[nodiscard]] inline auto ReadTextChunkStreamed(const std::filesystem::path& path, F proc) -> bool
	{
		std::ifstream stream(path);
		if (!stream) [[unlikely]]
		{
			return false;
		}

		std::string tmp = {};
		for (std::size_t i = 1; std::getline(stream, tmp); ++i)
		{
			proc(std::move(tmp), i);
		}

		return true;
	}
}
