/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_UNPACK_HPP
#define NSL_UNPACK_HPP

# include "Memory.hpp"

template <typename Fun, typename ... TPack>
struct	Unpack
{
	Unpack(Fun fun, TPack ...args)
	{
		fun(Memory::Move(args)...);
	}

	template <typename ... TArgs>
	struct	BreakItDown
	{
		BreakItDown(Fun fun, Package<TPack...> pack, TArgs& ...args)
		{
			decltype(pack.value)& newPack = pack.value;
			if constexpr (!newPack.last)
				typename Unpack<Fun, decltype(newPack.rest)>::template BreakItDown<TArgs ..., decltype(newPack.value)>(fun, newPack.rest, args..., newPack.value);
			else
				Unpack<Fun, TArgs..., decltype(newPack.value)>(fun, args..., newPack.value);
		}
	};

	Unpack(Fun fun, Package<TPack...>& pack)
	{
		if constexpr (!pack.last)
			typename Unpack<Fun, decltype(pack.rest)>::template BreakItDown<decltype(pack.value)>(fun, pack.rest, pack.value);
		else
			Unpack<Fun, TPack...>(fun, pack.value);
	}
};

#endif
