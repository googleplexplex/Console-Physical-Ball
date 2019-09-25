#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <atltypes.h>

#define RED RGB(255,0,0)

#define seconds(miliseconds) (miliseconds * 1000)
#define every(element, _seconds) for(int element = 0;;element++){Sleep(seconds(_seconds));
#define end }
#define every(element, _seconds, _code) for(int element = 0;;i++){_code Sleep(seconds(_seconds));}
#define point POINT
#define clear system("cls")

#define gravitation true
#define speed 0.01

HWND hWnd = GetForegroundWindow();
COORD P = { 100, 100 };
RECT pRECT = { 0 };
HPEN RPEN = CreatePen(PS_SOLID, 2, RED);
HDC hDC = GetWindowDC(hWnd);
EXTLOGPEN pINFO;

point max = { 940, 480 };
point min = { 0, 0 };
int devis = 2;
int gravityPower = 9.8;

POINT getWindowPos()
{
	POINT ret;
	CRect rect;
	GetWindowRect(hWnd, rect);
	ret.x = rect.left;
	ret.y = rect.top + 30 + 1;
	return ret;
}


class Object
{
public:
	point position = { 0, 0 };
	point size = { 0, 0 };
	point power = { 0, 0 };
	int mass = 0;
	bool upWallCollision = false;
	bool downWallCollision = false;
	bool leftWallCollision = false;
	bool rightWallCollision = false;

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
private:
	void falseCollisions()
	{
		upWallCollision = false;
		downWallCollision = false;
		leftWallCollision = false;
		rightWallCollision = false;
	}
public:
	void alife()
	{
		falseCollisions();
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
				rightWallCollision = true;
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
				leftWallCollision = true;
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
				upWallCollision = true;
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
				downWallCollision = true;
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

	void punch(POINT _power)
	{
		power.x += _power.x;
		power.y += _power.y;
	}

	void teleport(int px, int py)
	{
		power.x = px;
		power.y = py;
	}

	void teleport(POINT _position)
	{
		power.x = _position.x;
		power.y = _position.y;
	}

	void show()
	{
		Ellipse(hDC, position.x - size.x, position.y + size.y, position.x + size.x, position.y - size.y);
	}
};
POINT getWindowPower(short delay, byte factorX, byte factorY)
{
	POINT firstPosition = getWindowPos();
	Sleep(delay);
	POINT secondPosition = getWindowPos();
	return { -(firstPosition.x - secondPosition.x) * factorX, (firstPosition.y - secondPosition.y) * factorY };
}

int main(int argc, char *argv[])
{
	GetClientRect(hWnd, &pRECT);
	SetBkMode(hDC, TRANSPARENT);
	GetObject(RPEN, sizeof(EXTLOGPEN), &pINFO);
	SelectObject(hDC, RPEN);

	Object ellipse(P.X, P.Y, 30, 30, 0);
	ellipse.punch(500, 100);

	while (true)
	{
		if(ellipse.downWallCollision)
			ellipse.punch(getWindowPower(seconds(speed), 2, 4));
		ellipse.alife();
		clear;
		ellipse.show();
	}

	return 0;

}