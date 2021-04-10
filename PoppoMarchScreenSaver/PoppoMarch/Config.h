#pragma once
#include <Windows.h>

#define AUTHOR_NAME "lxfly2000"
#define APP_NAME "PoppoMarchScr"

#define KEY_SHOW_FPS "showFps"
#define KEY_PLAY_BGM "playBgm"
#define KEY_ANIMATION_SPEED "animationSpeed"
#define KEY_CLOSE_BY_CLICKING "closeByClicking"

BOOL InitConfigFile();
void WriteInt(LPCSTR key, UINT n);
UINT ReadInt(LPCSTR key);
UINT ReadInt(LPCSTR key,UINT def);
