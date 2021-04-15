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
	//��������������֡��
	void SetJumpFrames(int n);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int GetStatus();
	//����Ϊ�����ʱ������λ��
	void Explode(int mouse_x, int mouse_y);
	void SetBlankPixelsBottom(int n);
private:
	int frameCounter;
	int hGraph,hSoftImage;
	int status;//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int jumpFrames;//һ������ռ�ö���֡
	int blankPixelsBottom;
	int mouseX, mouseY;
	float graphWidth, graphHeight;
	float posX, posY;
	float speedX;//ÿ֡���ٶ�
	float zoom;
	float jumpHeight;//Pixels
};
