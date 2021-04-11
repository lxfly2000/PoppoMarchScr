#pragma once
#include "Game/SceneObject.h"

class BubbleScene :public SceneObject
{
public:
	virtual ~BubbleScene();
	virtual int Init()override;
	virtual int RunFrame()override;
private:
	float floatingPointX[2], floatingPointY[2];
	int targetingPoint;
	int frameCounter;
	int fps;
	int resolutionWidth, resolutionHeight;
};
