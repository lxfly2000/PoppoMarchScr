#include "PoppoMarchRoot.h"
#include "Config.h"
#include <DxLib.h>

PoppoMarchRoot::PoppoMarchRoot():DxRootScene(),
ktEsc(KEY_INPUT_ESCAPE), ktSpace(KEY_INPUT_SPACE), ktEnter(KEY_INPUT_RETURN), ktF11(KEY_INPUT_F11),
optionShowFps(FALSE),optionCloseByClick(FALSE),mouseHideCounter(0)
{
}

int PoppoMarchRoot::Init()
{
	if (!InitConfigFile())
		return -1;
	optionShowFps = ReadInt(KEY_SHOW_FPS);
	optionCloseByClick = ReadInt(KEY_CLOSE_BY_CLICKING);

	SetResolution(1280, 720);
	ChangeWindowed(FALSE);
	SetWindowText(TEXT("Poppo March"));

	fpsMeter.SetDesignFPS(GetRefreshRate());
	AddChild(&fpsMeter);
	AddChild(&ktEsc);
	AddChild(&ktSpace);
	AddChild(&ktEnter);
	AddChild(&ktF11);
	return DxRootScene::Init();
}

int PoppoMarchRoot::RunFrame()
{
	if (ProcessInput() == 1)
		return 0;
	DrawFrame();
	return DxRootScene::RunFrame();
}

int PoppoMarchRoot::ProcessInput()
{
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
		ChangeWindowed(GetIsWindowed() ^ 1);
	return 0;
}

void PoppoMarchRoot::DrawFrame()
{
	ClearDrawScreen();
	if (optionShowFps)
		DrawFormatString(0, 0, GetColor(255, 255, 255), TEXT("FPS:%6.2f"), fpsMeter.GetFPS());
}
