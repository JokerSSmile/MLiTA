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

Vector2u CalculatePathWithMaxWeight(std::vector<std::vector<Node>>& matrix, unsigned lineCount, const sf::Vector2u& position)
{
	if (position.y == 0)
	{
		matrix[position.x][position.y].value += matrix[position.x - 1][position.y].value;
		matrix[position.x][position.y].previousCell = { position.x - 1, position.y };
		return {position.x - 1, position.y};
	}
	else if (matrix[position.x - 1][position.y - 1].value > matrix[position.x - 1][position.y].value)
	{
		matrix[position.x][position.y].value += matrix[position.x - 1][position.y - 1].value;
		matrix[position.x][position.y].previousCell = { position.x - 1, position.y - 1 };
		return { position.x - 1, position.y - 1 };
	}
	else
	{
		matrix[position.x][position.y].value += matrix[position.x - 1][position.y].value;
		matrix[position.x][position.y].previousCell = { position.x - 1, position.y };
		return { position.x - 1, position.y };
	}

}

Vector2u FindMaxValuePosition(const std::vector<std::vector<Node>>& matrix, unsigned lineCount)
{
	Vector2u position;
	int maximum = 0;
	for (size_t i = 0; i < lineCount + 1; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			if (matrix[i][k].value > maximum)
			{
				maximum = matrix[i][k].value;
				position = { i, k };
			}
		}
	}

	return position;
}