#include "stdafx.h"
#include "stringUtils.h"

using namespace std;

std::string ReadFromFile(std::string& needle, std::vector<int>& lineSizes, const std::string& filename)
{	

	std::string str;

	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		throw std::ifstream::failure("Can not open file <input.txt>");
	}

	std::string strFilename;
	getline(fin, needle);
	fin >> strFilename;

	std::ifstream stringFin(strFilename);
	if (!stringFin.is_open())
	{
		throw std::ifstream::failure("Can not open file with string");
	}
	
	std::string currentLine;
	while (getline(stringFin, currentLine))
	{
		lineSizes.push_back(currentLine.size() + lineSizes.back() + 1);
		str += currentLine + " ";
	}

	return str;
};

void OutputPositions(const std::vector<int>& positions, const std::vector<int>& lineSizes)
{
	std::ofstream fout("OUTPUT.txt");
	
	if (positions.size() > 0)
	{
		for (size_t i = 0; i < positions.size(); i++)
		{
			int k = 0;

			do
			{
				k++;
			} while (positions[i] > lineSizes[k]);

			fout << k << " " << positions[i] - lineSizes[k - 1] + 1 << endl;
		}
	}
	else
	{
		fout << "No." << endl;
	}
};
