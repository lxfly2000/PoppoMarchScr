#pragma once
#include "Game/SceneObject.h"

#define CHARACTER_DRAW_DEFAULT_SPEED_JUMP_FRAMES 40
#define CHARACTER_DRAW_DEFAULT_SPEED_X 1.0f
#define CHARACTER_DRAW_DEFAULT_ZOOM 1.0f
#define CHARACTER_DRAW_DEFAULT_JUMP_HEIGHT_PIXELS 25

class CharacterDraw :public SceneObject
{
public:
	CharacterDraw();
	virtual int RunFrame()override;
	void SetGraph(int grHandle,int siHandle);
	void SetPos(float x, float y);
	void SetSpeedX(float v);
	//设置跳动的周期帧数
	void SetJumpFrames(int n);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=正常显示 1=爆炸效果中 2=消失
	int GetStatus();
	//参数为鼠标点击时的坐标位置
	void Explode(int mouse_x, int mouse_y);
	void SetBlankPixelsBottom(int n);
private:
	int frameCounter;
	int hGraph,hSoftImage;
	int status;//0=正常显示 1=爆炸效果中 2=消失
	int jumpFrames;//一次跳动占用多少帧
	int blankPixelsBottom;
	int mouseX, mouseY;
	float graphWidth, graphHeight;
	float posX, posY;
	float speedX;//每帧的速度
	float zoom;
	float jumpHeight;//Pixels
};
