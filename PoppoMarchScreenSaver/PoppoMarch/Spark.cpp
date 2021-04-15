#include "Spark.h"
#include <DxLib.h>

float Spark::graphWidth = 0.0f;
float Spark::graphHeight = 0.0f;

Spark::Spark(float sx, float sy, float vx, float vy, float _angle, float _zoom, int time_frames_a):SceneObject(),frameCounter(0),
startX(sx),startY(sy),vX(vx),vY(vy),angle(_angle),zoom(_zoom),timeFramesA(time_frames_a),hGraph(0)
{
}

int Spark::RunFrame()
{
	DrawRotaGraph2F(startX + vX * frameCounter, startY + vY * frameCounter, graphWidth / 2.0f, graphHeight / 2.0f, zoom, angle, hGraph, TRUE);
	frameCounter++;
	return 0;
}

bool Spark::IsDisappeared()
{
	return frameCounter >= timeFramesA;
}

void Spark::SetGraph(int gr)
{
	hGraph = gr;
	if (graphWidth == 0.0f)
		GetGraphSizeF(hGraph, &graphWidth, &graphHeight);
}
