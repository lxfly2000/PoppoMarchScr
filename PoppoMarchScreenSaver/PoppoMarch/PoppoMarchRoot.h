#pragma once
#include "Game/DxRootScene.h"
#include "Game/FPSMeter.h"
#include "Game/KeyTrigger.h"

class PoppoMarchRoot :public DxRootScene
{
public:
	PoppoMarchRoot();
	virtual int Init()override;
	virtual int RunFrame()override;
private:
	int ProcessInput();
	void DrawFrame();
	KeyTrigger ktEsc, ktSpace, ktEnter, ktF11;
	FPSMeter fpsMeter;
	int optionShowFps,optionCloseByClick;
	int mouseHideCounter;
};
