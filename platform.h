/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_PLATFORM_H
#define NSL_PLATFORM_H

# ifndef FORCEINLINE
#  define FORCEINLINE __attribute__((always_inline))
# endif

# ifndef MALLOC_ATTR
#  define MALLOC_ATTR __attribute__((malloc))
# endif

# include <assert.h>

typedef char		bool8;
typedef short		bool16;
typedef int			bool32;
typedef long long	bool64;

typedef char		char1w;
typedef short		char2w;
typedef wchar_t		char4w;

typedef char		int8;
typedef short		int16;
typedef int			int32;
typedef long long	int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef float	float32;
typedef double	float64;

#endif
