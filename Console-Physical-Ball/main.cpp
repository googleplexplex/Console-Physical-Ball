#include "2DPhysObjects.hpp"
#include <iostream>

void inline eriseWindowsConsole()
{
	system("cls");
}
int main(void)
{
	alignMaxToWindowSize(); //��������� ������ ���� ��� ������ ���������
	ball firstBallObj;
	int delayValue = 10;
	firstBallObj.v.x = 50;
	ball secondBallObj({ max.x / 2, 0 }, { 10, 0});
	secondBallObj.strokePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

	while(true)
	{
		alignMaxToWindowSize(); //���� ������������ ������� ������ ���� - �������� � ����
		physTickAllObjects(); //���������� �������������� ���� �������� � ���������� � ������� ���������

		eriseWindowsConsole(); //����� ���� ��������
		showAllObjects();

		Sleep(1000 / frameInSec); //������������� ������
	}

	return 0;
}