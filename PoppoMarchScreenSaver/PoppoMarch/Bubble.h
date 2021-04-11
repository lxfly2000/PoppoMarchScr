#pragma once
#include "Game/SceneObject.h"

#define BUBBLE_MAX_SPEED 2//pixels per second
#define BUBBLE_MAX_ACC 2
#define BUBBLE_MAX_RADIUS 40
#define BUBBLE_MIN_RADIUS 10

//f=kv f=a
#define FLUID_FORCE_FACTOR (BUBBLE_MAX_ACC/BUBBLE_MAX_SPEED)

class Bubble :public SceneObject
{
public:
	Bubble();
	virtual int Init()override;
	virtual int RunFrame()override;
	void SetPos(float x, float y);
	void SetToPos(float x, float y);
	void SetVelXY(float vx, float vy);
	// 　　↑3Π/2
	// 　　│
	// ←─┼─→0
	// Π　│
	// 　　↓Π/2
	void SetVelVA(float v, float angle);
	void SetAccXY(float ax, float ay);
	// 　　↑3Π/2
	// 　　│
	// ←─┼─→0
	// Π　│
	// 　　↓Π/2
	void SetAccVA(float a, float angle);
	void SetAccForce(float f);
	void SetRadius(float);
	void SetColor(int);
	float GetPosX();
	float GetPosY();
	float GetToPosX();
	float GetToPosY();
	float GetVelX();
	float GetVelY();
	float GetVel();
	// 　　↑3Π/2
	// 　　│
	// ←─┼─→0
	// Π　│
	// 　　↓Π/2
	float GetVelAngle();
	float GetAccX();
	float GetAccY();
	float GetAcc();
	// 　　↑3Π/2
	// 　　│
	// ←─┼─→0
	// Π　│
	// 　　↓Π/2
	float GetAccAngle();
	float GetAccForce();
	float GetRadius();
	int GetColor();
private:
	float posX, posY;//当前位置
	float toX, toY;//目标位置
	float vX, vY;//当前速度
	float aX, aY;//当前加速度
	float aF;//阻力加速度
	float radius;
	int color;
	int frameCounter;
	static int fps;
};