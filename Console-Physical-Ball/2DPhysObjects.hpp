#pragma once
#include <Windows.h>
#include <climits>

struct DOUBLE_POINT
{
	double x, y;
};
#define GRAVITY_STANDART 10
double gravity = GRAVITY_STANDART;
DOUBLE_POINT max = { 400, 200 };
DOUBLE_POINT min = { 0, 0 };
DOUBLE_POINT standartSize = { 30, 30 };
HWND thisWindowHWND = GetForegroundWindow();
HDC thisWindowDC = GetDC(thisWindowHWND);
int frameInSec = 30;

class object
{
public:
	DOUBLE_POINT pos;
	DOUBLE_POINT v;
	DOUBLE_POINT a;
	DOUBLE_POINT size;
	virtual void physTick() = 0;
};
void standartPhysTick(object& physObj)
{
	physObj.v.x += physObj.a.x / frameInSec;
	physObj.v.y += physObj.a.y / frameInSec;

	if (physObj.pos.x + physObj.v.x > max.x)
		physObj.pos.x = max.x;
	else if (physObj.pos.x + physObj.v.x < min.x)
		physObj.pos.x = min.x;
	else
		physObj.pos.x += physObj.v.x;

	if (physObj.pos.y + physObj.v.y > max.y)
		physObj.pos.y = max.y;
	else if(physObj.pos.y + physObj.v.y < min.y)
		physObj.pos.y = min.y;
	else
		physObj.pos.y += physObj.v.y;
}

class ball : object
{
public:
	HBRUSH fillColor;
	HPEN strokeColor;
	ball()
	{
		a = { 0, gravity };
		v = { 0, 0 };
		pos = { max.x / 2, max.y / 2};
		size = standartSize;
		fillColor = CreateSolidBrush(RGB(255, 255, 255));
		strokeColor = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	}
	void show()
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(thisWindowDC, fillColor);
		HPEN oldPen = (HPEN)SelectObject(thisWindowDC, strokeColor);

		Ellipse(thisWindowDC, pos.x, pos.y, pos.x + size.x, pos.y + size.y);

		SelectObject(thisWindowDC, oldBrush);
		SelectObject(thisWindowDC, oldPen);

		DeleteObject(oldBrush);
		DeleteObject(oldPen);
	}
	void inline reDirectX()
	{
		v.x = -v.x;
	}
	void inline reDirectY()
	{
		v.y = -v.y;
	}
	void inline redirectWhenCollisionHappened()
	{
		if (pos.x == min.x || pos.x == max.x)
			reDirectX();
		if (pos.y == min.y || pos.y == max.y)
			reDirectY();
	}
	void physTick()
	{
		redirectWhenCollisionHappened();
		standartPhysTick(*this);
	}
};