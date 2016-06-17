#pragma once

struct Node
{
	short value;
	short startValue;
	Vector2u previousCell;
};

std::vector<std::vector<Node>> InitializeNodeMatrix(std::ifstream& fin, unsigned lineCount);

Vector2u CalculatePathWithMaxWeight(std::vector<std::vector<Node>>& matrix, unsigned lineCount, const sf::Vector2u& position);

Vector2u FindMaxValuePosition(const std::vector<std::vector<Node>>& matrix, unsigned lineCount);