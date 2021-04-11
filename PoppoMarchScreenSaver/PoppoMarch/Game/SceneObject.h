#pragma once
#include <vector>
#define MAX_LAYER_COUNT 2
class SceneObject
{
public:
	SceneObject();
	//��ʼ��������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	//����ؿ����л�ȫ���������Դ��ʧ��Ҫ���¼��ص����
	//����˳���Ƽ�Ϊ�ȳ�ʼ���Լ��ٳ�ʼ���ӽڵ�
	virtual int Init();
	//ÿ֡�����к���������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	//����Ĭ����ΪΪͬһ���������Ȼ��ƣ�����ӵĻ��ƻ��渲������ӵ�
	//ͬһ����������Ƹ��߲�ģ��߲㸲�ǵͲ�
	//һ������£�
	//�ӳ���ֻ�踺�����ݸ��¼����Ʋ������߼��ǣ����������룩���ӽڵ�RunFrame�����ݸ��£�����
	//�����������ǰ�������⻹��Ҫ����DxLib����Ҫѭ���߼����������������Ļ�����������룬�ӽڵ�RunFrame�����ݸ��£����ƣ���������
	virtual int RunFrame();
	//�˳�������ֵΪ0��ʾ����ִ�У�����ֵΪ����
	//����˳���Ƽ�Ϊ���ͷ��ӽڵ����ͷ��Լ�
	virtual int End();
	//����ͼ�㣬����ʱ����Խ��ͼ��Խ�ߣ����ΪMAX_LAYER_COUNT-1
	//����ʱΪMAX_LAYER_COUNT+n��nС��-MAX_LAYER_COUNTʱ��Ϊ-MAX_LAYER_COUNT
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
	//ע��ڵ㲻ʹ��ʱ��õ���Remove��ز���
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
