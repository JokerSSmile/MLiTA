#include "stdafx.h"
#include "Triangle.h"

//////////////////////////////////////////////////////////////////////////
//
//4.2.�����������(5)
//
//����� ���������� ����� �����,
//������������� �� ���� �� ������� ����� ������������ �� ���������.
//������ ��� �� ���� ���������� � ����������� ���� �� ���������(����� ��� ������).�����
//����� � ������������ �� 1 �� 100. ����������� ��������� �� ����� ����� �� 0 �� 99.
//���� �� ����� INPUT.TXT.������ ����� ���������� ���������� ����� ������������ N
//����� � ���� OUTPUT.TXT.� ������ ������ ��������� ������������ ����� � ����������
//�����.�� ������ ������ �������� ����� ������ ����� �� ������� ������������ �� ���������,
//������ ���������� �����.���� ������� ���������, ������� ����� �� ���.
//
//////////////////////////////////////////////////////////////////////////

int main()
{

	ifstream fin("input.txt");

	unsigned lineCount = 0;
	fin >> lineCount;

	vector<vector<Node>> matrix = ReadFromFile(fin, lineCount);

	CalculatePathWithMaxWeight(matrix, lineCount);

	OutputResultToFile(matrix, lineCount);
	
    return 0;
}

