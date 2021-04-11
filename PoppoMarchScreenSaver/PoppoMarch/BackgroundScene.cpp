#include "BackgroundScene.h"
#include <DxLib.h>

int BackgroundScene::Init()
{
	int w, h;
	GetDrawScreenSize(&w, &h);
	grBg = MakeGraph(w, h);
	int scBg = MakeScreen(w, h);
	int bksc = GetDrawScreen();
	SetDrawScreen(scBg);
	COLOR_U8 colorLight = GetColorU8(255, 241, 219, 255);
	COLOR_U8 colorDark = GetColorU8(247, 160, 58, 255);
	COLOR_U8 colorMedium = GetColorU8((colorLight.r + colorDark.r) / 2, (colorLight.g + colorDark.g) / 2, (colorLight.b + colorDark.b) / 2, 255);
	VERTEX2D v[4] = {//根据文档rhw设为1即可
		{VGet(0,0,0),1.0f,colorLight,0,0},
		{VGet(w,0,0),1.0f,colorMedium,0,0},
		{VGet(0,h,0),1.0f,colorMedium,0,0},
		{VGet(w,h,0),1.0f,colorDark,0,0}
	};
	unsigned short idx[] = { 0,1,2,1,3,2 };
	DrawPolygonIndexed2D(v, ARRAYSIZE(v), idx, 2, DX_NONE_GRAPH, FALSE);
	if (GetDrawScreenGraph(0, 0, w, h, grBg))
		return -1;
	SetDrawScreen(bksc);
	return 0;
}

int BackgroundScene::RunFrame()
{
	DrawGraph(0, 0, grBg, FALSE);
	return 0;
}

int BackgroundScene::End()
{
	DeleteGraph(grBg);
	return 0;
}
