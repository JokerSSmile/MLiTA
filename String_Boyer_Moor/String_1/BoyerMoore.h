#pragma once
#include <string>
#include <vector>

using namespace std;

const int SIZE = 256;

void badSymbol(const std::string&, int badchar[SIZE]);
vector<int> search(const std::string& str, const std::string& needle);
