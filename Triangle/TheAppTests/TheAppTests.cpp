// TheAppTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Lab2_mlita/Triangle.h"

BOOST_AUTO_TEST_SUITE(traingle_tests)

BOOST_AUTO_TEST_CASE(if_empty)
{
	vector<vector<Node>> startMatrix = { };
	CalculatePathWithMaxWeight(startMatrix, 0);
	OutputResultToFile(startMatrix, 0);
	std::ifstream ifs1("output.txt.txt");
	std::ifstream ifs2("test/output1.txt.txt");
	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(ifs2), e2;
	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_CASE(from_example)
{
	vector<vector<Node>> startMatrix = { {7, 0, 0, 0}, {3, 8, 0, 0}, {8, 1, 6, 0}, {4, 2, 3, 0} };
	CalculatePathWithMaxWeight(startMatrix, 3);
	OutputResultToFile(startMatrix, 3);
	std::ifstream ifs1("output.txt.txt");
	std::ifstream ifs2("test/output.txt.txt");
	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(ifs2), e2;
	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_CASE(ten_size_vector)
{
	vector<vector<Node>> startMatrix = { { 8, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 8, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 8, 8, 7, 0, 0, 0, 0, 0, 0, 0 },
			{ 8, 1, 8, 8, 0, 0, 0, 0, 0, 0 },
			{ 8, 5, 8, 8, 8, 0, 0, 0, 0, 0 },
			{ 8, 8, 8, 8, 8, 8, 0, 0, 0, 0 },
			{ 8, 8, 6, 8, 8, 3, 8, 0, 0, 0 },
			{ 8, 8, 8, 8, 8, 8, 2, 8, 0, 0 }, 
			{ 8, 7, 8, 8, 8, 8, 0, 8, 8, 0 }, 
			{ 8, 8, 8, 8, 8, 8, 1, 8, 8, 8 } };
	CalculatePathWithMaxWeight(startMatrix, 9);
	OutputResultToFile(startMatrix, 9);
	std::ifstream ifs1("output.txt.txt");
	std::ifstream ifs2("test/output2.txt.txt");
	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(ifs2), e2;
	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_SUITE_END()
