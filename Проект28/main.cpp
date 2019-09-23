#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <atltypes.h>

HWND hWnd = GetForegroundWindow();

POINT getWindowPos()
{
	POINT ret;
	CRect rect;
	GetWindowRect(hWnd, rect);
	ret.x = rect.left;
	ret.y = rect.top + 30 + 1;
	return ret;
}

#define RED RGB(255,0,0)

#define seconds(miliseconds) (miliseconds * 1000)
#define every(element, _seconds) for(int element = 0;;element++){Sleep(seconds(_seconds));
#define end }
#define every(element, _seconds, _code) for(int element = 0;;i++){_code Sleep(seconds(_seconds));}
#define point POINT
#define clear system("cls")

#define gravitation true
#define speed 0.01

point max = { 940, 480 };
point min = { 0, 0 };
int devis = 2;
int gravityPower = 9.8;

POINT getPower()
{
	POINT pastPosition = getWindowPos();
	Sleep(seconds(1));
	POINT presentPosition = getWindowPos();

	return { pastPosition.x - presentPosition.x, pastPosition.y - presentPosition.y };
}


class Object
{
public:
	point position = { 0, 0 };
	point size = { 0, 0 };
	point power = { 0, 0 };
	int mass = 0;

	Object(int xpos, int ypos, int xsize, int ysize)
	{
		position.x = xpos;
		position.y = ypos;
		size.x = xsize;
		size.y = ysize;
	}

	Object(int xpos, int ypos, int xsize, int ysize, int _mass)
	{
		position.x = xpos;
		position.y = ypos;
		size.x = xsize;
		size.y = ysize;
		mass = _mass;
	}

	void alife()
	{
		if (power.x > 0)
		{
			if (position.x < max.x)
			{
				power.x -= power.x / devis / 2;
				position.x += power.x / devis;

				if (position.x >= max.x)
					position.x = max.x;
			}
			else {
				power.x = -power.x;
			}
		}
		else if (power.x < 0)
		{
			if (position.x > min.x + size.x)
			{
				power.x -= power.x / devis / 2;
				position.x += power.x / devis;

				if (position.x <= min.x + size.x)
					position.x = min.x + size.x;
			}
			else {
				power.x = -power.x;
			}
		}

		if (power.y > 0)
		{
			if (position.y > min.y + size.y)
			{
				power.y -= power.y / devis;
				position.y -= power.y / devis;

				if (position.y <= min.y + size.y)
					position.y = min.y + size.y;
			}
			else {
				power.y = -power.y + mass + gravityPower;
			}
		}
		else if (power.y < 0)
		{
			if (position.y < max.y)
			{
				power.y += power.y / devis;
				position.y -= power.y / devis;

				if (position.y >= max.y)
					position.y = max.y;
			}
			else {
				power.y = -power.y - mass - gravityPower;
			}
		}

		punch(0, -gravityPower - mass);
	}

	void punch(int px, int py)
	{
		power.x += px;
		power.y += py;
	}

	void show(HDC _hDC)
	{
		Ellipse(_hDC, position.x - size.x, position.y + size.y, position.x + size.x, position.y - size.y);
	}
};

int main(int argc, char *argv[])
{
	COORD P = { 0 };
	RECT pRECT = { 0 };
	GetClientRect(hWnd, &pRECT);
	HPEN RPEN = CreatePen(PS_SOLID, 2, RED);
	HDC hDC = GetWindowDC(hWnd);
	SetBkMode(hDC, TRANSPARENT);
	P.X = 100;
	P.Y = 100;
	EXTLOGPEN pINFO;
	GetObject(RPEN, sizeof(EXTLOGPEN), &pINFO);
	SelectObject(hDC, RPEN);

	Object ellipse(P.X, P.Y, 30, 30, 0);
	ellipse.punch(500, 0);

	every(i, speed,
		ellipse.alife();
		clear;
		ellipse.show(hDC);
	)

	return 0;

}