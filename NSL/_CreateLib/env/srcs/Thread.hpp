/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_THREAD_HPP
#define NSL_THREAD_HPP

# include "../platform.h"

# include "Function.hpp"
# include "Package.hpp"
# include "Unpack.hpp"
# include "String.hpp"
# include "Mutex.hpp"
# include <pthread.h>
# include <map>

extern pthread_t	Thread_MainThreadID;

class Thread
{
private:
	struct WrapperHelper
	{
		WrapperHelper() : args(nullptr), funPtr(nullptr), objPtr(nullptr)
		{}

		void*	args	= nullptr;
		void*	funPtr	= nullptr;
		void*	objPtr	= nullptr;
	};

public:
#pragma region Constructors
	Thread() = delete;

	template <typename TRet>
	Thread(TRet (*funThread)());
	template <typename TRet>
	Thread(TRet (*funThread)(void*), void*);
	template <typename TRet, typename ... TFunArgs, typename ... TArgs>
	Thread(TRet (*funThread)(TFunArgs ...), TArgs ...args);

		// Normal constructors with non-static method
	template <class TObject, typename TRet, typename ... TFunArgs, typename ... TArgs>
	Thread(TRet (TObject::*)(TFunArgs ...), TObject* obj, TArgs ...args);

	template <typename TRet>
	Thread(Function<TRet> funThread);
	template <typename TRet>
	Thread(Function<TRet, void*> funThread, void*);
	template <typename TRet, typename ... TFunArgs, typename ... TArgs>
	Thread(Function<TRet, TFunArgs ...> funThread, TArgs ...args);
	//template <class TObject, typename TRet, typename ... TFunArgs, typename ... TArgs> {à adapter avec Function<...>(...)}
	//Thread(TRet (TObject::*)(TFunArgs ...), TObject* obj, TArgs ...args);

	~Thread();
#pragma endregion

	void	TryStop();

	// Receive a message from Thread::Send()
	template <typename TRet>
	FORCEINLINE static TRet	Receive(const String&& messageID)
	{
		Thread::mutex_send.Lock();
		while (!Thread::async_send.contains(messageID))
		{
			Thread::mutex_send.Unlock();
			Thread::mutex_send.Lock();
		}
		TRet*	ptr = static_cast<TRet*>(Thread::async_send.at(messageID));
		TRet	ret = *ptr;
		delete(ptr);//::operator delete(ptr);
		Thread::async_send.erase(messageID);
		Thread::mutex_send.Unlock();
		return (ret);
	}

	// Waits for the thread to finish and returns its Thread::Return() value
	template <typename TRet>
	FORCEINLINE TRet	Get()
	{
		void*	buffer;
		TRet	ret;
		pthread_join(this->thread, &buffer);
		ret = *static_cast<TRet*>(buffer);
		delete(static_cast<int*>(buffer));//::operator delete(buffer);
		return (ret);
	}

	// Waits for thread end
	FORCEINLINE void	Wait()
	{
		void*	buffer;
		pthread_join(this->thread, &buffer);
		::operator delete(buffer);
	}

	// FRANCAIS :
	// Permet de quitter un thread, cependant si la fonction est appelé de manière native ET dans le MainThread, il faudra placer un 'return (...);' juste après, de manière à ce que la fonction quitte comme prévu, car cette fonction (Thread::Return) sera ignorée.
	// Si elle est appelée de manière native dans un thread qui n'est pas le principal, le thread sera quitté entièrement.
	//
	// ENGLISH :
	// Allows you to exit a thread, but if the function is called natively AND in the MainThread, you'll need to place a 'return (...);' just after it, so that the function exits as expected, as this function (Thread::Return) will be ignored.
	// If it is called natively in a thread that is not the main thread, the thread will be exited entirely.
	template <typename TRet>
	FORCEINLINE static TRet	Return(TRet return_arg)
	{
		if (pthread_equal(pthread_self(), Thread_MainThreadID))
			return (return_arg);
		TRet*	ret = new TRet;//static_cast<TRet*>(::operator new(sizeof(TRet)));
		*ret = return_arg;
		pthread_exit(ret);
	}

	// FRANCAIS :
	// Toujours utiliser des ID différents, sinon cela pourrait provoquer des comportements indéfinis, tels que des segfault.
	// Quand un message est receptioné avec Receive(), l'ID est libéré et réutilisable.
	//
	// ENGLISH :
	// Always use different IDs, otherwise it may cause undefined behavior, such as segfault.
	// When a message is received with Thread::Receive(), the ID is released and can be reused.
	template <typename TRet>
	FORCEINLINE static void	Send(const String& messageID, const TRet& arg_to_send)
	{
		TRet*	argptr = new TRet;//static_cast<TRet*>(::operator new(sizeof(TRet)));
		*argptr = arg_to_send;
		Thread::mutex_send.Lock();
		Thread::async_send.insert(std::make_pair<const String&, void*>(messageID, argptr));
		Thread::mutex_send.Unlock();
	}

private:
	template <typename TObject, typename TRet, typename TFun, typename ... TArgs>
	static void*	ThreadWrapperMethods(void*);
	template <typename TRet, typename TFun, typename ... TArgs>
	static void*	ThreadWrapper(void*);
	template <typename TRet>
	static void*	BasicThreadWrapper(void*);
	template <typename TRet>
	static void*	VoidptrThreadWrapper(void*);

	template <typename TRet, typename ... TFunArgs, typename ... TArgs>
	void	constructor(TRet (*)(TFunArgs ...), TArgs ...args);
	template <typename TRet>
	void	voidptr_constructor(TRet (*)(void*), void*);
	template <typename TRet>
	void	basic_constructor(TRet (*)());

	template <typename TObject, typename TRet, typename ... TFunArgs, typename ... TArgs>
	void	constructor_methods(TRet (TObject::*&)(TFunArgs ...), TObject* obj, TArgs ...args);

private:
	static std::map<String, void*>
							async_send;
	static Mutex			mutex_send;
	pthread_attr_t*			attr;
	pthread_t				thread;
	WrapperHelper*			wrapperHelper = nullptr;
};

# include "template/Thread.inl"
#endif
