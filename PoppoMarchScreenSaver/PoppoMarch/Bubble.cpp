#include "Bubble.h"
#include "Game/DxCommon.h"
#include <DxLib.h>

//计算从(x1,y1)到(x2,y2)的角度
float CalcLineAngle(float x1, float y1, float x2, float y2)
{
	return atan2f(y2 - y1, x2 - x1);
}

int Bubble::fps = 0;

Bubble::Bubble():posX(0), posY(0),toX(0), toY(0),vX(0), vY(0),aX(0), aY(0),aF(0),radius(0),color(0),frameCounter(0)
{
}

int Bubble::Init()
{
	if (fps == 0)
		fps = GetRefreshRate();
	return 0;
}

int Bubble::RunFrame()
{
	float va = GetVelAngle();
	aF = FLUID_FORCE_FACTOR * GetVel() / fps;
	vX = vX + aX - aF * cosf(va);
	vY = vY + aY - aF * sinf(va);
	posX += vX;
	posY += vY;
	if (frameCounter % (fps / 2) == 0)
		SetAccVA((float)GetRand(BUBBLE_MAX_ACC)/fps, CalcLineAngle(posX, posY, toX, toY) + DegToRad(GetRand(90)) - DX_PI / 4);
	DrawCircleAA(posX, posY, radius, 50, color);
#ifdef _DEBUG
	DrawLineAA(posX, posY, posX + aX*1000, posY + aY*1000, 0xFFFF0000);
	DrawCircleAA(posX, posY, aF*1000,50, 0xFF0000FF, FALSE);
#endif
	frameCounter = (frameCounter + 1) % fps;
	return 0;
}

void Bubble::SetPos(float x, float y)
{
	posX = x;
	posY = y;
}

void Bubble::SetToPos(float x, float y)
{
	toX = x;
	toY = y;
}

void Bubble::SetVelXY(float vx, float vy)
{
	vX = vx;
	vY = vy;
}

void Bubble::SetVelVA(float v, float angle)
{
	vX = v * cosf(angle);
	vY = v * sinf(angle);
}

void Bubble::SetAccXY(float ax, float ay)
{
	aX = ax;
	aY = ay;
}

void Bubble::SetAccVA(float a, float angle)
{
	aX = a * cosf(angle);
	aY = a * sinf(angle);
}

void Bubble::SetAccForce(float f)
{
	aF = f;
}

void Bubble::SetRadius(float r)
{
	radius = r;
}

void Bubble::SetColor(int c)
{
	color = c;
}

float Bubble::GetPosX()
{
	return posX;
}

float Bubble::GetPosY()
{
	return posY;
}

float Bubble::GetToPosX()
{
	return toX;
}

float Bubble::GetToPosY()
{
	return toY;
}

float Bubble::GetVelX()
{
	return vX;
}

float Bubble::GetVelY()
{
	return vY;
}

float Bubble::GetVel()
{
	return sqrtf(vX * vX + vY * vY);
}

float Bubble::GetVelAngle()
{
	return atan2f(vY, vX);
}

float Bubble::GetAccX()
{
	return aX;
}

float Bubble::GetAccY()
{
	return aY;
}

float Bubble::GetAcc()
{
	return sqrtf(aX * aX + aY * aY);
}

float Bubble::GetAccAngle()
{
	return atan2f(aY, aX);
}

float Bubble::GetAccForce()
{
	return aF;
}

float Bubble::GetRadius()
{
	return radius;
}

int Bubble::GetColor()
{
	return color;
}
