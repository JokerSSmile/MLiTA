#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void ShiftBM(const string& needle, char* stringSymbols, size_t* shiftValues)
{
	size_t needlePos;
	size_t pos = 0;
	bool flag;

	cout << "1" << endl;

	for (size_t i = needle.size() - 1; i > 0; i--)
	{
		flag = false;
		needlePos = 0;
		while ((needlePos < pos + 1) && (flag == false))
		{
			if (stringSymbols[needlePos] == needle[i])
			{
				flag = true;
			}
			needlePos++;
		}
		if (flag == false)
		{
			stringSymbols[pos] = needle[i];
			shiftValues[pos] = needle.size() - i - 1;
			pos++;
		}
	}

	cout << "2" << endl;
}

string BM(const string& needle, const string& str)
{
	char stringSymbols[256];
	size_t shiftValues[256];

	bool isSymbolInShiftTable;
	bool isSymbolInNeedle;

	size_t matchSymbolsCount;
	size_t needlePos;
	size_t strPos;

	ShiftBM(needle, stringSymbols, shiftValues); //fill shift values

	string nom = "";

	if (needle.size() > str.size() || needle.size() == 0 || str.size() == 0)
	{
		return nom;
	}

	for (strPos = 0; strPos < str.size() - needle.size() + 1; strPos++)
	{
		needlePos = needle.size() - 1;
		isSymbolInNeedle = true;
          
		while ((needlePos > 0) && (isSymbolInNeedle == true))
		{
			//Если не совпадает символ искомой и исходной
			if (str[strPos + needlePos] != needle[needlePos])
			{
				isSymbolInNeedle = false;
				//Если это последний символ
				if (needlePos == needle.size() - 1)
				{
					matchSymbolsCount = 0;
					isSymbolInShiftTable = false;
					while ((matchSymbolsCount < needle.size()) && (isSymbolInShiftTable == false))
					{
						//Если символ есть
						if (str[strPos + needlePos] == stringSymbols[matchSymbolsCount])
						{
							//Изменение флага
							isSymbolInShiftTable = true; 
							//Сдвиг на величину
							strPos = strPos + shiftValues[matchSymbolsCount] - 1;
						}
						matchSymbolsCount++;
					}
					//Если не найден символ в таблице смещений
					if (isSymbolInShiftTable == false)
						//Сдвиг на величину искомой строки
						strPos = strPos + needle.size() - 1;
				}
			}
			needlePos--;
		}
		if (isSymbolInNeedle == true)
			nom = nom + to_string(strPos) + " ";
	}
	if (nom.empty())
	{
		nom += "No.";
	}
	return nom;
}

int main()
{
	string str = "abbadabeccaabadbabbad";
	string strFind = "abbad";
	
	string kek = BM(strFind, str);

	cout << kek;
	return 0;
}
