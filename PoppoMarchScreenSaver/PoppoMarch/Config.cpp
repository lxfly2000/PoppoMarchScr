#include "Config.h"

#include <ShlObj.h>
#include <Shlwapi.h>

char iniPath[MAX_PATH];
LPCSTR keyList[] = { KEY_SHOW_FPS,KEY_PLAY_BGM,KEY_ANIMATION_SPEED,KEY_CLOSE_BY_CLICKING };

BOOL InitConfigFile()
{
	if (!SHGetSpecialFolderPathA(NULL, iniPath, CSIDL_APPDATA, TRUE))
		return FALSE;
	PathCombineA(iniPath, iniPath, AUTHOR_NAME);
	if (!PathFileExistsA(iniPath))
		CreateDirectoryA(iniPath, NULL);
	PathCombineA(iniPath, iniPath, APP_NAME);
	if (!PathFileExistsA(iniPath))
		CreateDirectoryA(iniPath, NULL);
	PathCombineA(iniPath, iniPath, APP_NAME);
	lstrcatA(iniPath, ".ini");
	return TRUE;
}

void WriteInt(LPCSTR key, UINT n)
{
	char t[16];
	_itoa_s(n, t, 10);
	WritePrivateProfileStringA(APP_NAME, key, t, iniPath);
}

UINT ReadInt(LPCSTR key)
{
	return ReadInt(key, 0);
}

UINT ReadInt(LPCSTR key,UINT def)
{
	return GetPrivateProfileIntA(APP_NAME, key, def, iniPath);
}
