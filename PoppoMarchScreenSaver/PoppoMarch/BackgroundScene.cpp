#include "BackgroundScene.h"
#include "Bubble.h"
#include <DxLib.h>

#define COLOR_LIGHT_R 255
#define COLOR_LIGHT_G 251
#define COLOR_LIGHT_B 242
#define COLOR_DARK_R 247
#define COLOR_DARK_G 160
#define COLOR_DARK_B 58

int BackgroundScene::Init()
{
	GetDrawScreenSize(&resolutionWidth, &resolutionHeight);
	grBg = MakeGraph(resolutionWidth, resolutionHeight);
	int scBg = MakeScreen(resolutionWidth, resolutionHeight);
	int bksc = GetDrawScreen();
	SetDrawScreen(scBg);
	COLOR_U8 colorLight = GetColorU8(COLOR_LIGHT_R, COLOR_LIGHT_G, COLOR_LIGHT_B, 255);
	COLOR_U8 colorDark = GetColorU8(COLOR_DARK_R, COLOR_DARK_G, COLOR_DARK_B, 255);
	COLOR_U8 colorMedium = GetColorU8((colorLight.r + colorDark.r) / 2, (colorLight.g + colorDark.g) / 2, (colorLight.b + colorDark.b) / 2, 255);
	VERTEX2D v[4] = {//根据文档rhw设为1即可
		{VGet(0,0,0),1.0f,colorLight,0,0},
		{VGet(resolutionWidth,0,0),1.0f,colorMedium,0,0},
		{VGet(0,resolutionHeight,0),1.0f,colorMedium,0,0},
		{VGet(resolutionWidth,resolutionHeight,0),1.0f,colorDark,0,0}
	};
	unsigned short idx[] = { 0,1,2,1,3,2 };
	DrawPolygonIndexed2D(v, ARRAYSIZE(v), idx, 2, DX_NONE_GRAPH, FALSE);
	if (GetDrawScreenGraph(0, 0, resolutionWidth, resolutionHeight, grBg))
		return -1;
	SetDrawScreen(bksc);

	return SceneObject::Init();
}

int BackgroundScene::RunFrame()
{
	DrawGraph(0, 0, grBg, FALSE);
	return SceneObject::RunFrame();
}

int BackgroundScene::End()
{
	if (SceneObject::End())
		return -1;
	DeleteGraph(grBg);
	return 0;
}
