#include "2DPhysObjects.hpp"

void inline eriseWindowsConsole()
{
	system("cls");
}
int main(void)
{
	ball ballObj;
	int delayValue = 10;

	RECT tempRect = { 0 };
	while(true)
	{
		GetWindowRect(thisWindowHWND, &tempRect);
		max.x = tempRect.right - tempRect.left;
		max.y = tempRect.bottom - tempRect.top - 70; //����������� �������������� ��� ������

		ballObj.physTick();
		eriseWindowsConsole();
		ballObj.show(); //�������, � ����� ������� �����. � ����� �������� ��������
		Sleep(1000 / frameInSec);
	}

	return 0;
}