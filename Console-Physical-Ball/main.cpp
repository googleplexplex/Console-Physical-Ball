#include "2DPhysObjects.hpp"
#include <iostream>

void inline eriseWindowsConsole()
{
	system("cls");
}
int main(void)
{
	ball ballObj;
	int delayValue = 10;
	ballObj.v.x = 50;

	RECT tempRect = { 0 };
	while(true)
	{
		GetWindowRect(thisWindowHWND, &tempRect);
		max.x = tempRect.right - tempRect.left;
		max.y = tempRect.bottom - tempRect.top - 70; //Динамически подстраиваемся под размер

		ballObj.physTick();
		eriseWindowsConsole();
		ballObj.show();
		Sleep(1000 / frameInSec);
	}

	return 0;
}