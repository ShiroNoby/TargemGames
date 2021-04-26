#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>
#include <string.h>
#include <utility>

namespace _str
{
	
	class string
	{

		int m_length;
		char* m_data;

	public:

		//default empty constructor
		string();

		//constructor coppying
		string(const _str::string& str);

		//constructor coppying
		string(const char* data);

		//operator coppying
		void operator=(_str::string str);

		//move-operator
		void operator=(_str::string& str);


		friend std::ostream& operator<<(std::ostream& out, const string& str);

		//&
		friend _str::string& operator+(_str::string& str1, string& str2);
		
		
		//str.swap(str1)
		void swap(_str::string& str);

		int get_length() const;

		char& operator[](int index) const;

		~string();
	};
}

#endif _STRING_H_
