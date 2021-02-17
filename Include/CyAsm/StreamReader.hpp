#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <execution>

namespace CyberAsm
{
	inline void ReadFile(std::string& out, const std::filesystem::path& path)
	{
		std::ifstream stream(path);
		if (!stream) [[unlikely]]
		{
			throw std::runtime_error("failed to open file!");
		}
		stream.seekg(0, std::ios::end);
		out.reserve(stream.tellg());
		stream.seekg(0, std::ios::beg);
		out.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(stream));
	}

	inline void SplitLines(const std::string& target, std::vector<std::size_t>& needles)
	{
		for (auto i = target.begin(); (i = std::find_if(i, target.end(), [](const char x)
		{
			return x == '\n';
		})) != target.end(); ++i)
		{
			needles.push_back(*i);
		}
	}
}
