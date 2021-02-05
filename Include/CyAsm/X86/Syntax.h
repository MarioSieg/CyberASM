#pragma once

namespace CyberAsm::X64
{
	constexpr auto RegisterPrefix = '%';
	constexpr auto ImmediatePrefix = '$';
	constexpr auto AbsoluteJumpPrefix = '*';

	constexpr auto Separator = ',';
	constexpr auto Comment = '#';

	constexpr auto HexPrefix = 'x';
	constexpr auto BinPrefix = 'b';
	constexpr auto OctPrefix = 'c';
}
