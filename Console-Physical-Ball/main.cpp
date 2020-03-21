#include "2DPhysObjects.hpp"
#include <iostream>

void inline eriseWindowsConsole()
{
	system("cls");
}
int main(void)
{
	alignMaxToWindowSize(); //Сохраняем размер окна при старте программы
	ball firstBallObj;
	int delayValue = 10;
	firstBallObj.v.x = 50;
	ball secondBallObj({ max.x / 2, 0 }, { 10, 0});
	secondBallObj.strokePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

	while(true)
	{
		alignMaxToWindowSize(); //Если пользователь изменил размер окна - сообщаем о этом
		physTickAllObjects(); //Физическое взаимодействие всех объектов с окружением и другими объектами

		eriseWindowsConsole(); //Вывод всех объектов
		showAllObjects();

		Sleep(1000 / frameInSec); //Синхронизация кадров
	}

	return 0;
}