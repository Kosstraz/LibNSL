/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MEMORY_HPP
#define NSL_MEMORY_HPP

# include "TypesCap.hpp"

namespace Memory
{

template <typename TCast>
FORCEINLINE constexpr RemoveRef<TCast>&&	Move(TCast&& arg) noexcept
{
	return (static_cast<RemoveRef<TCast>&&>(arg));
}

template <typename T>
requires Types::IsNative<T>
inline constexpr void	Swap(T& a, T& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

template <class T>
requires Types::IsObject<T>
inline constexpr void	Swap(T& a, T& b)
{
	T	temp = Memory::Move(a);
	a = Memory::Move(b);
	b = Memory::Move(temp);
}

}

#endif
