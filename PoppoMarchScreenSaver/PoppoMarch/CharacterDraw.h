#pragma once
#include "Game/SceneObject.h"

#define CHARACTER_DRAW_DEFAULT_SPEED_JUMP 30
#define CHARACTER_DRAW_DEFAULT_SPEED_X 1.0f

class CharacterDraw :public SceneObject
{
public:
	CharacterDraw();
	virtual int RunFrame()override;
	void SetGraph(int grHandle);
	void SetPos(float x, float y);
	void SetSpeedX(float v);
	//��������������֡��
	void SetSpeedJump(float v);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int GetStatus();
	void Explode();
private:
	int frameCounter;
	int hPic;
	int status;//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int speedJump;//һ������ռ�ö���֡
	float posX, posY;
	float speedX;//ÿ֡���ٶ�
	float zoom;
};
