#pragma once
#include "Game/SceneObject.h"

#define CHARACTER_DRAW_DEFAULT_SPEED_JUMP_MS 667
#define CHARACTER_DRAW_DEFAULT_SPEED_X_BY_60FPS 1.0f//这仅仅是在60FPS的情况下【一帧】的移动速度！！
#define CHARACTER_DRAW_DEFAULT_ZOOM 1.0f
#define CHARACTER_DRAW_DEFAULT_JUMP_HEIGHT_PIXELS 25

class CharacterDraw :public SceneObject
{
public:
	CharacterDraw();
	virtual int RunFrame()override;
	void SetGraph(int grHandle,int siHandle);
	void SetPos(float x, float y);
	//设置在60FPS时【每帧】的移动速度（像素）
	void SetSpeedXBy60FPS(float v);
	//设置跳动的周期毫秒数
	void SetJumpMs(int n);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=正常显示 1=爆炸效果中 2=消失
	int GetStatus();
	//参数为鼠标点击时的坐标位置
	void Explode(int x,int y);
	void SetBlankPixelsBottom(int n);
	static void SetSparkGraph(int gr);
	static int GetSparkGraph();
private:
	static int hGraphSpark;
	int frameCounter;
	int hGraph,hSoftImage;
	int status;//0=正常显示 1=爆炸效果中 2=消失
	int jumpFrames;//一次跳动占用多少帧
	int blankPixelsBottom;
	float graphWidth, graphHeight;
	float posX, posY;
	float speedX;//每帧的速度
	float zoom;
	float jumpHeight;//Pixels
};
