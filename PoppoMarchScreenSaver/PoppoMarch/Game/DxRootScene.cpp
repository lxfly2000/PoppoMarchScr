#include "DxRootScene.h"
#include <DxLib.h>

//DxLib指定默认分辨率：640x480（DOS时代的）
//如今最小分辨率应该以Win7为基准1024x768（工业常用）
//若是宽屏则应该没有小于1366x768的吧
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
