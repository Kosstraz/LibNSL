/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MULTITHREADING_HPP
#define NSL_MULTITHREADING_HPP

# include "Thread.hpp"
# include "String.hpp"
# include <map>

class MultiThreading final : private Thread
{
public:
	MultiThreading(const MultiThreading&) 	= delete;
	MultiThreading(MultiThreading&&) 		= delete;
	MultiThreading()						= delete;
	virtual ~MultiThreading();

	template <typename TRet, typename ... TArgs>
	static void	Create(const String& threadName, TRet (*)(TArgs...), TArgs...args) noexcept;
	template <typename TRet>
	static void	Create(const String& threadName, TRet (*)()) noexcept;
	template <typename TRet>
	static TRet	GetOne(const String& threadToGet) noexcept;

	static void	WaitOne(const String& threadToWait) noexcept;

private:
	thread_local static std::map<String, Thread>	threads;
};

# include "template/MultiThreading.inl"
#endif
