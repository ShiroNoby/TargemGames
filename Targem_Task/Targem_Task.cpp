#include <iostream>
#include <vector>
#include <conio.h>
#include "string.h"

//nevermind
void swap(char& a, char& b)
{
	char tmp;
	tmp = a;
	a = b;
	b = tmp;
}

bool string_sort(const _str::string& str1, const _str::string& str2)
{
	for (int index = 0; index < str1.get_length(); index++)
	{
		if (str1[index] < str2[index]) { return true; }
	}
	return false;
}

//я не начинаю сортировку с vector[0], поскольку 0 элемен несет имя программы
void vector_sort(std::vector<_str::string>& vector)
{
	for (int i = 1; i < vector.size(); i++)
	{
		for (int j = i + 1; j < vector.size(); j++)
		{
			if (string_sort(vector[i], vector[j])) { vector[i].swap(vector[j]); }
		}
	}
}


int main(int argc, char* argv[])
{
	std::vector<_str::string> ArgVector;

	for (int i = 0; i < argc; i++) 
	{
		ArgVector.push_back(argv[i]);
	}

	vector_sort(ArgVector);

	for (int i = 1; i < argc; i++) 
	{
		std::cout << ArgVector[i] << std::endl;
	}
	
	_getch();
}