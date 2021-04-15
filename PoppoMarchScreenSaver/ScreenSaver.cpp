#include "ScreenSaver.h"
#include "SettingsDialog.h"
#include "PoppoMarch/PoppoMarchGame.h"

int ScreenSaver::Settings(HINSTANCE hInst, HWND hWndParent)
{
	int r = SettingsDialog(hInst, hWndParent);
	if (r == 1)
		return Run(NULL);
	return r;
}

int ScreenSaver::Run(HWND hWndParent)
{
	if (hWndParent)
		return 1;
	return PoppoMarchGame().GameMain();
}
