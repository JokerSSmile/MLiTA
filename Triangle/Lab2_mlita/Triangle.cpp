#include "stdafx.h"
#include "Triangle.h"

vector<vector<Node>> ReadFromFile(ifstream& fin, const unsigned& lineCount)
{
	vector<vector<Node>> matrix(lineCount + 1, vector<Node>(lineCount + 1));
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			fin >> matrix[i][k].value;
		}
	}

	return matrix;
}

void OutputResultToFile(const vector<vector<Node>>& startMatrix, const vector<vector<Node>>& matrix, const unsigned& lineCount)
{
	short maximum = 0;
	pair<short, short> previous;
	ofstream fout("output.txt");

	for (size_t i = 0; i < lineCount + 1; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			if (matrix[i][k].value > maximum)
			{
				maximum = matrix[i][k].value;
				previous = std::pair<short, short>((short)i, (short)k);
			}
		}
	}

	fout << maximum << endl;
	while (previous.first != 0)
	{
		fout << startMatrix[previous.first][previous.second].value << " ";
		previous = matrix[previous.first][previous.second].previousCell;
	}
}

void ManipulateWithMatrix(vector<vector<Node>>& matrix, const unsigned& lineCount)
{
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			if (k == 0)
			{
				if (i > 1)
				{
					matrix[i][k].value = matrix[i][k].value + matrix[i - 1][k].value;
					matrix[i][k].previousCell = make_pair((short)i - 1, short(k));
				}
			}
			else
			{
				if (k == i)
				{
					matrix[i][k].value = matrix[i][k].value + matrix[i - 1][k - 1].value;
					matrix[i][k].previousCell = make_pair((short)i - 1, (short)k - 1);
				}
				else
				{
					matrix[i][k].value = matrix[i][k].value + max(matrix[i - 1][k - 1].value, matrix[i - 1][k].value);
					if (matrix[i - 1][k - 1].value > matrix[i - 1][k].value)
					{
						matrix[i][k].previousCell = make_pair((short)i - 1, (short)k - 1);
					}
					else
					{
						matrix[i][k].previousCell = make_pair((short)i - 1, (short)k);
					}
				}
			}
		}
	}
}


/////////////////////////// Debug tool //////////////////////////////////
//void OutputMatrix(const vector<vector<Node>>& matrix, const unsigned& lineCount)
//{
//	for (size_t i = 0; i < lineCount + 1; i++)
//	{
//		for (size_t k = 0; k < i; k++)
//		{
//			cout << matrix[i][k].value << '\t';
//		}
//		cout << endl;
//	}
//}
//////////////////////////////////////////////////////////////////////////
