#include "DxRootScene.h"
#include <DxLib.h>

//DxLibָ��Ĭ�Ϸֱ��ʣ�640x480��DOSʱ���ģ�
//�����С�ֱ���Ӧ����Win7Ϊ��׼1024x768����ҵ���ã�
//���ǿ�����Ӧ��û��С��1366x768�İ�
DxRootScene::DxRootScene():SceneObject(),resolutionWidth(1024),resolutionHeight(768),isWindowed(FALSE)
{
}

void DxRootScene::SetResolution(int w, int h)
{
	resolutionWidth = w;
	resolutionHeight = h;
}

int DxRootScene::GetResolutionWidth()
{
	return resolutionWidth;
}

int DxRootScene::GetResolutionHeight()
{
	return resolutionHeight;
}

void DxRootScene::ChangeWindowed(int w)
{
	isWindowed = w;
	ChangeWindowMode(isWindowed);
}

int DxRootScene::GetIsWindowed()
{
	return isWindowed;
}

int DxRootScene::Init()
{
	SetGraphMode(resolutionWidth, resolutionHeight, 32);
	ChangeWindowMode(isWindowed);
	if (DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	return SceneObject::Init();
}

int DxRootScene::RunFrame()
{
	ClearDrawScreen();
	if (SceneObject::RunFrame())
		return -1;
	if (ScreenFlip() == -1)
		return -2;
	if(ProcessMessage()==-1)
		SetIsRunning(FALSE);
	return 0;
}
