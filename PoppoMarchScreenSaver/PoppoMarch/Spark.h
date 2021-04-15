#pragma once
#include "Game/SceneObject.h"

class Spark :public SceneObject
{
public:
	Spark(float sx, float sy, float vx, float vy, float _angle, float _zoom, int time_frames_a);
	virtual int RunFrame()override;
	bool IsDisappeared();
	void SetGraph(int gr);
private:
	static float graphWidth, graphHeight;
	float startX, startY, vX, vY, angle, zoom;
	int timeFramesA;
	int frameCounter;
	int hGraph;
};
