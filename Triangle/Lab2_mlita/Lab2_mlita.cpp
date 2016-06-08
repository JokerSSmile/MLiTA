#include "stdafx.h"
#include "Triangle.h"

//////////////////////////////////////////////////////////////////////////
//
//4.2.Треугольник(5)
//
//Найти наибольшую сумму чисел,
//расположенных на пути из верхней точки треугольника до основания.
//Каждый шаг на пути происходит в направлении вниз по диагонали(влево или вправо).Число
//строк в треугольнике от 1 до 100. Треугольник составлен из целых чисел от 0 до 99.
//Ввод из файла INPUT.TXT.Первое число определяет количество строк треугольника N
//Вывод в файл OUTPUT.TXT.В первой строке выводится единственное число – наибольшая
//сумма.Во второй строке выдаются через пробел числа от вершины треугольника до основания,
//дающие наибольшую сумму.Если решений несколько, вывести любое из них.
//
//////////////////////////////////////////////////////////////////////////

int main()
{

	ifstream fin("input.txt");

	string line;

	unsigned lineCount = 0;
	unsigned inLinePos = 1;
	fin >> lineCount;

	vector<vector<Node>> startMatrix;

	startMatrix = ReadFromFile(fin, lineCount);
	vector<vector<Node>> workMatrix(startMatrix);

	ManipulateWithMatrix(workMatrix, lineCount);

	OutputResultToFile(startMatrix, workMatrix, lineCount);
	
    return 0;
}

