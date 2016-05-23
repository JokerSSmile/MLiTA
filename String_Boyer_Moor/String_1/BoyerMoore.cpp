#include "stdafx.h"
#include "BoyerMoore.h"
#include <iostream>
#include <array>

namespace BM
{
	void Shift(const string& needle, char* stringSymbols, int* shiftValues)
	{
		
		int needlePos;
		int pos = 0;
		bool isExist;

		for (int i = needle.size() - 1; i >= 0; i--)
		{
			isExist = false;
			needlePos = 0;
			while ((needlePos < pos + 1) && (isExist == false))
			{

				if (stringSymbols[needlePos] == needle[i])
				{
					isExist = true;
				}
				needlePos++;
			}
			if (isExist == false)
			{
				//cout << needle[needlePos] << endl;
				stringSymbols[pos] = needle[i];
				shiftValues[pos] = needle.size() - i - 2;
				pos++;
			}
		}

		for (int i = 0; i < 10; i++)
		{
			cout << stringSymbols[i] << " " << shiftValues[i] << endl;
		}
	}

	vector<int> Alghorithm(const string& needle, const string& str)
	{
		char stringSymbols[256];
		int shiftValues[256] = { needle.size() };

		bool isSymbolInShiftTable;
		bool isSymbolInNeedle;

		int matchSymbolsCount;
		int strPos;
		int needlePos;

		Shift(needle, stringSymbols, shiftValues);

		vector<int> positions;

		if (needle.size() > str.size() || needle.size() == 0 || str.size() == 0)
		{
			return positions;
		}

		for (strPos = 0; strPos < str.size() - needle.size() + 1; strPos++)
		{
			needlePos = needle.size() - 1;
			isSymbolInNeedle = true;

			while ((needlePos >= 0) && (isSymbolInNeedle == true))
			{
				if (str[strPos + needlePos] != needle[needlePos])
				{	
					isSymbolInNeedle = false;
					if (needlePos == needle.size() - 1)
					{
						matchSymbolsCount = 0;
						isSymbolInShiftTable = false;
						while ((matchSymbolsCount < needle.size()) && (isSymbolInShiftTable == false))
						{
							if (str[strPos + needlePos] == stringSymbols[matchSymbolsCount])
							{						
								isSymbolInShiftTable = true;
								strPos += shiftValues[matchSymbolsCount] - 1;
							}
							matchSymbolsCount++;
						}
						if (isSymbolInShiftTable == false)
							strPos = strPos + needle.size() - 1;
					}
				}
				needlePos--;
			}
			if (isSymbolInNeedle == true)
			{
				positions.push_back(strPos);
			}
		}

		return positions;
	}
}