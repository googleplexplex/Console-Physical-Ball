#pragma once
#include <Windows.h>
#include <climits>
#include <list>
#include <math.h>

struct DOUBLE_POINT
{
	double x, y;
};
#define GRAVITY_STANDART 10
#define sqr(x) ((x)*(x))
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
	unsigned int m;
	double S;
	virtual void physTick() = 0;
	virtual DOUBLE_POINT getCenter() = 0;
	virtual void show() = 0;
};
void standartPhysTick(object& physObj)
{
	physObj.v.x += physObj.a.x / frameInSec;
	physObj.v.y += physObj.a.y / frameInSec + physObj.m * gravity;

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
std::list<object*> allObjectsList;

class ball : public object
{
public:
	HBRUSH fillBrush;
	HPEN strokePen;
	ball(DOUBLE_POINT _pos = { max.x / 2, max.y / 2 }, DOUBLE_POINT _v = { 0, 0 }, DOUBLE_POINT _a = { 0, 0 }, DOUBLE_POINT _size = standartSize, COLORREF _fillColor = RGB(255, 255, 255), COLORREF _strokeColor = RGB(255, 0, 0), int strokePenWidth = 2, unsigned int _m = 5)
	{
		pos = _pos;
		v = _v;
		a = _a;
		size = _size;
		fillBrush = CreateSolidBrush(_fillColor);
		strokePen = CreatePen(PS_SOLID, strokePenWidth, _strokeColor);
		m = _m;
		S = size.x * size.x * 3.14;

		allObjectsList.push_back(this);
	}
	DOUBLE_POINT inline getCenter()
	{
		double halfOfSize = size.x / 2;
		return { pos.x + halfOfSize, pos.y + halfOfSize };
	}
	void show()
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(thisWindowDC, fillBrush);
		HPEN oldPen = (HPEN)SelectObject(thisWindowDC, strokePen);

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

void physTickAllObjects()
{
	for (std::list<object*>::iterator i = allObjectsList.begin(); i != allObjectsList.end(); i++)
	{
		(*i)->physTick();
	}
}
void alignMaxToWindowSize()
{
	RECT tempRect = { 0 };
	GetWindowRect(thisWindowHWND, &tempRect);
	max.x = tempRect.right - tempRect.left;
	max.y = tempRect.bottom - tempRect.top - 70;
}
void inline showAllObjects()
{
	for (std::list<object*>::iterator i = allObjectsList.begin(); i != allObjectsList.end(); i++)
	{
		(*i)->show();
	}
}