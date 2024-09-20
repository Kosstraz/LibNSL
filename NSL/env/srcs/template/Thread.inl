/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_THREAD_INL
#define NSL_THREAD_INL

# include "../Thread.hpp"

#pragma region Constructor

template <typename TRet>
Thread::Thread(	TRet (*funThread)()) :
										attr(nullptr)
{
	this->basic_constructor(funThread);
}

template <typename TRet>
Thread::Thread(TRet (*funThread)(void*),
				void* arg) :
									attr(nullptr)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(TRet (*funThread)(TFunArgs ...),
				TArgs ...args) :
									attr(nullptr)
{
	this->constructor(funThread, args...);
}
 
template <typename TRet>
Thread::Thread(	Function<TRet> funThread) :
													attr(nullptr)
{
	TRet (*funTmp)() = static_cast<TRet (*)()>(funThread);
	this->basic_constructor(funTmp);
}

template <typename TRet>
Thread::Thread(Function<TRet, void*> funThread,
				void* arg) :
									attr(nullptr)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(	Function<TRet, TFunArgs ...> funThread,
				TArgs ...args) :
									attr(nullptr)
{
	TRet (*funTmp)(TArgs ...) = static_cast<TRet (*)(TArgs ...)>(funThread);
	this->constructor<TRet>(funTmp, args...);
}

#pragma endregion






#pragma region constructorHelper

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
void	Thread::constructor(TRet (*f)(TFunArgs ...), TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapper<TRet, TRet (*)(TFunArgs...), TArgs...>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void	Thread::basic_constructor(TRet (*f)())
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = nullptr;
	pthread_create(&this->thread, nullptr, Thread::BasicThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void	Thread::voidptr_constructor(TRet (*f)(void*), void* arg)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = arg;
	pthread_create(&this->thread, nullptr, Thread::VoidptrThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}

#pragma endregion






#pragma region ThreadWrapper

template <typename TRet, typename TFun, typename ... TArgs>
void*	Thread::ThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TFun	funPtr						= reinterpret_cast<TFun>(helpingArgs->funPtr);
	Package<TArgs...>	*argsPack		= static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack<TFun, TArgs...>(funPtr, (*argsPack));
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*	Thread::BasicThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)()			= reinterpret_cast<TRet (*)()>(helpingArgs->funPtr);
	funPtr();
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*	Thread::VoidptrThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)(void*)			= reinterpret_cast<TRet (*)(void*)>(helpingArgs->funPtr);
	funPtr(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

#pragma endregion

#endif
