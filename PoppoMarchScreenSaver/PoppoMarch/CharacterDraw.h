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
	//设置跳动的周期帧数
	void SetSpeedJump(float v);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=正常显示 1=爆炸效果中 2=消失
	int GetStatus();
	void Explode();
private:
	int frameCounter;
	int hPic;
	int status;//0=正常显示 1=爆炸效果中 2=消失
	int speedJump;//一次跳动占用多少帧
	float posX, posY;
	float speedX;//每帧的速度
	float zoom;
};
