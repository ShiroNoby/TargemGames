#include <iostream>
#include <fstream>
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
	for (int index = 0; index < str1.get(); index++)
	{
		if (str1[index] < str2[index]) { return true; }
	}
	return false;
}

//я не начинаю сортировку с vector[0], поскольку 0 элемен несет имя программы
void vector_sort(std::vector<_str::string>& vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		for (int j = i + 1; j < vector.size(); j++)
		{
			if (string_sort(vector[i], vector[j])) { vector[i].swap(vector[j]); }
		}
	}
}

//пишем построчно из файла в вектор
void BUFFER(std::ifstream& File, std::vector<_str::string>& vector)
{
	char* buff = new char[32767];
	for (int index = 0; !File.eof(); index++)
	{
		File.getline(buff, 32767, '\n');
		vector.push_back(buff);
	}
	delete[] buff;
}

void createFile(std::vector<_str::string>& vector, std::ofstream& File)
{
	for (int i = 0; i < vector.size(); i++)
	{
		File << vector[i] << std::endl;
	}
}

int main(int argc, char* argv[])
{
	
	std::vector<_str::string> ArgVector;

	
	//основной блок
	std::ifstream File("input.txt");
	if (File.is_open())
	{
		std::cout << "file is open" << std::endl;

		BUFFER(File, ArgVector);

		for (int i = 0; i < ArgVector.size(); i++)
		{
			std::cout << ArgVector[i] << std::endl;
		}
		std::cout << std::endl;
	}
	File.close();

	//sort string
	//сравниваем поэлементно каждые строки
	vector_sort(ArgVector);
	std::cout << std::endl;


	for (int i = 0; i < ArgVector.size(); i++)
	{
		std::cout << ArgVector[i] << std::endl;
	}
	std::cout << std::endl;

	std::ofstream buff("output.txt");

	if (buff.is_open())
	{
		createFile(ArgVector, buff);
	}
	buff.close();
	
	_getch();
}