#include <iostream>
#include <vector>
#include "string.h"

void vector_sort(std::vector<string::CString>& vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		for (int j = i + 1; j < vector.size(); j++)
		{
			if (vector[i] < vector[j]) { vector[i].swap(vector[j]); }
		}
	}
}

int main(int argc, char* argv[])
{
	std::vector<string::CString> ArgVector;

	while (std::cin)
	{
		char TMP_ch[120];
		std::cin.getline(TMP_ch, 120);

		if (TMP_ch[0] == '\0') { break; }

		string::CString str1(TMP_ch);
		ArgVector.push_back(std::move(str1));
	}

	vector_sort(ArgVector);

	for (int i = 0; i < ArgVector.size(); i++)
	{
		std::cout << ArgVector[i].c_str() << std::endl;
	}

	system("pause");
}