#pragma once

namespace CyberAsm
{
	template <typename... T>
	struct Overload : T...
	{
		using T::operator()...;
	};

	template <typename... T>
	Overload(T ...) -> Overload<T...>;
}
