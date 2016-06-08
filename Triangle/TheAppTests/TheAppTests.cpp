// TheAppTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Lab2_mlita/Triangle.h"

BOOST_AUTO_TEST_SUITE(traingle_tests)

BOOST_AUTO_TEST_CASE(from_example)
{
	vector<vector<Node>> startMatrix = { {7, 0, 0, 0}, {3, 8, 0, 0}, {8, 1, 6, 0}, {4, 2, 3, 0} };
	auto workVec = startMatrix;
	ManipulateWithMatrix(startMatrix, 3);
	OutputResultToFile(startMatrix, workVec, 3);
	std::ifstream ifs1("output.txt.txt");
	std::ifstream ifs2("test/output.txt.txt");
	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(ifs2), e2;
	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_SUITE_END()
