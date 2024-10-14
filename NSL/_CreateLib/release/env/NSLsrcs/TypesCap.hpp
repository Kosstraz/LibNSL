/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_TYPESCAP_HPP
#define NSL_TYPESCAP_HPP

# include "../NSL_platform.h"

/************/
/*	PRIVATE	*/
/************/

namespace private_removeRefStructs
{
	template <typename T>
	struct RemoveRefStruct
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemoveRefStruct<T&>
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemoveRefStruct<T&&>
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemoveRefStruct<const T&>
	{
		typedef	const T	type;
	};
}

namespace private_removePtrStructs
{
	template <typename T>
	struct RemovePtrStruct
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemovePtrStruct<T*>
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemovePtrStruct<const T*>
	{
		typedef	const T	type;
	};
}

namespace private_removeConstStructs
{
	template <typename T>
	struct RemoveConstStruct
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemoveConstStruct<const T>
	{
		typedef	T	type;
	};

	template <typename T>
	struct RemoveConstStruct<const T&>
	{
		typedef	T&	type;
	};

	template <typename T>
	struct RemoveConstStruct<const T*>
	{
		typedef	T*	type;
	};
}

namespace private_EnableIf
{
	template <typename T, const bool BCondition>
	struct EnableIFStruct
	{
		typedef T	TType;
	};
	template <typename T>
	struct EnableIFStruct<T, false>
	{
	};
}

/************/
/*	PUBLIC	*/
/************/

/********************/
/*	REMOVE TYPES	*/
/********************/


template <typename T>
using RemoveRef = typename private_removeRefStructs::RemoveRefStruct<T>::type;

template <typename T>
using RemovePtr = typename private_removePtrStructs::RemovePtrStruct<T>::type;

template <typename T>
using RemoveConst = typename private_removeConstStructs::RemoveConstStruct<T>::type;

template <typename T>
using RawType = RemoveConst<RemoveRef<RemovePtr<T>>>;

/************/
/*	TYPES	*/
/************/

namespace Types
{

template <typename T, const bool BCondition>
using EnableIF = private_EnableIf::EnableIFStruct<T, BCondition>::TType;

// Knowing if two types are the same
template <typename T, typename U>
inline constexpr bool	IsSame = false;
// Knowing if two types are the same
template <typename T>
inline constexpr bool	IsSame<T, T> = true;

/*// Savoir si deux types BRUTS sont les mêmes
template <typename T, typename U>
inline constexpr bool	IsRawSame = false;
// Savoir si deux types BRUTS sont les mêmes
template <typename T>
inline constexpr bool	IsRawSame<RawType<T>, RawType<T>> = true;*/

template <typename T>
inline constexpr bool	IsVoid = IsSame<T, void>;

template <typename T>
inline constexpr bool	IsUnsigned =
	(
		IsSame<RawType<T>, unsigned char>
			||
		IsSame<RawType<T>, unsigned short>
			||
		IsSame<RawType<T>, unsigned int>
			||
		IsSame<RawType<T>, unsigned long>
			||
		IsSame<RawType<T>, unsigned long long>
	);

template <typename T>
inline constexpr bool	IsIntegral =
	(
		IsSame<RawType<T>, char>
			||
		IsSame<RawType<T>, short>
			||
		IsSame<RawType<T>, int>
			||
		IsSame<RawType<T>, long>
			||
		IsSame<RawType<T>, long long>
			||
		IsSame<RawType<T>, bool>
			||
		IsUnsigned<T>
	);

template <typename T>
inline constexpr bool	IsSigned =
	(
		!IsUnsigned<T>
			&&
		IsIntegral<T>
	);

template <typename T>
inline constexpr bool	IsFloatingPoint =
	(
		IsSame<RawType<T>, float>
			||
		IsSame<RawType<T>, double>
			||
		IsSame<RawType<T>, long double>
	);

template <typename T>
inline constexpr bool	IsNative =
	(
		IsFloatingPoint<T>
			||
		IsIntegral<T>
			||
		IsVoid<T>
	);

template <typename T>
inline constexpr bool	IsObject =
	(
		!IsNative<T>
			&&
		!IsVoid<T>
	);

template <typename T>
inline constexpr bool	IsAnyNumberType =
	(
		IsFloatingPoint<T>
			||
		IsIntegral<T>
	);

template <typename T>
inline constexpr unsigned long	SizeMax =
	(
		IsSigned<T>
			*
		static_cast<long>((1UL << ((sizeof(T) * 8) - 1)) - 1UL)
			+
		IsUnsigned<T>
			*
		static_cast<long>((1UL << (sizeof(T) * 8)) - 1UL)
			+
		IsObject<T>
			*
		sizeof(T)
	);

template <typename T>
inline constexpr unsigned long	SizeMin =
	(
		IsSigned<T>
			*
		-SizeMax<T> - (1UL - IsUnsigned<T>)
			+
		IsUnsigned<T>
			*
		0UL
			+
		IsObject<T>
			*
		sizeof(T)
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsPositive =
	(
		N >= 0
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsNegative =
	(
		N < 0
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsZero =
	(
		N == 0
	);

}

#endif
