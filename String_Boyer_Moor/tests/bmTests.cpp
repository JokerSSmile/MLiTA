#include "stdafx.h"
#include "..\String_1\BoyerMoore.h"
#include "..\String_1\stringUtils.h"

BOOST_AUTO_TEST_SUITE(alghorithm_tests)

BOOST_AUTO_TEST_CASE(no_findings_if_empty_strings_given)
{
	std::string emptyStr;
	std::string emptyNeedle;
	std::vector<int> result = search(emptyStr, emptyNeedle);
	BOOST_CHECK(result.size() == 0);
}

BOOST_AUTO_TEST_CASE(correct_result_if_only_one_needle_at_start_position_in_string)
{
	std::string str = "asd";
	std::string needle = "asd";
	std::vector<int> result = search(str, needle);
	std::vector<int> correct = { 0 };
	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), correct.begin(), correct.end());
}

BOOST_AUTO_TEST_CASE(correct_result_if_different_letter_case_string)
{
	std::string str = "asd Asd aSd asD ASD";
	std::string needle = "asd";
	std::vector<int> result = search(str, needle);
	std::vector<int> correct = { 0, 4, 8, 12, 16 };
	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), correct.begin(), correct.end());
}

BOOST_AUTO_TEST_CASE(correct_result_if_needle_string_is_on_2_lines_in_given_file)
{
	std::string str = "mama mila ramu vchera, mama ";
	str += "mila ramu segodnya";
	std::string needle = "mama mila ramu";
	std::vector<int> result = search(str, needle);
	std::vector<int> correct = { 0, 23 };
	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), correct.begin(), correct.end());
}

BOOST_AUTO_TEST_SUITE_END()