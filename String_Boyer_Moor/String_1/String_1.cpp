#include "stdafx.h"
#include "BoyerMoore.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ReadFromFile(string& needle, string& str, vector<int>& lineSizes)
{	
	ifstream fin("INPUT.txt");
	if (!fin.is_open())
	{
		throw std::ifstream::failure("Can not open file <input.txt>");
	}

	string strFilename;
	getline(fin, needle);
	fin >> strFilename;

	ifstream stringFin(strFilename);
	if (!stringFin.is_open())
	{
		throw std::ifstream::failure("Can not open file with string");
	}
	
	string currentLine;
	while (getline(stringFin, currentLine))
	{
		lineSizes.push_back(currentLine.size() + lineSizes.back() + 1);
		str += currentLine + " ";
	}

}

void OutputPositions(const vector<int>& positions, const vector<int>& lineSizes, string str)
{
	ofstream fout("OUTPUT.txt");
	
	for (size_t i = 0; i < positions.size(); i++)
	{
		int k = 1;
		
		while (positions[i] > lineSizes[k])
		{
			k++;
		}

		fout << k << " " << positions[i] + 1 << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	string str;
	string needle;
	vector<int> lineSizes;
	lineSizes.push_back(0);

	try
	{
		ReadFromFile(needle, str, lineSizes);
	}
	catch (const std::exception& error)
	{
		cout << error.what() << endl;
	}

	vector<int> kek = BM::Alghorithm(needle, str);

	for (auto i : kek)
	{
		//cout << i << " " << str[i] << endl;
	}

	OutputPositions(kek, lineSizes, str);

	return 0;
}
