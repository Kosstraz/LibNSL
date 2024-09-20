/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MULTITHREADING_INL
#define NSL_MULTITHREADING_INL

# include "../MultiThreading.hpp"

template <typename TRet>
TRet	MultiThreading::GetOne(const String& threadToWait) noexcept
{
	return (MultiThreading::threads.at(threadToWait).Get<TRet>());
}

template <typename TRet, typename ... TArgs>
void	MultiThreading::Create(const String& threadName, TRet (*fun)(TArgs...), TArgs...args) noexcept
{
	MultiThreading::threads.insert(std::make_pair<const String&, Thread>(threadName, Thread(fun, args...)));
}

template <typename TRet>
void	MultiThreading::Create(const String& threadName, TRet (*fun)()) noexcept
{
	MultiThreading::threads.insert(std::make_pair<const String&, Thread>(threadName, Thread(fun)));
}

#endif
