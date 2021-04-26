//я мог бы вынести это в отдельный файл, но не буду
#include "string.h"

namespace _str 
{
	//*init m_length
	//default empty constructor
	string::string()
		:m_data(nullptr), m_length(0) {}


	//constructor coppying
	string::string(const _str::string& str)
	{
		
		//запрос памяти для новых данных
		this->m_length = str.m_length;
		this->m_data = new char[this->m_length + 1];

		//копирование данных
		for (int i = 0; i < str.m_length; i++)
		{
			this->m_data[i] = str.m_data[i];
		}

		//точка останова
		this->m_data[m_length] = '\0';
		
		//где нуль-термин
		//что со старыми данными?
	}

	//constructor coppying
	string::string(const char* data)
	{
		
		//запрос памяти для новых данных
		this->m_length = strlen(data);
		this->m_data = new char[strlen(data) + 1];

		//копирование данных
		for (int i = 0; i < m_length; i++)
		{
			this->m_data[i] = data[i];
		}

		//точка останова
		this->m_data[m_length] = '\0';

		//где нуль-термин
		//что со старыми данными?
	}

	//operator coppying
	void string::operator=(_str::string str)
	{
		//чистка старых данных
		if (this->m_data)
		{
			delete[] m_data;
			this->m_data = nullptr;
			this->m_length = 0;
		}

		//запрос памяти для новых данных
		this->m_length = str.m_length;
		this->m_data = new char[this->m_length + 1];

		//копирование данных
		for (int i = 0; i < str.m_length; i++)
		{
			this->m_data[i] = str.m_data[i];
		}

		//точка останова
		this->m_data[m_length] = '\0';

		//где нуль-термин
		//что со старыми данными?
	}

	//move-operator
	void string::operator=(_str::string& str)
	{
		//чистка старых данных
		if (this->m_data)
		{
			delete[] m_data;
			this->m_data = nullptr;
			this->m_length = 0;
		}

		//отжимаем указатель и размер строки
		this->m_length = str.m_length;
		this->m_data = str.m_data;;


		//убираем свидетелей
		str.m_length = 0;
		str.m_data = nullptr;
	}

	//эт что такое?
	char& string::operator[](int index) const
	{
		return m_data[index];
	}

	//str.swap(str1)
	void string::swap(_str::string& str)
	{
		//чую косяк с памятью 

		//делаем времянку
		_str::string tmp;
		
		//присваиваем временной строке значение строки а
		tmp = std::move(*this);

		//присваиваем строке а значение строки б
		*this = std::move(str);

		//присваиваем строке б значение из временной строки
		str = std::move(tmp);
	}

	//измение имя
	int string::get_length() const
	{ 
		return m_length;
	}
	
	std::ostream& operator<<(std::ostream& out, const string& str)
	{
		std::cout << str.m_data;

		return out;

		//переделать с использованием терминатора
	}

	_str::string& operator+(_str::string& str1, _str::string& str2)
	{
		////запрос памяти для новых данных
		//_str::string str;
		//str.m_length = (str1.m_length + str2.m_length); 
		//str.m_data = new char[str.m_length + 1];

		//int i = 0;

		_str::string tmp;
		tmp = std::move(str1);

		//чистка старых данных
		if (str1.m_data)
		{
			delete[] str1.m_data;
			str1.m_data = nullptr;
			str1.m_length = 0;
		}

		//запрос памяти для новых данных
		str1.m_length = str2.m_length + tmp.m_length;
		str1.m_data = new char[str1.m_length + 1];

		int i = 0;

		//копирование данных строки а
		for (int index = 0; index < tmp.m_length; i++, index++)
		{
			str1.m_data[i] = tmp.m_data[index];
		}

		//копирование данных строки б
		for (int index = 0; index < str2.m_length; index++, i++ )
		{
			str1.m_data[i] = str2.m_data[index];
		}

		//точка останова
		str1.m_data[str1.m_length] = '\0';

		//терминатор
		//вернуть ссылку
		return str1;
	}

	string::~string()
	{
		//проверка данных
		delete[] m_data;
		m_data = nullptr;
	}
}