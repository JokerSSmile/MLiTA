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

