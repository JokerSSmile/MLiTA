#pragma once

struct Node
{
	Node(short x = 0)
		:value(x)
	{

	}

	short value;
	pair<short, short> previousCell;
	pair<short, short> startValue;
};

vector<vector<Node>> ReadFromFile(ifstream& fin, unsigned lineCount);

void OutputResultToFile(const vector<vector<Node>>& matrix, unsigned lineCount);

void CalculatePathWithMaxWeight(vector<vector<Node>>& matrix, unsigned lineCount);
