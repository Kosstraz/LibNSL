/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_STRING_INL
#define NSL_STRING_INL

# include "../String.hpp"
# include <cstring>

constexpr String::String() : data(nullptr), allocated(false)
{
}

String::String(const std::string& str) : data(String::CString(str.data())), allocated(true)
{
}

String::String(const String& str) : data(String::CString(str)), allocated(true)
{
}

constexpr String::String(const char* data) : data(const_cast<char*>(data)), allocated(false)
{
}

constexpr String::~String()
{
	this->Destroy();
}

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

void	String::__replace__(const String& str) noexcept
{
	unsigned int	newSize = strlen(str.data);

	if (this->allocated && this->data)
		delete[](this->data);
	this->data = new char[newSize + 1U];
	this->allocated = true;
	strlcpy(this->data, str.data, newSize + 1U);
	this->data[newSize] = '\0';
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

void	String::__join__(const String& str) noexcept
{
	unsigned int	thisLen = strlen(this->data);
	unsigned int	dataLen = strlen(str.data);
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
}
#pragma endregion






#pragma region Strlen
constexpr int	String::Len() const noexcept
{
	if (this->data)
		return (strlen(this->data));
	return (-1);
}

constexpr int	String::Size() const noexcept
{
	if (this->data)
		return (strlen(this->data));
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
	int			totalSize = strlen(this->data);
	unsigned	secondPart= index + 1U;
	char*		ref = this->data;

	if (totalSize == -1)
		return ;
	this->data = new char[totalSize];
	strlcpy(this->data, ref, secondPart);
	strlcpy(&this->data[index], &ref[secondPart], totalSize - index);
	this->data[totalSize - 1U] = '\0';
	if (this->allocated)
		delete[](ref);
	this->allocated = true;
}

constexpr bool			String::Empty() const
{
	return (!strlen(this->data));
}

constexpr const char*	String::Data() const noexcept
{
	return (this->data);
}

constexpr const char&	String::At(int index) const noexcept
{
	return (this->data[index]);
}

constexpr const char&	String::First() const noexcept
{
	return (*this->data);
}

constexpr const char&	String::Last() const noexcept
{
	return (this->data[this->Len() - 1]);
}

constexpr void	String::Clear() noexcept
{
	if (this->allocated && this->data)
		delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
}

constexpr void	String::Destroy() noexcept
{
	if (this->allocated && this->data)
		delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
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
