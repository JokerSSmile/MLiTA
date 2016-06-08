#pragma once

struct Node
{
	Node(short x = 0)
		:value(x)
	{

	}

	short value;
	pair<short, short> previousCell;
};

vector<vector<Node>> ReadFromFile(ifstream& fin, const unsigned& lineCount);

void OutputResultToFile(const vector<vector<Node>>& startMatrix, const vector<vector<Node>>& matrix, const unsigned& lineCount);

void ManipulateWithMatrix(vector<vector<Node>>& matrix, const unsigned& lineCount);
