#pragma once
#include <string>
#include <vector>

using namespace std;

const int NO_OF_CHARS = 256;
static int helper[NO_OF_CHARS];

namespace BM
{
	void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]);
	vector<int> search(string txt, string pat);
}