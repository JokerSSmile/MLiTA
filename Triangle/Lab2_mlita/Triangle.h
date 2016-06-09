#pragma once

struct Node
{
	Node(short x = 0)
		:value(x)
	{

	}

	short value;
	short startValue;
	pair<short, short> previousCell;
};

vector<vector<Node>> ReadFromFile(ifstream& fin, unsigned lineCount);

void OutputResultToFile(const vector<vector<Node>>& matrix, unsigned lineCount);

void CalculatePathWithMaxWeight(vector<vector<Node>>& matrix, unsigned lineCount);
