/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_STRING_INL
#define NSL_STRING_INL

# include "../String.hpp"
# include <cstring>

bool	String::Contains(const char* data) const
{
	return (strstr(this->data, data) ? true : false);
}

bool	String::Contains(const String& str) const
{
	return (strstr(this->data, str.data) ? true : false);
}

#pragma region CompareWith
constexpr int	String::CompareWith(const char* data) const
{
	return (strcmp(this->data, data));
}

constexpr int	String::CompareWith(const String& str) const
{
	return (strcmp(this->data, str.data));
}

constexpr int	String::CompareNByteWith(const char* data, unsigned int n) const
{
	return (strncmp(this->data, data, n));
}

constexpr int	String::CompareNByteWith(const String& str, unsigned int n) const
{
	return (strncmp(this->data, str.data, n));
}
#pragma endregion






#pragma region IsEqual
constexpr bool	String::IsEqualWith(const char* data) const
{
	return (!strcmp(this->data, data));
}

constexpr bool	String::IsEqualWith(const String& str) const
{
	return (!strcmp(this->data, str.data));
}

constexpr bool	String::IsNByteEqualWith(const char* data, unsigned int n) const
{
	return (!strncmp(this->data, data, n));
}

constexpr bool	String::IsNByteEqualWith(const String& str, unsigned int n) const
{
	return (!strncmp(this->data, str.data, n));
}
#pragma endregion






#pragma region Replace
void	String::Replace(const char* data) noexcept
{
	this->__replace__(data);
}

void	String::Replace(const String& str) noexcept
{
	this->__replace__(str.data);
}

void	String::Overwrite(const char* data) noexcept
{
	this->__replace__(data);
}

void	String::Overwrite(const String& str) noexcept
{
	this->__replace__(str.data);
}
#pragma endregion






#pragma region Strjoin
void	String::Join(const char* data) noexcept
{
	this->__join__(data);
}

void	String::Join(const String& str) noexcept
{
	this->__join__(str);
}

void	String::Append(const char* data) noexcept
{
	this->__join__(data);
}

void	String::Append(const String& str) noexcept
{
	this->__join__(str);
}
#pragma endregion






#pragma region Strlen
uint64	String::Len() const noexcept
{
	if (this->size_calculated)
		return (this->size);
	else if (this->data)
		return (this->__length__());
	return (-1);
}

uint64	String::Size() noexcept
{
	if (this->size_calculated)
		return (this->size);
	else if (this->data)
	{
		this->_setSize_(this->__length__());
		return (this->size);
	}
	return (-1);
}

uint64	String::Len(const String& str) noexcept
{
	if (str.size_calculated)
		return (str.size);
	else if (str.data)
	{
		return (__length__(str));
	}
	return (-1);
}

uint64	String::Size(String& str) noexcept
{
	if (str.size_calculated)
		return (str.size);
	else if (str.data)
		return (__length__(str));
	return (-1);
}
#pragma endregion





void	String::Swap(String& str) noexcept
{
	Memory::Swap(*this, str);
}

void	String::Shuffle() noexcept
{
	this->data = strfry(this->data);
}

char*	String::CString(const String& str) noexcept
{
	int		newSize = str.Len();
	char*	ret = new char[newSize + 1U];
	strlcpy(ret, str.data, newSize + 1U);
	ret[newSize] = '\0';
	return (ret);
}

char*	String::CString() noexcept
{
	char*	ret = new char[this->Len()];
	strlcpy(ret, this->data, this->Len() + 1U);
	return (ret);
}

void	String::Erase(int index) noexcept
{
	int			totalSize = this->Size();
	unsigned	secondPart= index + 1U;
	char*		ref = this->data;

	if (index >= totalSize || totalSize == -1)
		return ;
	this->data = new char[totalSize];
	strlcpy(this->data, ref, secondPart);
	strlcpy(&this->data[index], &ref[secondPart], totalSize - index);
	this->data[totalSize - 1U] = '\0';
	if (this->allocated)
		delete[](ref);
	this->allocated = true;
	this->_setSize_(totalSize - 1ULL);
}

bool			String::Empty() const
{
	return (!this->data || !this->data[0]);
}

constexpr const char*	String::Data() const noexcept
{
	return (this->data);
}

constexpr const char&	String::At(int index) const noexcept
{
	return (this->data[index]);
}

const char&	String::First() const noexcept
{
	return (*this->data);
}

const char&	String::Last() const noexcept
{
	return (this->data[this->Len() - 1]);
}

constexpr void	String::Clear() noexcept
{
	if (this->allocated && this->data)
		delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
	this->_setSize_(0ULL);
}

constexpr void	String::Destroy() noexcept
{
	if (this->allocated && this->data)
		delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
	this->_setSize_(0ULL);
}

constexpr void	String::_setSize_(uint64 newSize) noexcept
{
	this->size = newSize;
	this->size_calculated = true;
}


#pragma region OthersOP
constexpr const char&	String::operator[](int index) const noexcept
{
	return (this->data[index]);
}

constexpr	String::operator const char*() const noexcept
{
	return (this->data);
}
#pragma endregion





#pragma region ComparaisonOP
constexpr bool	String::operator<(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) < 0)
		return (true);
	return (false);
}

constexpr bool	String::operator>(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) > 0)
		return (true);
	return (false);
}

constexpr bool	String::operator<=(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) <= 0)
		return (true);
	return (false);
}

constexpr bool	String::operator>=(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) >= 0)
		return (true);
	return (false);
}

constexpr int	String::operator<=>(const String& str) const noexcept
{
	return (strcmp(this->data, str.data));
}

constexpr bool	String::operator==(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) == 0)
		return (true);
	return (false);
}

constexpr bool	String::operator!=(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) != 0)
		return (true);
	return (false);
}
#pragma endregion





#pragma region ArithmeticOP
String		String::operator+(const String& str) const noexcept
{
	String	ret(*this);
	ret.Join(str);
	return (ret);
}

String		String::operator*(const unsigned int& count) const noexcept
{
	String	ret(*this);
	String	toMultiply(ret);
	for (unsigned int i = 1 ; i < count ; i++)
		ret.Join(toMultiply);
	return (ret);
}
#pragma endregion






#pragma region AssignmentOP
String&		String::operator=(const String& str) noexcept
{
	if (this != &str)
	{
		if (this->data && this->allocated)
			delete[](this->data);
		this->data = String::CString(str);
		this->allocated = true;
		this->size = str.size;
		this->size_calculated = str.size_calculated;
	}
	return (*this);
}

String&		String::operator+=(const String& str) noexcept
{
	this->Join(str);
	return (*this);
}

String&		String::operator*=(const unsigned int& count) noexcept
{
	*this = *this * count;
	return (*this);
}
#pragma endregion


#endif
