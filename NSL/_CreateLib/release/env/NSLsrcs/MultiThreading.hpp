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

	template <typename TRet, typename TObject, typename... TArgs>
	static void	Create(const String& threadName, TRet (TObject::*)(TArgs...), TObject* objInstance, TArgs... args) noexcept;
	template <typename TRet, typename... TArgs>
	static void	Create(const String& threadName, TRet (*)(TArgs...), TArgs...args) noexcept;
	template <typename TRet>
	static void	Create(const String& threadName, TRet (*)()) noexcept;
	template <typename TRet>
	static TRet	Get(const String& threadToGet) noexcept;

	using Thread::Wait;
	static void	Wait(const String& threadToWait) noexcept ;

	
	static FORCEINLINE bool	IsAlive(const String& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(const String& threadName) noexcept;

	
	static FORCEINLINE bool	IsAlive(String&& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(String&& threadName) noexcept;

private:
	
	static FORCEINLINE bool	__isExist__(const String& threadName) noexcept;
	
	static FORCEINLINE bool	__isExist__(String&& threadName) noexcept;

private:
	thread_local static std::map<String, Thread>	threads;
};

# include "template/MultiThreading.inl"
#endif
