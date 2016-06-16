#pragma once

class Node
{
public:
	Node() = default;
	short value;
	short startValue;
	std::pair<short, short> previousCell;
};

std::vector<std::vector<Node>> InitializeNodeMatrix(std::ifstream& fin, unsigned lineCount);

void CalculatePathWithMaxWeight(std::vector<std::vector<Node>>& matrix, unsigned lineCount);