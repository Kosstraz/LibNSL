/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_STRING_HPP
#define NSL_STRING_HPP

# ifndef MALLOC_ATTR
#  define MALLOC_ATTR __attribute__((malloc))
# endif

# include "Memory.hpp"
# include "../NSL_SIMDplatform.h"
# include "../NSL_platform.h"
# include <string> // just for the conversion between String AND std::string

class String final
{
public:
	String();
	String(const std::string& str_cpy);
	String(const String& str_cpy);
	String(const char* data);
	~String();

	inline bool	Contains(const char* data)	const;
	inline bool	Contains(const String& str)	const;

	constexpr int	CompareWith(const char* data)	const;
	constexpr int	CompareWith(const String& str)	const;
	constexpr int	CompareNByteWith(const char* data, unsigned int n)	const;
	constexpr int	CompareNByteWith(const String& str, unsigned int n)	const;

	constexpr bool	IsEqualWith(const char* data)	const;
	constexpr bool	IsEqualWith(const String& str)	const;
	constexpr bool	IsNByteEqualWith(const char* data, unsigned int n)	const;
	constexpr bool	IsNByteEqualWith(const String& str, unsigned int n)	const;

	// Equivalent to .Overwrite()
	inline void	Replace(const char* data)		noexcept;
		// Equivalent to .Overwrite()
	inline void	Replace(const String& str)		noexcept;
	// Equivalent to .Replace()
	inline void	Overwrite(const char*  data)	noexcept;
	// Equivalent to .Replace()
	inline void	Overwrite(const String& str)	noexcept;

	// Equivalent to .Join()
	inline void	Append(const char* data)	noexcept;
	// Equivalent to .Join()
	inline void	Append(const String& str)	noexcept;
	// Equivalent to .Append()
	inline void	Join(const char* data)		noexcept;
	// Equivalent to .Append()
	inline void	Join(const String& str)		noexcept;

	// Return -1 if the string is null
	// Calcul the length for each call (use Size() instead)
	[[nodiscard]]
	inline uint64	Len() const noexcept;
	// Return -1 if the string is null
	// Like Len(), but Size() doesn't recalculate the length if it has already been calculated
	[[nodiscard]]
	inline uint64	Size() noexcept;

	// Return -1 if the string is null
	// Calcul the length for each call (use Size() instead)
	[[nodiscard]]
	static inline uint64	Len(const String& str) noexcept;
	// Return -1 if the string is null
	// Like Len(), but Size() doesn't recalculate the length if it has already been calculated
	[[nodiscard]]
	static inline uint64	Size(String& str) noexcept;


	// (static) Return a new allocated string equal to the string.Data() in parameter
	// !(ne pas oublier de 'delete[]')!
	[[nodiscard]]
	static inline char*	CString(const String&)	noexcept MALLOC_ATTR;
	// Return a new allocated string equal to this string .Data()
	// !(ne pas oublier de 'delete[]')!
	[[nodiscard]]
	inline char*		CString()				noexcept MALLOC_ATTR;

	inline void				Swap(String&)		  noexcept;
	inline void				Shuffle()			  noexcept;
	inline void				Erase(int idex)		  noexcept;
	inline bool				Empty()			const;
	constexpr const char*	Data()			const noexcept;
	constexpr const char&	At(int index)	const noexcept;
	inline const char&		First()			const noexcept;
	inline const char&		Last()			const noexcept;
	// Equivalent to .Destroy()
	constexpr void			Clear()				  noexcept;
	// Equivalent to .Clear()
	constexpr void			Destroy()		 	  noexcept;

private:
	constexpr void	_setSize_(uint64 newSize)		noexcept;

	void	__join__(const String& str)		noexcept;
	void	__replace__(const String& str)	noexcept;
	uint64	__length__()			  const noexcept;

	static uint64	__length__(const String& str)	noexcept;

public:
	constexpr const char&	operator[](int index)	const noexcept;
	constexpr				operator const char*()	const noexcept;

	constexpr bool			operator<(const String& str)	const noexcept;
	constexpr bool			operator>(const String& str)	const noexcept;
	constexpr bool			operator<=(const String& str)	const noexcept;
	constexpr bool			operator>=(const String& str)	const noexcept;
	constexpr bool			operator==(const String& str)	const noexcept;
	constexpr int			operator<=>(const String& str)	const noexcept;
	constexpr bool			operator!=(const String& str)	const noexcept;

	inline String	operator+(const String& str)			const noexcept;
	inline String	operator*(const unsigned int& count)	const noexcept;

	inline String&	operator=(const String& str)			noexcept;
	inline String&	operator+=(const String& str)			noexcept;
	inline String&	operator*=(const unsigned int& count)	noexcept;

private:
	char*	data;
	uint64	size;
	bool	allocated;
	bool	size_calculated;
};

# include "template/String.inl"
# include "template/String_op.inl"
#endif
