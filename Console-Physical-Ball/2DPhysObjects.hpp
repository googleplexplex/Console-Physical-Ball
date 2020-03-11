#pragma once
#include <Windows.h>
#include <climits>

#define GRAVITY_STANDART 10
int gravity = GRAVITY_STANDART;
POINT max = { 940, 480 };
POINT min = { 0, 0 };

class object
{
public:
	POINT pos;
	POINT v;
	POINT a;
	virtual void physTick() = 0;
};
void standartPhysTick(object &physObj)
{
	physObj.a.y += gravity;
	physObj.v.x += physObj.a.x;
	physObj.v.y += physObj.a.y;
	physObj.pos.x += physObj.v.x;
	physObj.pos.y += physObj.v.y;
}

class ball : object
{
public:
	ball()
	{
		a = v = { 0, 0 };
		pos = { max.x / 2, max.y / 2};
	}
	void show()
	{
		//TODO
	}
	void inline reDirectX()
	{
		v.x = -v.x;
	}
	void inline reDirectY()
	{
		v.y = -v.y;
	}
	void redirectWhenCollisionHappened()
	{
		if (pos.x < min.x || pos.x > max.x)
			reDirectX();
		if (pos.y < min.y || pos.y > max.y)
			reDirectY();
	}
	void physTick()
	{
		redirectWhenCollisionHappened();
		standartPhysTick(*this);
	}
};