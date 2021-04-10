#include "DxCommon.h"
#include "KeyTrigger.h"

KeyTrigger::KeyTrigger():key(NULL),SceneObject()
{
}

KeyTrigger::KeyTrigger(int _key):KeyTrigger()
{
	SetKey(_key);
}

void KeyTrigger::SetKey(int _key)
{
	key = _key;
	isPressing_prev = isPressing_now = false;
}

int KeyTrigger::RunFrame()
{
	isPressing_prev = isPressing_now;
	isPressing_now = CheckHitKey(key);
	return 0;
}

bool KeyTrigger::IsPressing()
{
	return isPressing_now;
}

bool KeyTrigger::IsOnPress()
{
	return !isPressing_prev&&isPressing_now;
}

bool KeyTrigger::IsOnRelease()
{
	return isPressing_prev && !isPressing_now;
}
