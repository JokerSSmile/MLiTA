// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

#define BOOST_TEST_MODULE TheAppTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable : 4202)
#include <boost/test/unit_test.hpp>