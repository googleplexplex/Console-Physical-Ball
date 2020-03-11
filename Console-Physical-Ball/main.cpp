#include "2DPhysObjects.hpp"

int main(void)
{
	ball ballObj;
	int delayValue = 10;

	while(true)
	{
		ballObj.physTick();
		Sleep(delayValue);
	}

	return 0;
}