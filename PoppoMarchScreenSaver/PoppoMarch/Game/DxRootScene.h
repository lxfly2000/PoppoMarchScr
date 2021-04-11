#pragma once
#include "SceneObject.h"

class DxRootScene :public SceneObject
{
public:
	DxRootScene();
	//������Ϸ�ڲ��ֱ��ʣ�������Initǰ���ã�������Ϸ���л�����ɿ���
	virtual void SetResolution(int w, int h);
	virtual int GetResolutionWidth();
	virtual int GetResolutionHeight();
	//0=ȫ��Ļ��1=����
	virtual void ChangeWindowed(int);
	virtual int GetIsWindowed();
	//ע�⿼����Ҫ���¼�����Դ�����
	virtual int Init()override;
	//DEMO��������Ҫ�ڼ̳����е��ã�������������SceneObject::RunFrame
	virtual int RunFrame()override;
private:
	int resolutionWidth, resolutionHeight,isWindowed;
};
