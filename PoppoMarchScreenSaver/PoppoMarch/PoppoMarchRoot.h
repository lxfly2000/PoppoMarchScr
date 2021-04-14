#pragma once
#include "Game/DxRootScene.h"
#include "Game/FPSMeter.h"
#include "Game/KeyTrigger.h"
#include "BackgroundScene.h"
#include "BubbleScene.h"
#include "PoppoScene.h"

class PoppoMarchRoot :public DxRootScene
{
public:
	PoppoMarchRoot();
	virtual int Init()override;
	virtual int RunFrame()override;
	virtual int End()override;
	virtual void SetIsRunning(int)override;
private:
	int ProcessInput();
	void DrawFrame();
	KeyTrigger ktEsc, ktSpace, ktEnter, ktF11;
	FPSMeter fpsMeter;
	int optionCloseByClick;
	int optionShowFps;
	int optionPlayBgm;
	int mouseHideCounter;
	BackgroundScene bg;
	BubbleScene bb;
	PoppoScene pp;
	int hBgm;
};
