// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
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

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

#define BOOST_TEST_MODULE TheAppTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable : 4202)
#include <boost/test/unit_test.hpp>