#include "stdafx.h"
#include "BoyerMoore.h"
#include <iostream>
#include <algorithm>

void badSymbol(const string& needle, int badchar[SIZE])
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

vector<int> search(const string& str, const string& needle)
{
	string strCopy = str;
	string needleCopy = needle;
	std::transform(needleCopy.begin(), needleCopy.end(), needleCopy.begin(), ::tolower);
	std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(), ::tolower);

	vector<int> positions;

	int needleSize = needleCopy.size();
	int strSize = strCopy.size();

	if (needleSize == 0 || strSize == 0 || strSize < needleSize)
	{
		return positions;
	}

	int badchar[SIZE];

	badSymbol(needleCopy, badchar);

	int shift = 0;
	while (shift <= (strSize - needleSize))
	{
		int j = needleSize - 1;

		while (j >= 0 && needleCopy[j] == strCopy[shift + j])
		{
			j--;
		}

		if (j < 0)
		{
			positions.push_back(shift);
			shift += (shift + needleSize < strSize) ? needleSize - badchar[strCopy[shift + needleSize]] : 1;
		}

		else
		{
			shift += max(1, j - badchar[strCopy[shift + j]]);
		}
	}

	return positions;
}
