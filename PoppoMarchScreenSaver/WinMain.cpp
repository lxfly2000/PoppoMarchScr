#include <Windows.h>
#include "ScreenSaver.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR param, int iShow)
{
	SetThreadUILanguage(GetUserDefaultUILanguage());
	ScreenSaver saver;
	HWND hParent = NULL;
	if (lstrlenA(param) > 3)
		hParent = (HWND)atoi(param + 3);
	if (lstrlenA(param) == 0)
		return saver.Settings(hInst, hParent);//在文件的右键菜单上选择配置屏保
	else switch (param[1])
	{//https://support.microsoft.com/en-us/help/182383/info-screen-saver-command-line-arguments
	case TEXT('c')://在屏保设置对话框里的配置屏保
	case TEXT('C'):return saver.Settings(hInst, hParent);
	case TEXT('p')://在屏保设置对话框里的屏保预览
	case TEXT('P'):return 0;//这个程序不支持预览
	case TEXT('a'):case TEXT('A'):return 0;//退出屏保时要求输入密码（仅Win95）
	case TEXT('s')://在屏保设置对话框里点击预览按钮后的预览，系统空闲超时后的屏保运行
	case TEXT('S')://在文件上预览
		return saver.Run(hParent);
	}
	return -1;
}
