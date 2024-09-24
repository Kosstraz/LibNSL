#include "../String.hpp"

#pragma region OthersOP
constexpr const char&
String::operator[](int index) const noexcept
{
	return (this->data[index]);
}

constexpr
String::operator const char*() const noexcept
{
	return (this->data);
}
#pragma endregion





#pragma region ComparaisonOP
constexpr bool
String::operator<(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) < 0)
		return (true);
	return (false);
}

constexpr bool
String::operator>(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) > 0)
		return (true);
	return (false);
}

constexpr bool
String::operator<=(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) <= 0)
		return (true);
	return (false);
}

constexpr bool
String::operator>=(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) >= 0)
		return (true);
	return (false);
}

constexpr int
String::operator<=>(const String& str) const noexcept
{
	return (strcmp(this->data, str.data));
}

constexpr bool
String::operator==(const String& str) const noexcept
{
	if (strcmp(this->data, str.data) == 0)
		return (true);
	return (false);
}

constexpr bool
String::operator!=(const String& str) const noexcept
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
