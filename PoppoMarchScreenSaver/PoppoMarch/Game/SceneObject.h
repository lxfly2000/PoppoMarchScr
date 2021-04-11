#pragma once
#include <vector>
#define MAX_LAYER_COUNT 2
class SceneObject
{
public:
	SceneObject();
	//初始化，返回值为0表示正常执行，其他值为错误
	//请务必考虑切换全屏等造成资源丢失需要重新加载的情况
	//调用顺序推荐为先初始化自己再初始化子节点
	virtual int Init();
	//每帧的运行函数，返回值为0表示正常执行，其他值为错误
	//函数默认行为为同一层的先添加先绘制，后添加的绘制画面覆盖先添加的
	//同一层绘制完后绘制更高层的，高层覆盖低层
	//一般情况下，
	//子场景只需负责数据更新及绘制操作，逻辑是：（处理输入），子节点RunFrame，数据更新，绘制
	//而根场景则除前述操作外还需要处理DxLib的主要循环逻辑，包括：（清空屏幕），处理输入，子节点RunFrame，数据更新，绘制，交换缓冲
	virtual int RunFrame();
	//退出，返回值为0表示正常执行，其他值为错误
	//调用顺序推荐为先释放子节点再释放自己
	virtual int End();
	//设置图层，正数时数字越大图层越高，最大为MAX_LAYER_COUNT-1
	//负数时为MAX_LAYER_COUNT+n且n小于-MAX_LAYER_COUNT时视为-MAX_LAYER_COUNT
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
	//注意节点不使用时最好调用Remove相关操作
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
