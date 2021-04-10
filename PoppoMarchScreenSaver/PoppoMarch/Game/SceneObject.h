#pragma once
#include <vector>
#define MAX_LAYER_COUNT 5
class SceneObject
{
public:
	SceneObject();
	//初始化，返回值为0表示正常执行，其他值为错误
	virtual int Init();
	//每帧的运行函数，返回值为0表示正常执行，其他值为错误
	virtual int RunFrame();
	//退出，返回值为0表示正常执行，其他值为错误
	virtual int End();
	//设置图层，数字越大图层越高，最大为MAX_LAYER_COUNT-1
	virtual void SetLayer(int);
	virtual int GetLayer();
	//1表示运行中，0表示运行停止，应结束循环
	virtual int IsRunning();
	//1表示运行中，0表示运行停止，应结束循环
	virtual void SetIsRunning(int);
protected:
	//返回值为0表示正常执行，其他值为错误
	virtual int InitChilds();
	//返回值为0表示正常执行，其他值为错误
	virtual int RunFrameChilds();
	//返回值为0表示正常执行，其他值为错误
	virtual int EndChilds();
	//向子级列表末尾添加节点，返回值为插入的位置
	virtual size_t AddChild(SceneObject*);
	//向指定位置添加节点，如果指定位置超过列表总数则会在末尾处添加，返回值为插入的位置
	virtual size_t AddChild(size_t, SceneObject*);
	virtual int RemoveChild(size_t);
	virtual int RemoveChildRecursive(size_t);
	//删除所有直接子节点
	virtual int RemoveAllChilds();
	//递归删除所有子节点
	virtual int RemoveAllChildsRecursive();
	virtual SceneObject* GetChild(size_t);
	virtual size_t GetChildCount();
private:
	std::vector<SceneObject*>childNodes;//直接子级列表
	int layer;
	int isRunning;
};
