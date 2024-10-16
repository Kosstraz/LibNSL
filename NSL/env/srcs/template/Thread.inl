/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_THREAD_INL
#define NSL_THREAD_INL

# include "../Thread.hpp"

#pragma region Constructor

template <typename TRet>
Thread::Thread(	TRet (*funThread)()) : joined(false)
{
	this->basic_constructor(funThread);
}

template <typename TRet>
Thread::Thread(TRet (*funThread)(void*),
				void* arg) : joined(false)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(TRet (*funThread)(TFunArgs ...),
				TArgs ...args) : joined(false)
{
	this->constructor(funThread, args...);
}
 
template <typename TRet>
Thread::Thread(	Function<TRet> funThread) : joined(false)
{
	TRet (*funTmp)() = static_cast<TRet (*)()>(funThread);
	this->basic_constructor(funTmp);
}

template <typename TRet>
Thread::Thread(Function<TRet, void*> funThread,
				void* arg) : joined(false)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(	Function<TRet, TFunArgs ...> funThread,
				TArgs ...args) : joined(false)
{
	TRet (*funTmp)(TArgs ...) = static_cast<TRet (*)(TArgs ...)>(funThread);
	this->constructor<TRet>(funTmp, args...);
}

#pragma endregion






#pragma region Constructor non-static methods
template <typename TObject, typename TRet, typename... TFunArgs, typename... TArgs>
Thread::Thread(TRet (TObject::*funmethod)(TFunArgs ...), TObject* obj, TArgs ...args) : joined(false)
{
	this->constructor_methods(funmethod, obj, args...);
}
#pragma endregion






#pragma region constructorHelper

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
void
Thread::constructor(TRet (*f)(TFunArgs ...), TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapper<TRet, TRet (*)(TFunArgs...), TArgs...>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void
Thread::basic_constructor(TRet (*f)())
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = nullptr;
	pthread_create(&this->thread, nullptr, Thread::BasicThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void
Thread::voidptr_constructor(TRet (*f)(void*), void* arg)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = arg;
	pthread_create(&this->thread, nullptr, Thread::VoidptrThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}


template <typename TObject, typename TRet, typename ... TFunArgs, typename ... TArgs>
void
Thread::constructor_methods(TRet (TObject::*&f)(TFunArgs ...), TObject* obj, TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	this->wrapperHelper->objPtr = static_cast<void*>(obj);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperMethods<TObject, TRet, TRet (TObject::*)(TFunArgs...), TArgs...>, static_cast<void*>(this->wrapperHelper));
}

#pragma endregion






#pragma region ThreadWrapper

template <typename TRet, typename TFun, typename ... TArgs>
void*
Thread::ThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TFun					funPtr		= reinterpret_cast<TFun>(helpingArgs->funPtr);
	Package<TArgs...>		*argsPack	= static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack<TFun, TArgs...>(funPtr, (*argsPack));
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*
Thread::BasicThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)()					= reinterpret_cast<TRet (*)()>(helpingArgs->funPtr);
	funPtr();
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*
Thread::VoidptrThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)(void*)				= reinterpret_cast<TRet (*)(void*)>(helpingArgs->funPtr);
	funPtr(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}


template <typename TObject, typename TRet, typename TFun, typename ... TArgs>
void*
Thread::ThreadWrapperMethods(void* args)
{
	Thread::WrapperHelper*	helpingArgs 	= static_cast<Thread::WrapperHelper*>(args);
	TObject*				classInstance	= static_cast<TObject*>(helpingArgs->objPtr);
	TFun					funPtr			= reinterpret_cast<TFun>(reinterpret_cast<TFun&>(helpingArgs->funPtr));
	Package<TArgs...>*		argsPack		= static_cast<Package<TArgs...>*>(helpingArgs->args);
	NSUnpack<TFun, TObject, TArgs...>(funPtr, classInstance, (*argsPack));
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

#pragma endregion




#pragma region Methods

#pragma endregion


#endif
