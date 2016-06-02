#include "stdafx.h"
#include "BoyerMoore.h"
#include <iostream>
#include <algorithm>

void BadSymbol(const string& needle, short badchar[SIZE])
{
	size_t size = needle.size();

	for (size_t i = 0; i < SIZE; i++)
	{
		badchar[i] = -1;
	}

	for (size_t i = 0; i < size; i++)
	{
		badchar[needle[i]] = i;
	}
}

void Algorithm(const std::string& needle, const std::string& str, short badchar[SIZE], vector<int>& positions)
{
	int strSize = str.size();
	int needleSize = needle.size();
	int shift = 0;

	while (shift <= (strSize - needleSize))
	{
		int j = needleSize - 1;

		while (j >= 0 && needle[j] == str[shift + j])
		{
			j--;
		}

		if (j < 0)
		{
			positions.push_back(shift);
			shift += (shift + needleSize < strSize) ? needleSize - badchar[str[shift + needleSize]] : 1;
		}

		else
		{
			shift += max(1, j - badchar[str[shift + j]]);
		}
	}
}

vector<int> Search(const string& str, const string& needle)
{
	vector<int> positions;

	string strCopy = str;
	string needleCopy = needle;

	std::transform(needleCopy.begin(), needleCopy.end(), needleCopy.begin(), ::tolower);
	std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(), ::tolower);

	if (needleCopy.size() == 0 || strCopy.size() == 0 || strCopy.size() < needleCopy.size())
	{
		return positions;
	}

	short badchar[SIZE];

	BadSymbol(needleCopy, badchar);
	Algorithm(needleCopy, strCopy, badchar, positions);

	return positions;
}
