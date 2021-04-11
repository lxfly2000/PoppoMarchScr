#include "DxCommon.h"
#include "FPSMeter.h"

FPSMeter::FPSMeter() :tick_prev(0), tick_now(0), frame_count(0), design_fps(0), current_fps(0.0f),
acceptable_min_fps(0), low_fps_counter(0),show_fps(false),pos_x(0),pos_y(0),color(0xFFFFFFFF),SceneObject()
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
	if (show_fps)
		DrawFormatString(pos_x, pos_y, color, TEXT("FPS:%6.2f"), current_fps);
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

void FPSMeter::SetShowFPS(bool s)
{
	show_fps = s;
}

bool FPSMeter::GetShowFPS()
{
	return show_fps;
}

void FPSMeter::SetPos(int n)
{
	int& w = pos_x, & h = pos_y;
	GetDrawScreenSize(&w, &h);
	int x, y, z;
	GetDrawStringSize(&x, &y, &z, TEXT("FPS:000.00"), 10);
	switch (n)
	{
	case 0:default:
		pos_x = pos_y = 0;
		break;
	case 1:
		pos_x = (w - x) / 2;
		pos_y = 0;
		break;
	case 2:
		pos_x = w - x;
		pos_y = 0;
		break;
	case 3:
		pos_x = 0;
		pos_y = (h - y) / 2;
		break;
	case 4:
		pos_x = (w - x) / 2;
		pos_y = (h - y) / 2;
		break;
	case 5:
		pos_x = w - x;
		pos_y = (h - y) / 2;
		break;
	case 6:
		pos_x = 0;
		pos_y = h - y;
		break;
	case 7:
		pos_x = (w - x) / 2;
		pos_y = h - y;
		break;
	case 8:
		pos_x = w - x;
		pos_y = h - y;
		break;
	}
}

void FPSMeter::SetColor(int c)
{
	color = c;
}
