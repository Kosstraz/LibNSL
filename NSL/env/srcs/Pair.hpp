#ifndef NSL_PAIR_HPP
#define NSL_PAIR_HPP

# include "../NSLplatform.h"
# include "TypesCap.hpp"

template <typename T1, typename T2>
struct Pair
{
private:
	typedef Decay<T1>	_T1;
	typedef Decay<T2>	_T2;

public:
	constexpr	Pair() noexcept : key(), val()
	{
	}

	constexpr	Pair(const T1& a, const T2& b) noexcept : key(_T1(a)), val(_T2(b))
	{
	}

	constexpr	Pair(T1&& a, T2&& b) noexcept : key(Meta::Forward<T1>(a)), val(Meta::Forward<T2>(b))
	{
	}

	virtual FORCEINLINE	~Pair()
	{
	}

	_T1	key;
	_T2	val;
};


#endif
