#pragma once
#include "SceneObject.h"

class DxRootScene :public SceneObject
{
public:
	DxRootScene();
	//设置游戏内部分辨率，尽量在Init前调用，否则游戏中切换会造成卡顿
	virtual void SetResolution(int w, int h);
	virtual int GetResolutionWidth();
	virtual int GetResolutionHeight();
	//0=全屏幕，1=窗口
	virtual void ChangeWindowed(int);
	virtual int GetIsWindowed();
	//注意考虑需要重新加载资源的情况
	virtual int Init()override;
	//DEMO函数，不要在继承类中调用，如若调用请用SceneObject::RunFrame
	virtual int RunFrame()override;
private:
	int resolutionWidth, resolutionHeight,isWindowed;
};
