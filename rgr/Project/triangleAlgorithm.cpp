#include "stdafx.h"
#include "triangleAlgorithm.h"

std::vector<std::vector<Node>> InitializeNodeMatrix(std::ifstream& fin, unsigned lineCount)
{
	std::vector<std::vector<Node>> matrix(lineCount + 1, std::vector<Node>(lineCount + 1));
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			fin >> matrix[i][k].value;
			matrix[i][k].startValue = matrix[i][k].value;
		}
	}

	return matrix;
}

void CalculatePathWithMaxWeight(std::vector<std::vector<Node> >& matrix, unsigned lineCount)
{
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			if (k == 0)
			{
				matrix[i][k].value += matrix[i - 1][k].value;
				matrix[i][k].previousCell = std::make_pair((short)i - 1, short(k));
			}
			else if (matrix[i - 1][k - 1].value > matrix[i - 1][k].value)
			{
				matrix[i][k].value += matrix[i - 1][k - 1].value;
				matrix[i][k].previousCell = std::make_pair((short)i - 1, (short)k - 1);
			}
			else
			{
				matrix[i][k].value += matrix[i - 1][k].value;
				matrix[i][k].previousCell = std::make_pair((short)i - 1, (short)k);
			}
		}
	}
}