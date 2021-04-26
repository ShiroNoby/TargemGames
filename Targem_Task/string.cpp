//� ��� �� ������� ��� � ��������� ����, �� �� ����
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
		
		//������ ������ ��� ����� ������
		this->m_length = str.m_length;
		this->m_data = new char[this->m_length + 1];

		//����������� ������
		for (int i = 0; i < str.m_length; i++)
		{
			this->m_data[i] = str.m_data[i];
		}

		//����� ��������
		this->m_data[m_length] = '\0';
		
		//��� ����-������
		//��� �� ������� �������?
	}

	//constructor coppying
	string::string(const char* data)
	{
		
		//������ ������ ��� ����� ������
		this->m_length = strlen(data);
		this->m_data = new char[strlen(data) + 1];

		//����������� ������
		for (int i = 0; i < m_length; i++)
		{
			this->m_data[i] = data[i];
		}

		//����� ��������
		this->m_data[m_length] = '\0';

		//��� ����-������
		//��� �� ������� �������?
	}

	//operator coppying
	void string::operator=(_str::string str)
	{
		//������ ������ ������
		if (this->m_data)
		{
			delete[] m_data;
			this->m_data = nullptr;
			this->m_length = 0;
		}

		//������ ������ ��� ����� ������
		this->m_length = str.m_length;
		this->m_data = new char[this->m_length + 1];

		//����������� ������
		for (int i = 0; i < str.m_length; i++)
		{
			this->m_data[i] = str.m_data[i];
		}

		//����� ��������
		this->m_data[m_length] = '\0';

		//��� ����-������
		//��� �� ������� �������?
	}

	//move-operator
	void string::operator=(_str::string& str)
	{
		//������ ������ ������
		if (this->m_data)
		{
			delete[] m_data;
			this->m_data = nullptr;
			this->m_length = 0;
		}

		//�������� ��������� � ������ ������
		this->m_length = str.m_length;
		this->m_data = str.m_data;;


		//������� ����������
		str.m_length = 0;
		str.m_data = nullptr;
	}

	//�� ��� �����?
	char& string::operator[](int index) const
	{
		return m_data[index];
	}

	//str.swap(str1)
	void string::swap(_str::string& str)
	{
		//��� ����� � ������� 

		//������ ��������
		_str::string tmp;
		
		//����������� ��������� ������ �������� ������ �
		tmp = std::move(*this);

		//����������� ������ � �������� ������ �
		*this = std::move(str);

		//����������� ������ � �������� �� ��������� ������
		str = std::move(tmp);
	}

	//������� ���
	int string::get_length() const
	{ 
		return m_length;
	}
	
	std::ostream& operator<<(std::ostream& out, const string& str)
	{
		std::cout << str.m_data;

		return out;

		//���������� � �������������� �����������
	}

	_str::string& operator+(_str::string& str1, _str::string& str2)
	{
		////������ ������ ��� ����� ������
		//_str::string str;
		//str.m_length = (str1.m_length + str2.m_length); 
		//str.m_data = new char[str.m_length + 1];

		//int i = 0;

		_str::string tmp;
		tmp = std::move(str1);

		//������ ������ ������
		if (str1.m_data)
		{
			delete[] str1.m_data;
			str1.m_data = nullptr;
			str1.m_length = 0;
		}

		//������ ������ ��� ����� ������
		str1.m_length = str2.m_length + tmp.m_length;
		str1.m_data = new char[str1.m_length + 1];

		int i = 0;

		//����������� ������ ������ �
		for (int index = 0; index < tmp.m_length; i++, index++)
		{
			str1.m_data[i] = tmp.m_data[index];
		}

		//����������� ������ ������ �
		for (int index = 0; index < str2.m_length; index++, i++ )
		{
			str1.m_data[i] = str2.m_data[index];
		}

		//����� ��������
		str1.m_data[str1.m_length] = '\0';

		//����������
		//������� ������
		return str1;
	}

	string::~string()
	{
		//�������� ������
		delete[] m_data;
		m_data = nullptr;
	}
}