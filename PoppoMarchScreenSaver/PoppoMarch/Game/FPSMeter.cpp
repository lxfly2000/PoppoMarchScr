#include "DxCommon.h"
#include "FPSMeter.h"

FPSMeter::FPSMeter() :tick_prev(0), tick_now(0), frame_count(0), design_fps(0), current_fps(0.0f),
acceptable_min_fps(0), low_fps_counter(0),SceneObject()
{
}

void FPSMeter::SetDesignFPS(int fps)
{
	design_fps = fps;
	acceptable_min_fps = design_fps * 80 / 100;
}

int FPSMeter::RunFrame()
{
	if ((++frame_count) % design_fps == 0)
	{
		current_fps = CalcFPS();
		if (current_fps < acceptable_min_fps)
		{
			if ((++low_fps_counter) >= 3)
				AppLogAdd(TEXT("程序运行速度过慢，请关闭一些不必要的程序。FPS：%.2f\n"), current_fps);
		}
		else
		{
			low_fps_counter = 0;
		}
	}
	return 0;
}

float FPSMeter::CalcFPS()
{
	tick_prev = tick_now;
	tick_now = GetNowCount();
	return 1000.0f * design_fps / (tick_now - tick_prev);
}

float FPSMeter::GetFPS() const
{
	return current_fps;
}
