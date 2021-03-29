#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>
#include <string.h>
#include <utility>

namespace _str
{
	
	class string
	{
		int m_length = 0;
		char* m_data;

	public:

		//default empty constructor
		string();

		//default constructor
		string(int length);


		//constructor coppying
		string(const _str::string& str);

		//constructor coppying
		string(const char* data);

		//move-constuctor
		string(_str::string&& str);

		//operator coppying
		void operator=(_str::string& str);

		//move-operator
		void operator=(_str::string&& str);


		friend std::ostream& operator<<(std::ostream& out, const string& str);

		friend _str::string	operator+(_str::string& str1, string& str2);
		
		
		//str.swap(str1)
		void swap(_str::string& str);

		int get() const;

		char& operator[](int index) const;

		~string();
	};
}

#endif _STRING_H_
