#pragma once
#include <string>
#include <vector>

using namespace std;


namespace BM
{
	void Shift(const string& needle, char* stringSymbols, int* shiftValues);
	vector<int> Alghorithm(const string& needle, const string& str);
}