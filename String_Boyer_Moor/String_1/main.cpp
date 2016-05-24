#include "stdafx.h"
#include "BoyerMoore.h"
#include "stringUtils.h"

int main()
{
	setlocale(LC_ALL, "");

	string str;
	string needle;
	vector<int> lineSizes;
	lineSizes.push_back(0);

	try
	{
		str = ReadFromFile(needle, lineSizes);
	}
	catch (const std::exception& error)
	{
		cout << error.what() << endl;
	}

	vector<int> findPos = search(str, needle);

	OutputPositions(findPos, lineSizes);

	return 0;
}
