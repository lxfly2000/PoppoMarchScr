#pragma once
#include "SceneObject.h"
class FPSMeter:public SceneObject
{
public:
	FPSMeter();
	void SetDesignFPS(int fps);
	int RunFrame()override;
	float CalcFPS();
	float GetFPS()const;
	int tick_prev, tick_now;
private:
	int frame_count;
	int design_fps;
	int acceptable_min_fps;
	int low_fps_counter;
	float current_fps;
};
