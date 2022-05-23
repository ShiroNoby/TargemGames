
#include "string.h"

using namespace string;

//проверить пустую строку
uint32_t size_strlen(const char* data)
{
	assert(data && "data is null");

	uint32_t sum = 0;
	int i = 0;
	while (data[i]) { ++sum;++i; }
	return sum;
}


//*****************************************************************************
// dtor
CString::~CString()												
{
	if(!this->empty()) 
	{
		delete[] m_data;
		m_data = nullptr;
	}					
}


//*****************************************************************************
//ctor
CString::CString(uint32_t size) : m_length(size), m_data(nullptr)
{
	//new data + '\0'
	Allocate(m_length + 1);
}


//ctor
CString::CString(const char* data)	: m_length(size_strlen(data)), m_data(nullptr)
{	
	//???
	//str("") is bad...
	//if(m_length == 0) return;

	//new data + '\0'
	Allocate(m_length + 1);
	Access(data);
}


CString::CString(const CString& str) : m_length(str.m_length), m_data(nullptr)
{
	
	//CString str1 == str2();
	if (str.empty()) { return; }

	//new data + '\0'
	Allocate(m_length + 1);
	Access(str.m_data);	
}


CString::CString(CString&& str) noexcept :m_length(str.m_length), m_data(str.m_data)
{
	str.m_length = 0;
	str.m_data = nullptr;
}


//*****************************************************************************
//operator
CString& CString::operator=(CString& str)
{
	//str1 = str2();
	if (str.empty()) { return *this; }

	//str1 = str1;
	if (*this == str) { return *this; }

	
	delete[] m_data;
	m_length = str.m_length;


	//new data + '\0'
	Allocate(m_length + 1);
	Access(str.m_data);

	return *this;
}


//operator
CString& CString::operator=(CString&& str) noexcept
{
	//str1 = str2();
	if (str.empty()) { return *this; }

	//str1 = str1;
	if (*this == str) { return *this; }


	delete[] m_data;


	m_length = str.m_length;
	m_data = str.m_data;

	str.m_length = 0;
	str.m_data = nullptr;

	return *this;
}


//*****************************************************************************
//new
void CString::Allocate(uint32_t size)
{
	if(!this->empty()) delete[] m_data;
	
	assert(size && "Bad alloce size");

	m_data = new char[size];
}


//m_data[] = data[]
void CString::Access(const char* data)
{
	assert(data && "fail access(data)");
	//???
	//assert(m_length && "fail access(size)");

	for (uint32_t i = 0; i < m_length; i++)
	{
		m_data[i] = data[i];
	}

	m_data[m_length] = '\0';
}


//*****************************************************************************
 //operators whithouth range check
char& CString::operator[](uint32_t index)
{
	assert(!this->empty() && "Bad operator[]");

	return m_data[index];
}


//operator whithouth range check
const char& CString::operator[](uint32_t index) const
{
	assert(!this->empty() && "Bad operator[] const");

	return m_data[index];
}


//operators whith range chek
char& CString::at(uint32_t index)
{
	assert((index <= m_length) && "Bad range check");

	return this->operator[](index);
}


//operators whith range chek
const char& CString::at(uint32_t index) const
{
	assert((index <= m_length) && "Bad range check(const)");

	return this->operator[](index);
}


//(ab|cdf)|(dgf)
//(ab|bcd)|()
//First cmp(str1, str2) then the rest
bool CString::operator<(const CString& str) const 
{
	//so so slow, but i did it
	if(*this == str) {return false;}

	//str1() < str("") --> ret true
	if(m_data == nullptr) { return true;}

	if(m_length <= str.m_length)
	{
		for (uint32_t index = 0; index < m_length; index++)
		{
			if (this->m_data[index] < str[index]) { return true; }
			if (this->m_data[index] > str[index]) { return false; }
		}
		return false;

	}else{
		
		for (uint32_t index = 0; index < str.m_length; index++)
		{
			if (this->m_data[index] < str[index]) { return true; }
			if (this->m_data[index] > str[index]) { return false; }
		}
		return false;
	}
}


//so so(x2) so slow
bool CString::operator>(const CString& str) const 
{
	//so so slow, but i did it... too
	if (*this == str) { return false; }

	return !(this->operator<(str));
}


//so slow
bool CString::operator==(const CString& str) const
{
	if(m_length == str.m_length) 
	{
		for (uint32_t index = 0; index < m_length; index++)
		{
			if (this->operator[](index) != str[index]) { return false; }
		}
		return true;
	}

	return false;
}


//*****************************************************************************
//concatination
CString string::operator+(const CString& str1, const CString& str2)
{
	CString summ(str1.length() + str2.length());

	uint32_t index = 0;
	for( ; index < str1.length(); index++ )
	{
		summ[index] = str1[index];
	}

	for (uint32_t i = 0; i < str2.length(); index++, i++ )
	{
		summ[index] = str2[i];
	}

	summ[index] = '\0';

	return summ;
}


CString string::operator+(const CString& str, const char* data)
{ 
	string::CString tmp(data);
	return str + tmp;
}


CString string::operator+(const char* data, const CString& str)
{
	string::CString tmp(data);
	return tmp + str;
}


//gets whith null-term
const char* CString::c_str() const
{
    return m_data;
}


//gets
uint32_t CString::length() const
{
    return m_length;
}


//data in nullptr
bool CString::empty() const
{
	return m_data == nullptr;
}


//swap str1 <-> str2
void CString::swap(CString& str)
{
	CString tmp;

	tmp = static_cast<string::CString&&>(str);
	str = static_cast<string::CString&&>(*this);
	*this = static_cast<string::CString&&>(tmp);
}