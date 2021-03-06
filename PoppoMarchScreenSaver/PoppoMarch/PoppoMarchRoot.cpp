#define NOMINMAX
#include "PoppoMarchRoot.h"
#include "Config.h"
#include "../resource.h"
#include <DxLib.h>
#include <time.h>
#include <algorithm>

#define FADEIN_TIME_MS 1000
static int fadein_frames = 0;
static int fadein_counter = 0;

PoppoMarchRoot::PoppoMarchRoot():DxRootScene(),
ktEsc(KEY_INPUT_ESCAPE), ktSpace(KEY_INPUT_SPACE), ktEnter(KEY_INPUT_RETURN), ktF11(KEY_INPUT_F11),
optionCloseByClick(FALSE),mouseHideCounter(0),optionShowFps(0),optionPlayBgm(0),hBgm(0)
{
}

int PoppoMarchRoot::Init()
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(FALSE);
#endif
	if (!InitConfigFile())
		return -1;
	optionShowFps = ReadInt(KEY_SHOW_FPS);
	optionCloseByClick = ReadInt(KEY_CLOSE_BY_CLICKING, 1);
	optionPlayBgm = ReadInt(KEY_PLAY_BGM);

	SetResolution(std::min(1280, GetSystemMetrics(SM_CXSCREEN)), std::min(720, GetSystemMetrics(SM_CYSCREEN)));
	if (!DxLib_IsInit())
		ChangeWindowed(FALSE);
	SetAlwaysRunFlag(TRUE);
	SetWindowText(TEXT("Poppo March"));

	fadein_frames = FADEIN_TIME_MS * GetRefreshRate() / 1000;
	AddChild(&fpsMeter);
	AddChild(&ktEsc);
	AddChild(&ktSpace);
	AddChild(&ktEnter);
	AddChild(&ktF11);
	AddChild(&bg);
	AddChild(&bb);
	AddChild(&pp);
	SRand(time(NULL));
	if (DxRootScene::Init())
		return -2;
	fpsMeter.SetDesignFPS(GetRefreshRate());
	if (optionPlayBgm && hBgm == 0)
	{
		//这个函数只能在DxLib_Init后调用
		hBgm = LoadSoundMemByResource(TEXT("bgm.ogg"), TEXT("bgm"));
		if (hBgm && hBgm != -1)
		{
			LPVOID ptr;
			size_t sz;
			if (GetResourceInfo(TEXT("bgm.txt"), TEXT("loop"), &ptr, &sz) == 0)
			{
				int a, b;
				sscanf_s((LPSTR)ptr, "%d %d", &a, &b);
				SetLoopAreaSamplePosSoundMem(a, b, hBgm);
			}
			PlaySoundMem(hBgm, DX_PLAYTYPE_LOOP);
		}
	}
	return 0;
}

int PoppoMarchRoot::RunFrame()
{
	if (ProcessInput() == 1)
		return 0;
	ClearDrawScreen();
	if (fadein_counter < fadein_frames)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * fadein_counter / fadein_frames);
	if (SceneObject::RunFrame())
		return -1;
	if (fadein_counter < fadein_frames)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		fadein_counter++;
	}
	//此处暂无数据更新的操作
	DrawFrame();
	if (ScreenFlip() == -1)
		return -2;
	return 0;
}

int PoppoMarchRoot::End()
{
	if (SceneObject::End())
		return -1;
	if (RemoveAllChilds())
		return -2;
	if (hBgm && IsRunning() == FALSE)
	{
		StopMusicMem(hBgm);
		DeleteMusicMem(hBgm);
		hBgm = 0;
	}
	return 0;
}

void PoppoMarchRoot::SetIsRunning(int r)
{
	pp.SetIsRunning(FALSE);
	SceneObject::SetIsRunning(r);
}

int PoppoMarchRoot::ProcessInput()
{
	if (ProcessMessage() == -1)
	{
		SetIsRunning(FALSE);
		return 0;
	}
	if (optionCloseByClick)
	{
		if (GetMouseInput())
		{
			SetIsRunning(FALSE);
			return 1;
		}
	}
	else
	{
		static int lastMouseX = 0, lastMouseY = 0;
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);
		if (mouseX != lastMouseX || mouseY != lastMouseY)
		{
			mouseHideCounter = GetRefreshRate() * 5;
			SetMouseDispFlag(TRUE);
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}
		if (mouseHideCounter)
		{
			mouseHideCounter--;
			if (mouseHideCounter == 0)
				SetMouseDispFlag(FALSE);
		}
	}
	if (ktEsc.IsOnRelease() || ktSpace.IsOnRelease() || ktEnter.IsOnRelease())
		SetIsRunning(FALSE);
	if (ktF11.IsOnRelease())
	{
		if (End())
			return -1;
		ChangeWindowed(GetIsWindowed() ^ 1);
		if (Init())
			return -2;
	}
	return 0;
}

void PoppoMarchRoot::DrawFrame()
{
	if (optionShowFps)
		DrawFormatString(0, 0, GetColor(0, 128, 0), TEXT("FPS:%6.2f"), fpsMeter.GetFPS());
#ifdef _DEBUG
	static int showDbgX = 0;
	if (showDbgX == 0)
	{
		int x, y, z;
		GetDrawScreenSize(&showDbgX, &y);
		GetDrawStringSize(&x, &y, &z, TEXT("DEBUG"), 5);
		showDbgX -= x;
	}
	DrawString(showDbgX, 0, TEXT("DEBUG"), GetColor(255, 0, 255));
#endif
}
