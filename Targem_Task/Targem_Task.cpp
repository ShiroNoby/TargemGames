#include <iostream>
#include <fstream>
#include <utility>

#include <vector>
#include <conio.h>

#include <string.h>
#include "string.h"

//выбор принципа сотритовки
/*
#if HIGTH
#define OPERATOR >
#else
#define OPERATOR <
#endif HIGTH
*/

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
	//Писал для проверки строки
	/*
	std::string str;
	std::string str2{ "hello" };
	std::string str3 = { "hello" };
	std::string str4("hello");
	std::string str5 = str2 + str3 ;

	std::cout << '1' << ' ' << str2 << std::endl;
	std::cout << '2' << ' ' << str3 << std::endl;
	std::cout << '3' << ' ' << str4 << std::endl;
	std::cout << '4' << ' ' << str5 << std::endl;

	//вывод
	//	hello
	//	hello
	//	hello
	//	hellohello

	std::cout << std::endl;

	_str::string str_str;
	_str::string str_str2{ "hello"};
	_str::string str_str3 = { "hello" };
	_str::string str_str4("hello");
	_str::string str_str5 = str_str2 + str_str3;

	std::cout << '5' << ' ' << str_str2 << std::endl;
	std::cout << '6' << ' ' << str_str3 << std::endl;
	std::cout << '7' << ' ' << str_str4 << std::endl;
	std::cout << '8' << ' ' << str_str5 << std::endl;
	*/

	//это врожде пузырьковый метод
		//вымышленная реальность трактуетБ, что строки приходящие 
	//ну вот 100% не будут больше чем 2.147.483.647 знаков 
	//ну а додумаешься засунуть троку превышающую этот лимит пеняй на себя, я предупредил
	/*
	*
	* char array[15] = "hallo, wolrd!";
	*
	for (int i = 0; i < static_cast<int>(strlen(array)); i++)
	{
		for (int j = i + 1; j < static_cast<int>(strlen(array)); j++)
		{
			if (array[i] > array[j]) { swap(array[i], array[j]); }
		}
	}

	_str::string str = array;
	std::cout << str << std::endl;
	*/

	std::vector<_str::string> ArgVector;

	//buffers our string
	//запись в вектор параметров аргумента
	/*
	for (int i = 0; i < argc; i++)
	{
		ArgVector.push_back(argv[i]);
	}
	std::cout << std::endl;
	*/


	//input our string
	/*
	for (int i = 0; i < argc; i++)
	{
		std::cout << ArgVector[i] << std::endl;
	}
	std::cout << std::endl;
	*/

	//sort string
	//сравниваем поэлементно каждые строки
	/*
	vector_sort(ArgVector, argc);
	std::cout << std::endl;

	//input our string befor sorf
	for (int i = 0; i < argc; i++)
	{
		std::cout << ArgVector[i] << std::endl;
	}
	*/

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

		File.close();
	}

	//std::cout << std::endl;


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
	

	//проверка семантики
	/*
	char ara[] = "coppying me";

	std::cout << "array befor:" << std::endl;
	for (int i = 0; i < strlen(ara); i++)
	{
		std::cout << ara[i];
	}

	std::cout << std::endl;
	std::cout << std::endl;

	_str::string ara1(std::move(ara));


	std::cout << "array after:" << std::endl;
	for (int i = 0; i < strlen(ara); i++) 
	{
		std::cout << ara[i];
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "ara1 befor:" << std::endl;
	std::cout << ara1 << std::endl;
	std::cout << std::endl;

	_str::string ara2(std::move(ara1));

	std::cout << "ara1 after:" << std::endl;
	std::cout << ara1 << std::endl;
	std::cout << "ara2:" << std::endl;
	std::cout << ara2 << std::endl;
	*/

	/*
	//вывод 
		array befor:
		coppying me

		array after:
		coppying me

		ara1 befor:
		coppying me
		
		ara1 after:

		ra2:
		coppying me
	*/
	
	_getch();
}