// TheAppTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Lab2_mlita/Triangle.h"

void CompareGivenAndExpectedFiles(ifstream& fin, ifstream& resultFile)
{
	short lineCount;
	fin >> lineCount;
	vector<vector<Node>> startMatrix = ReadFromFile(fin, lineCount);
	CalculatePathWithMaxWeight(startMatrix, lineCount);
	OutputResultToFile(startMatrix, lineCount);
	std::ifstream ifs1("output.txt");
	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(resultFile), e2;
	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

BOOST_AUTO_TEST_SUITE(traingle_tests)

BOOST_AUTO_TEST_CASE(from_example)
{
	ifstream finIn("test/input.txt");
	ifstream finOut("test/output.txt");
	CompareGivenAndExpectedFiles(finIn, finOut);
}

BOOST_AUTO_TEST_CASE(if_empty)
{
	ifstream finIn("test/input1.txt");
	ifstream finOut("test/output1.txt");
	CompareGivenAndExpectedFiles(finIn, finOut);
}

BOOST_AUTO_TEST_CASE(ten_size_vector)
{
	ifstream finIn("test/input2.txt");
	ifstream finOut("test/output2.txt");
	CompareGivenAndExpectedFiles(finIn, finOut);
}

BOOST_AUTO_TEST_SUITE_END()
