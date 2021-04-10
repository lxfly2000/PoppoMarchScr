#include "DxRootScene.h"
#include <DxLib.h>

DxRootScene::DxRootScene():SceneObject(),resolutionWidth(1280),resolutionHeight(720),isWindowed(FALSE)
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
	if (ScreenFlip() == -1)
		return -1;
	if(ProcessMessage()==-1)
		SetIsRunning(FALSE);
	return SceneObject::RunFrame();
}
