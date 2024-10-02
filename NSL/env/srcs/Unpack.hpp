/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_UNPACK_HPP
#define NSL_UNPACK_HPP

# include "Memory.hpp"

template <typename TFun, typename ... TPack>
struct	Unpack
{
	Unpack(TFun fun, TPack ...args)
	{
		fun(Memory::Move(args)...);
	}

	template <typename ... TArgs>
	struct	BreakItDown
	{
		BreakItDown(TFun fun, Package<TPack...> pack, TArgs& ...args)
		{
			decltype(pack.value)& newPack = pack.value;
			if constexpr (!newPack.last)
				typename Unpack<TFun, decltype(newPack.rest)>::template BreakItDown<TArgs ..., decltype(newPack.value)>(fun, newPack.rest, args..., newPack.value);
			else
				Unpack<TFun, TArgs..., decltype(newPack.value)>(fun, args..., newPack.value);
		}
	};

	Unpack(TFun fun, Package<TPack...>& pack)
	{
		if constexpr (!pack.last)
			typename Unpack<TFun, decltype(pack.rest)>::template BreakItDown<decltype(pack.value)>(fun, pack.rest, pack.value);
		else
			Unpack<TFun, TPack...>(fun, pack.value);
	}
};

// For non-static method calls
template <typename TFun, typename TObject, typename ... TPack>
struct	NSUnpack
{
	NSUnpack(TFun fun, TObject* instance, TPack ...args)
	{
		(instance->*fun)(Memory::Move(args)...);
		std::cout << "Last\n";
	}

	template <typename ... TArgs>
	struct	BreakItDown
	{
		BreakItDown(TFun fun, TObject* instance, Package<TPack...> pack, TArgs& ...args)
		{
			decltype(pack.value)& newPack = pack.value;
			if constexpr (!newPack.last)
				typename NSUnpack<TFun, TObject, decltype(newPack.rest)>::template BreakItDown<TArgs ..., decltype(newPack.value)>(fun, instance, newPack.rest, args..., newPack.value);
			else
				NSUnpack<TFun, TObject, TArgs..., decltype(newPack.value)>(fun, instance, args..., newPack.value);
		}
	};

	NSUnpack(TFun fun, TObject* instance, Package<TPack...>& pack)
	{
		std::cout << "First\n";
		if constexpr (!pack.last)
			typename NSUnpack<TFun, TObject, decltype(pack.rest)>::template BreakItDown<decltype(pack.value)>(fun, instance, pack.rest, pack.value);
		else
			NSUnpack<TFun, TObject, TPack...>(fun, instance, pack.value);
	}
};

#endif
