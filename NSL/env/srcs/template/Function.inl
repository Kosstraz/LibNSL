/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_FUNCTION_INL
#define NSL_FUNCTION_INL

# include "../Function.hpp"

template <typename TRet, typename ... TArgs>
Function<TRet, TArgs ...>::Function() noexcept
										: fun(static_cast<FUNTYPE>(nullptr))
{
}

template <typename TRet, typename ... TArgs>
Function<TRet, TArgs ...>::Function(FUNTYPE fun) noexcept : fun(fun)
{
}

template <typename TRet, typename ... TArgs>
Function<TRet, TArgs ...>::FUNTYPE
	Function<TRet, TArgs ...>::Get() const noexcept
{
	return (this->fun);
}

template <typename TRet, typename ... TArgs>
TRet	Function<TRet, TArgs ...>::Play(TArgs ...args) const noexcept
{
	return (this->fun(args ...));
}

template <typename TRet, typename ... TArgs>
void	Function<TRet, TArgs ...>::Replace(FUNTYPE fun) noexcept
{
	this->fun = fun;
}









template <typename TRet>
Function<TRet>::Function() noexcept : fun(static_cast<FUNTYPE>(nullptr))
{
}

template <typename TRet>
Function<TRet>::Function(FUNTYPE fun) noexcept : fun(fun)
{
}

template <typename TRet>
Function<TRet>::FUNTYPE
	Function<TRet>::Get() const noexcept
{
	return (this->fun);
}

template <typename TRet>
TRet	Function<TRet>::Play() const noexcept
{
	return (this->fun());
}

template <typename TRet>
void	Function<TRet>::Replace(FUNTYPE fun) noexcept
{
	this->fun = fun;
}

#endif
