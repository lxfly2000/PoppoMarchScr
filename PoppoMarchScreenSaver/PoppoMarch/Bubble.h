#pragma once
#include "Game/SceneObject.h"

#define BUBBLE_MAX_SPEED 4.4f//pixels per second
#define BUBBLE_MAX_ACC 4.0f//pixels per second sq.
#define BUBBLE_MAX_RADIUS 40.0f
#define BUBBLE_MIN_RADIUS 10.0f
#define BUBBLE_REFERENCE_RADIUS 40.0f

//�ο���https://www.guokr.com/article/268900/
#define FLUID_FORCE_FACTOR (BUBBLE_MAX_ACC*BUBBLE_REFERENCE_RADIUS/BUBBLE_MAX_SPEED)//per second

class Bubble :public SceneObject
{
public:
	Bubble();
	virtual int Init()override;
	virtual int RunFrame()override;
	void SetPos(float x, float y);
	void SetToPos(float x, float y);
	void SetVelXY(float vx, float vy);
	// ������3��/2
	// ������
	// �����੤��0
	// ������
	// ��������/2
	void SetVelVA(float v, float angle);
	void SetAccXY(float ax, float ay);
	// ������3��/2
	// ������
	// �����੤��0
	// ������
	// ��������/2
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
	// ������3��/2
	// ������
	// �����੤��0
	// ������
	// ��������/2
	float GetVelAngle();
	float GetAccX();
	float GetAccY();
	float GetAcc();
	// ������3��/2
	// ������
	// �����੤��0
	// ������
	// ��������/2
	float GetAccAngle();
	float GetAccForce();
	float GetRadius();
	int GetColor();
private:
	float posX, posY;//��ǰλ��
	float toX, toY;//Ŀ��λ��
	float vX, vY;//��ǰ�ٶ�
	float aX, aY;//��ǰ���ٶ�
	float aF;//�������ٶ�
	float radius;
	int color;
	int frameCounter;
	static int fps;
};