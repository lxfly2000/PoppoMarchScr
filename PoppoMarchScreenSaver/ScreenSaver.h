#pragma once
#include <Windows.h>

class ScreenSaver
{
public:
	int Settings(HINSTANCE hInst, HWND hWndParent);
	int Run(HWND hWndParent);
};
