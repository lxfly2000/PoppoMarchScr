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
};
