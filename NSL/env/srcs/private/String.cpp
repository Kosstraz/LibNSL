/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../String.hpp"

String::String() : data(nullptr), size(0ULL), allocated(false), size_calculated(true)
{
}

String::String(const std::string& str) : data(String::CString(str.data())), size(0ULL), allocated(true), size_calculated(false)
{
}

String::String(const String& str) : data(String::CString(str)), size(0ULL), allocated(true), size_calculated(false)
{
}

String::String(const char* data) : data(const_cast<char*>(data)), size(0ULL), allocated(false), size_calculated(false)
{
}

String::~String()
{
	this->Destroy();
}

void	String::__replace__(const String& str) noexcept
{
	unsigned int	newSize = str.Len();

	if (this->allocated && this->data)
		delete[](this->data);
	this->data = new char[newSize + 1U];
	this->allocated = true;
	strlcpy(this->data, str.data, newSize + 1U);
	this->data[newSize] = '\0';
	this->_setSize_(newSize);
}

void	String::__join__(const String& str) noexcept
{
	unsigned int	thisLen = this->Len();
	unsigned int	dataLen = str.Len();
	unsigned int	totaLen = thisLen + dataLen + 2U;
	char*			ref = this->data;

	this->data = new char[totaLen];
	if (thisLen > 0)
	{
		strlcpy(this->data, ref, thisLen + 1);
		if (this->allocated)
			delete[](ref);
	}
	strlcpy(&this->data[thisLen], str.data, dataLen + 1);
	this->data[totaLen - 1U] = '\0';
	this->allocated = true;
	this->_setSize_(totaLen - 2ULL);
}

#pragma region __length__
#if defined(AVX2)
uint64	String::__length__() const noexcept
{
	uint64			i	= 0ULL;
	const int256	z	= _mm256_setzero_si256();
	const int256*	mem	= (const int256*)this->data;

	for ( ; ; i += 1ULL)
	{
		const int256	chunk	= _mm256_loadu_si256(&mem[i]);
		const int256	mask	= _mm256_cmpeq_epi8(z, chunk);
		const int		val		= _mm256_movemask_epi8(mask);
		if (val)
			return (i * 32ULL + __builtin_ctz(val));

	}
	assert(false);
}
#elif defined(SSE2)
uint64	String::__length__() const noexcept
{
	uint64			i	= 0ULL;
	const int128	z	= _mm_setzero_si128();
	const int128*	mem	= (const int128*)this->data;

	for ( ; ; i += 1ULL)
	{
		const int128	chunk	= _mm_loadu_si128(&mem[i]);
		const int128	mask	= _mm_cmpeq_epi8(z, chunk);
		const int		val		= _mm_movemask_epi8(mask);
		if (val)
			return (i * 16ULL + __builtin_ctz(val));
	}
	assert(false);
}
#else
uint64	String::__length__() const noexcept
{
	uint64 i = 0;
	for ( ; this->data[i] ; i++) ;
	return (i);
}
#endif
#pragma endregion







#pragma region static __length__
#if defined(AVX2)
uint64	String::__length__(const String& str) noexcept
{
	uint64			i	= 0ULL;
	const int256	z	= _mm256_setzero_si256();
	const int256*	mem	= (const int256*)str.data;

	for ( ; ; i += 1ULL)
	{
		const int256	chunk	= _mm256_loadu_si256(&mem[i]);
		const int256	mask	= _mm256_cmpeq_epi8(z, chunk);
		const int		val		= _mm256_movemask_epi8(mask);
		if (val)
			return (i * 32ULL + __builtin_ctz(val));

	}
	assert(false);
}
#elif defined(SSE2)
uint64	String::__length__(const String& str) noexcept
{
	uint64			i	= 0ULL;
	const int128	z	= _mm_setzero_si128();
	const int128*	mem	= (const int128*)str.data;

	for ( ; ; i += 1ULL)
	{
		const int128	chunk	= _mm_loadu_si128(&mem[i]);
		const int128	mask	= _mm_cmpeq_epi8(z, chunk);
		const int		val		= _mm_movemask_epi8(mask);
		if (val)
			return (i * 16ULL + __builtin_ctz(val));
	}
	assert(false);
}
#else
uint64	String::__length__(const String& str) noexcept
{
	uint64 i = 0;
	for ( ; str.data[i] ; i++) ;
	return (i);
}
#endif
#pragma endregion
