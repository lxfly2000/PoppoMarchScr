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
		return saver.Settings(hInst, hParent);//���ļ����Ҽ��˵���ѡ����������
	else switch (param[1])
	{//https://support.microsoft.com/en-us/help/182383/info-screen-saver-command-line-arguments
	case TEXT('c')://���������öԻ��������������
	case TEXT('C'):return saver.Settings(hInst, hParent);
	case TEXT('p')://���������öԻ����������Ԥ��
	case TEXT('P'):return 0;//�������֧��Ԥ��
	case TEXT('a'):case TEXT('A'):return 0;//�˳�����ʱҪ���������루��Win95��
	case TEXT('s')://���������öԻ�������Ԥ����ť���Ԥ����ϵͳ���г�ʱ�����������
	case TEXT('S')://���ļ���Ԥ��
		return saver.Run(hParent);
	}
	return -1;
}
