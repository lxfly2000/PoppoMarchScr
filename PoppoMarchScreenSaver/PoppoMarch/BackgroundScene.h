#pragma once
#include "Game/SceneObject.h"

class BackgroundScene :public SceneObject
{
public:
	virtual int Init()override;
	virtual int RunFrame()override;
	virtual int End()override;
private:
	int grBg;
	float floatingPointX[2], floatingPointY[2];
	int targetingPoint;
	int frameCounter;
	int fps;
	int resolutionWidth, resolutionHeight;
};
