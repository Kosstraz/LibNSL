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
# include <string> // just for the conversion between String AND std::string

class String final
{
public:
	constexpr	String();
	inline		String(const std::string& str_cpy);
	inline		String(const String& str_cpy);
	constexpr	String(const char* data);
	constexpr	~String();

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

	// Equivalent to .Size(), return -1 if the string is null
	[[nodiscard]]
	constexpr int	Len() const noexcept;
	// Equivalent to .Len(), return -1 if the string is null
	[[nodiscard]]
	constexpr int	Size() const noexcept;

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
	constexpr bool			Empty()			const;
	constexpr const char*	Data()			const noexcept;
	constexpr const char&	At(int index)	const noexcept;
	constexpr const char&	First()			const noexcept;
	constexpr const char&	Last()			const noexcept;
	// Equivalent to .Destroy()
	constexpr void			Clear()				  noexcept;
	// Equivalent to .Clear()
	constexpr void			Destroy()		 	  noexcept;

private:
	inline void	__join__(const String& str)		noexcept;
	inline void	__replace__(const String& str)	noexcept;

public:
	constexpr const char&	operator[](int index) const noexcept;
	constexpr				operator const char*() const noexcept;

	constexpr bool			operator<(const String& str) const noexcept;
	constexpr bool			operator>(const String& str) const noexcept;
	constexpr bool			operator<=(const String& str) const noexcept;
	constexpr bool			operator>=(const String& str) const noexcept;
	constexpr bool			operator==(const String& str) const noexcept;
	constexpr int			operator<=>(const String& str) const noexcept;
	constexpr bool			operator!=(const String& str) const noexcept;

	inline String	operator+(const String& str) const noexcept;
	inline String	operator*(const unsigned int& count) const noexcept;

	inline String&	operator=(const String& str) noexcept;
	inline String&	operator+=(const String& str) noexcept;
	inline String&	operator*=(const unsigned int& count) noexcept;

private:
	char*	data;
	bool	allocated;
};

# include "template/String.inl"
#endif
