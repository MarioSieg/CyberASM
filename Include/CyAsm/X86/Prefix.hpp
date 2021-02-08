#pragma once

namespace CyberAsm::X86
{
	enum class PrefixType : char8_t
	{
		None = 0,
		RexW64 = u8'\x48',
		OperandOverride32 = u8'\x66',
		AddressOverride = u8'\x67',
		Lock = u8'\xF0'
	};
}
