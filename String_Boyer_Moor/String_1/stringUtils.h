#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

std::string ReadFromFile(std::string& needle, std::vector<int>& lineSizes, const std::string& filename = "INPUT.txt");
void OutputPositions(const std::vector<int>& positions, const std::vector<int>& lineSizes);