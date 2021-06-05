#pragma once
#include "Game/SceneObject.h"

#define CHARACTER_DRAW_DEFAULT_SPEED_JUMP_MS 667
#define CHARACTER_DRAW_DEFAULT_SPEED_X_BY_60FPS 1.0f//���������60FPS������¡�һ֡�����ƶ��ٶȣ���
#define CHARACTER_DRAW_DEFAULT_ZOOM 1.0f
#define CHARACTER_DRAW_DEFAULT_JUMP_HEIGHT_PIXELS 25

class CharacterDraw :public SceneObject
{
public:
	CharacterDraw();
	virtual int RunFrame()override;
	void SetGraph(int grHandle,int siHandle);
	void SetPos(float x, float y);
	//������60FPSʱ��ÿ֡�����ƶ��ٶȣ����أ�
	void SetSpeedXBy60FPS(float v);
	//�������������ں�����
	void SetJumpMs(int n);
	void SetZoom(float z);
	bool HitTest(float x, float y);
	float GetPosX();
	//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int GetStatus();
	//����Ϊ�����ʱ������λ��
	void Explode(int x,int y);
	void SetBlankPixelsBottom(int n);
	static void SetSparkGraph(int gr);
	static int GetSparkGraph();
private:
	static int hGraphSpark;
	int frameCounter;
	int hGraph,hSoftImage;
	int status;//0=������ʾ 1=��ըЧ���� 2=��ʧ
	int jumpFrames;//һ������ռ�ö���֡
	int blankPixelsBottom;
	float graphWidth, graphHeight;
	float posX, posY;
	float speedX;//ÿ֡���ٶ�
	float zoom;
	float jumpHeight;//Pixels
};
