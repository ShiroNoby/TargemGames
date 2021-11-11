#include "string.h"

using namespace string;

//
int size_strlen(const char* data) 
{
	int sum = 0;
	int i = 0;
	while (data[i]) { ++sum;++i; }
	return sum;
}


/////////////////**************************************************************\\\\\\\\\\\\\\\\\\\\\\\\\\


//ctor
CString::CString():m_length(0), m_data(nullptr)					{}

//ctor
CString::CString(const CString& str) : m_length(str.m_length), m_data(nullptr)
{
	m_data = new char[static_cast<__int64>(m_length) + 1];

	for (int i = 0; i < m_length; i++)
	{
		m_data[i] = str.m_data[i];
	}

	m_data[m_length] = '\0';
	
	return;	
}

//ctor
CString::CString(CString&& str) noexcept :m_length(str.m_length), m_data(str.m_data)
{
	str.m_length = 0;
	str.m_data = nullptr;
}

//ctor
CString::CString(const char* data)	: m_length(size_strlen(data)), m_data(nullptr)
{	
	m_data = new char[static_cast<__int64>(m_length) + 1];

	for (int i = 0; i < m_length; i++) 
	{
		m_data[i] = data[i];
	}

	m_data[m_length] = '\0';
}

// dtor
CString::~CString()												
{
	if (m_data == nullptr) return;

	delete [] m_data;
	m_data = nullptr; 					
}


//////////////////operator
/////////////////**************************************************************\\\\\\\\\\\\\\\\\\\\\\\\\\

//operator
char& CString::operator[](int index) 
{
	if (index >= 0 && index < m_length) return m_data[index];
}


//operator
const char& CString::operator[](int index) const
{
	if (index >= 0 && index < m_length) return m_data[index];
}


//operator
CString& CString::operator=(const char* data)
{
	if (!data) { return *this; }

	m_length = size_strlen(data);
	delete[] m_data;
	m_data = new char[static_cast<__int64>(m_length) + 1];

	for (int i = 0; i < m_length; i++)
	{
		m_data[i] = data[i];
	}

	m_data[m_length] = '\0';
	return *this;
}


//operator
CString& CString::operator=(CString& str)
{
	if (!str.m_data) { return *this; }
	if (this->m_data == str.m_data) { return *this; }

	m_length = str.m_length;
	delete[] m_data;
	m_data = new char[static_cast<__int64>(m_length) + 1];

	for (int i = 0; i < m_length; i++)
	{
		m_data[i] = str.m_data[i];
	}

	m_data[m_length] = '\0';
	return *this;
}


//operator
CString& CString::operator=(CString&& str) noexcept
{
	if (!str.m_data) { return *this; }
	if (this->m_data == str.m_data) { return *this; }

	delete[] m_data;

	m_length = str.m_length;
	m_data = str.m_data;

	str.m_length = 0;
	str.m_data = nullptr;

	return *this;
}


//operator
bool CString::operator<(const CString& str) const
{
	for (int index = 0; index < this->get_length(); index++)
	{
		if (this->m_data[index] < str[index]) { return true; }
		if (this->m_data[index] > str[index]) { return false; }
	}

	return false;
}


//operator
bool CString::operator>(const CString& str) const
{
	return str < *this;
}


//////////////////concatination
/////////////////**************************************************************\\\\\\\\\\\\\\\\\\\\\\\\\\


//concatination
CString& CString::operator+(string::CString& str)
{
	CString sum;
	
	//bcos str1 + ' ' + str2
	sum.m_length = this->m_length + 1 + str.m_length;

	sum.m_data = new char[static_cast<__int64>(sum.m_length) + 1];

	int index = 0;
	if (this->m_length)
	{
		for (index; index < this->m_length; index++)
		{
			sum.m_data[index] = this->m_data[index];
		}

		sum.m_data[index] = ' ';
		++index;
	}

	for (int i = 0; i < str.m_length; i++, index++)
	{
		sum.m_data[index] = str.m_data[i];
	}

	sum.m_data[sum.m_length] = '\0';
		
	*this = sum;
	return *this;
}


//concatination
CString& CString::operator+(const char* data)
{
	CString sum;

	//bcos str1 + ' ' + str2
	sum.m_length = this->m_length + 1 + size_strlen(data);

	sum.m_data = new char[static_cast<__int64>(sum.m_length) + 1];

	int index = 0;
	if (this->m_length)
	{
		for (index; index < this->m_length; index++)
		{
			sum.m_data[index] = this->m_data[index];
		}

		sum.m_data[index] = ' ';
		++index;
	}

	for (int i = 0; i < size_strlen(data); i++, index++)
	{
		sum.m_data[index] = data[i];
	}

	sum.m_data[sum.m_length] = '\0';
	
	*this = sum;
	return *this;
}


//extra-concatination
CString	string::operator+(const char* data, string::CString& str2)
{
	CString sum;

	//bcos str1 + ' ' + str2
	sum.m_length = size_strlen(data) + 1 + str2.m_length;

	sum.m_data = new char[static_cast<__int64>(sum.m_length) + 1];

	int index = 0;
	for (index; index < size_strlen(data); index++)
	{
		sum.m_data[index] = data[index];
	}

	sum.m_data[index] = ' ';
	++index;

	for (int i = 0; i < str2.m_length; i++, index++)
	{
		sum.m_data[index] = str2.m_data[i];
	}

	sum.m_data[sum.m_length] = '\0';
	return sum;
}


//get
const char* CString::get_char() const
{
	if (m_data) return m_data;

	return "nullString";
}


//get
int CString::get_length() const	{ return m_length; }


//
void CString::swap(string::CString& str) 
{
	CString tmp;

	tmp = static_cast<string::CString&&>(str);
	str = static_cast<string::CString&&>(*this);
	*this = static_cast<string::CString&&>(tmp);
}
