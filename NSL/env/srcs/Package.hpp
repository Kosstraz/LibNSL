/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_PACKAGE_HPP
#define NSL_PACKAGE_HPP

// Package class encapsulates any many args
// Can be unpack with the Unpack/NSUnpack class
template <typename T, typename ... TArgs>
class Package
{
public:
	Package(const T& v, const TArgs&... rest) : value(v), rest(rest...)
	{}

	explicit operator T() const
	{
		return (this->value);
	}

public:
	T					value;
	Package<TArgs...>	rest;
	inline static constexpr bool	last = false;
};

// Package class encapsulates any many args
// Can be unpack with the Unpack/NSUnpack class
template <typename T>
class Package<T>
{
public:
	Package(const T& v) : value(v)
	{}

	explicit operator T() const
	{
		return (this->value);
	}

public:
	T		value;
	inline static constexpr bool	last = true;

};

#endif
