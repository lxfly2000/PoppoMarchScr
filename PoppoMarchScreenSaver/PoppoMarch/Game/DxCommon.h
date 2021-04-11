#pragma once
#include<DxLib.h>
#define BCHECK(expression)\
if(!(expression))\
{\
TCHAR msg[256];\
wsprintf(msg,TEXT("%s:%d:$%s$���ؽ��ΪFALSE��$$����ȷ������ֹ�����ȡ�����������С�\n"),TEXT(__FILE__),__LINE__,TEXT(_CRT_STRINGIZE(expression)));\
ErrorLogAdd(msg);\
for(int i=0;i<lstrlen(msg);i++)\
if(msg[i]=='$')\
msg[i]='\n';\
if(MessageBox(GetMainWindowHandle(),msg,NULL,MB_OKCANCEL|MB_ICONERROR)==IDOK)\
{\
AppLogAdd(TEXT("ǿ���˳�����\n"));\
exit(-1);\
}\
}
#define ZCHECK(expression) BCHECK((expression)==0)

#define MsToFrames(ms) ((ms)*GetRefreshRate()/1000)
#define DegToRad(d) ((d)*DX_PI/180)
#define RadToDeg(r) ((r)*180/DX_PI)
