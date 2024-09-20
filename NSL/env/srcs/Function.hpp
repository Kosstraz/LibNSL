/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_FUNCTION_HPP
#define NSL_FUNCTION_HPP

template <typename TRet, typename ... TArgs>
class Function final
{
private:
	typedef TRet (*FUNTYPE)(TArgs...);

public:
	Function() 				noexcept;
	Function(FUNTYPE fun) 	noexcept;
	~Function() 			noexcept = default;

public:
	FUNTYPE	Get() 				const	noexcept;
	TRet	Play(TArgs ...args) const	noexcept;
	void	Replace(FUNTYPE fun) 		noexcept;

private:
	TRet (*fun)(TArgs ...);

public:
	operator FUNTYPE() const noexcept
	{
		return (this->fun);
	}

	TRet	operator()(TArgs ...args) const
	{
		return (this->fun(args ...));
	}
};

template <typename TRet>
class Function<TRet> final
{
	private:
	typedef TRet (*FUNTYPE)();

public:
	Function() 				noexcept;
	Function(FUNTYPE fun) 	noexcept;
	~Function() 			noexcept = default;

public:
	FUNTYPE	Get() 				const	noexcept;
	TRet	Play() 				const	noexcept;
	void	Replace(FUNTYPE fun)		noexcept;

private:
	TRet (*fun)();

public:
	operator FUNTYPE() const noexcept
	{
		return (this->fun);
	}

	TRet	operator()() const
	{
		return (this->fun());
	}
};

# include "template/Function.inl"
#endif
