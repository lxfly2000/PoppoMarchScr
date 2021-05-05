#pragma once
#include "SceneObject.h"
class FPSMeter:public SceneObject
{
public:
	FPSMeter();
	//这个主要用来提示用户当实际帧速率与设计帧速率不符时发出警告
	void SetDesignFPS(int fps);
	int RunFrame()override;
	float CalcFPS();
	float GetFPS()const;
	int tick_prev, tick_now;
	void SetShowFPS(bool s);
	bool GetShowFPS();
	//0 1 2
	//3 4 5
	//6 7 8
	void SetPos(int);
	void SetColor(int);
private:
	int frame_count;
	int design_fps;
	int acceptable_min_fps;
	int low_fps_counter;
	float current_fps;
	bool show_fps;
	int pos_x, pos_y;
	int color;
};
