#pragma once
#include "SceneObject.h"
class KeyTrigger :public SceneObject
{
public:
	KeyTrigger();
	KeyTrigger(int _key);
	void SetKey(int _key);
	int RunFrame()override;
	bool IsPressing();
	bool IsOnPress();
	bool IsOnRelease();
protected:
	int key;
private:
	bool isPressing_prev, isPressing_now;
};