#include "SceneObject.h"
#include <algorithm>

SceneObject::SceneObject():childNodes(),layer(0),isRunning(1)
{
}

int SceneObject::Init()
{
	return InitChilds();
}

int SceneObject::RunFrame()
{
	return RunFrameChilds();
}

int SceneObject::End()
{
	return EndChilds();
}

int SceneObject::InitChilds()
{
	for (int layer = 0; layer < MAX_LAYER_COUNT; layer++)
	{
		for (size_t i = 0; i < childNodes.size();)
		{
			if (childNodes[i])
			{
				if (childNodes[i]->layer == layer && childNodes[i]->Init())
					return -1;
				i++;
			}
			else
			{
				childNodes.erase(childNodes.begin() + i);
			}
		}
	}
	return 0;
}

int SceneObject::RunFrameChilds()
{
	for (int layer = 0; layer < MAX_LAYER_COUNT; layer++)
	{
		for (size_t i = 0; i < childNodes.size();)
		{
			if (childNodes[i])
			{
				if (childNodes[i]->layer == layer && childNodes[i]->RunFrame())
					return -1;
				i++;
			}
			else
			{
				childNodes.erase(childNodes.begin() + i);
			}
		}
	}
	return 0;
}

int SceneObject::EndChilds()
{
	for (int layer = 0; layer < MAX_LAYER_COUNT; layer++)
	{
		for (size_t i = 0; i < childNodes.size();)
		{
			if (childNodes[i])
			{
				if (childNodes[i]->layer == layer && childNodes[i]->End())
					return -1;
				i++;
			}
			else
			{
				childNodes.erase(childNodes.begin() + i);
			}
		}
	}
	return 0;
}

size_t SceneObject::AddChild(SceneObject* child)
{
	childNodes.push_back(child);
	return childNodes.size() - 1;
}

size_t SceneObject::AddChild(size_t i, SceneObject* child)
{
	if (i >= childNodes.size())
		return AddChild(child);
	childNodes.insert(childNodes.begin() + i, child);
	return i;
}

int SceneObject::RemoveChild(size_t i)
{
	if (i >= childNodes.size())
		return -1;
	childNodes.erase(childNodes.begin() + i);
	return 0;
}

int SceneObject::RemoveChildRecursive(size_t i)
{
	if (GetChild(i)->RemoveAllChildsRecursive())
		return -1;
	return RemoveChild(i);
}

int SceneObject::RemoveAllChilds()
{
	while (GetChildCount())
	{
		if (RemoveChild(0))
			return -1;
	}
	return 0;
}

int SceneObject::RemoveAllChildsRecursive()
{
	while (GetChildCount())
	{
		if (RemoveChildRecursive(0))
			return -1;
	}
	return 0;
}

SceneObject* SceneObject::GetChild(size_t i)
{
	return childNodes[i];
}

size_t SceneObject::GetChildCount()
{
	return childNodes.size();
}

void SceneObject::SetLayer(int n)
{
	if (n < 0)
		n = std::max(-MAX_LAYER_COUNT, n) + MAX_LAYER_COUNT;
	layer = std::min(std::max(0, n), MAX_LAYER_COUNT - 1);
}

int SceneObject::GetLayer()
{
	return layer;
}

int SceneObject::IsRunning()
{
	return isRunning;
}

void SceneObject::SetIsRunning(int i)
{
	isRunning = i;
}
