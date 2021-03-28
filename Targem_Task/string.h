#ifndef _STRING_H_
#define _STRING_H_

namespace _str
{
	class string
	{
		int m_length = 0;
		char* m_data;

	public:

		string()
			:m_data(NULL) {}

		string(int length)
			:m_length(length)
		{
			if (length)
			{
				m_data = new char[m_length];
			}
		}



		string(const _str::string& str)
		{
			m_length = str.m_length;;

			m_data = new char[m_length];

			for (int i = 0; i < str.m_length; i++)
			{
				this->m_data[i] = str.m_data[i];
			}
		}

		string(const char* data)
		{

			m_length = strlen(data);

			m_data = new char[m_length];

			for (int i = 0; i < m_length; i++)
			{
				this->m_data[i] = data[i];
			}
		}

		friend std::ostream& operator<<(std::ostream& out, _str::string& str)
		{
			for (int i = 0; i < str.m_length; i++)
			{
				out << str.m_data[i];
			}
			return out;
		}

		void operator=(_str::string str)
		{
			if (this->m_length) { delete[] this->m_data; m_data = NULL; }

			this->m_length = str.m_length;
			m_data = new char[this->m_length];

			for (int i = 0; i < str.m_length; i++)
			{
				this->m_data[i] = str.m_data[i];
			}
		}


		friend _str::string operator+(_str::string& str1, _str::string& str2)
		{
			int size = str1.m_length + str2.m_length;

			_str::string str(size);

			for (int i = 0; i <= str1.m_length; i++)
			{
				str.m_data[i] = str1.m_data[i];
			}

			for (int i = str1.m_length, index = 0; i <= size; i++, index++)
			{
				str.m_data[i] = str2.m_data[index];
				str.m_length = i;
			}

			return str;
		}

		//str.swap(str1)
		void swap(_str::string& str)
		{
			_str::string tmp;
			tmp = *this;
			*this = str;;
			str = tmp;
		}

		int get() const { return m_length; }

		char operator[](int index) const
		{
			return m_data[index];
		}

		~string()
		{
			delete[] m_data;
			m_data = NULL;
		}

	};

}



#endif _STRING_H_
