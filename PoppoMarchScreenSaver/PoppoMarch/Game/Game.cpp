#include "Game.h"
#include "DxRootScene.h"

int Game::GameMain()
{
	DxRootScene o;
	if (o.Init())
		return -1;
	while (o.IsRunning())
	{
		if (o.RunFrame())
			return -2;
	}
	if (o.End())
		return -3;
	return 0;
}
