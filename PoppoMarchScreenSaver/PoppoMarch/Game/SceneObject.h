#pragma once
#include <vector>
#define MAX_LAYER_COUNT 5
class SceneObject
{
public:
	SceneObject();
	//��ʼ��������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int Init();
	//ÿ֡�����к���������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int RunFrame();
	//�˳�������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int End();
	//����ͼ�㣬����Խ��ͼ��Խ�ߣ����ΪMAX_LAYER_COUNT-1
	virtual void SetLayer(int);
	virtual int GetLayer();
	//1��ʾ�����У�0��ʾ����ֹͣ��Ӧ����ѭ��
	virtual int IsRunning();
	//1��ʾ�����У�0��ʾ����ֹͣ��Ӧ����ѭ��
	virtual void SetIsRunning(int);
protected:
	//����ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int InitChilds();
	//����ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int RunFrameChilds();
	//����ֵΪ0��ʾ����ִ�У�����ֵΪ����
	virtual int EndChilds();
	//���Ӽ��б�ĩβ��ӽڵ㣬����ֵΪ�����λ��
	virtual size_t AddChild(SceneObject*);
	//��ָ��λ����ӽڵ㣬���ָ��λ�ó����б����������ĩβ����ӣ�����ֵΪ�����λ��
	virtual size_t AddChild(size_t, SceneObject*);
	virtual int RemoveChild(size_t);
	virtual int RemoveChildRecursive(size_t);
	//ɾ������ֱ���ӽڵ�
	virtual int RemoveAllChilds();
	//�ݹ�ɾ�������ӽڵ�
	virtual int RemoveAllChildsRecursive();
	virtual SceneObject* GetChild(size_t);
	virtual size_t GetChildCount();
private:
	std::vector<SceneObject*>childNodes;//ֱ���Ӽ��б�
	int layer;
	int isRunning;
};
