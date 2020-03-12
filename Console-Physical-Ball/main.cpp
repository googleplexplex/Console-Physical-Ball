#include "2DPhysObjects.hpp"

void inline eriseWindowsConsole()
{
	system("cls");
}
int main(void)
{
	ball ballObj;
	int delayValue = 10;

	while(true)
	{
		ballObj.physTick();
		eriseWindowsConsole();
		ballObj.show(); //Очищаем, и сразу выводим снова. В угоду отсутвия мерцания
		Sleep(1000 / frameInSec);
	}

	return 0;
}