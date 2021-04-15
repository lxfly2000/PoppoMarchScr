#include "BubbleScene.h"
#include "Bubble.h"
#include <DxLib.h>

#define COLOR_LIGHT_R 255
#define COLOR_LIGHT_G 251
#define COLOR_LIGHT_B 242
#define COLOR_DARK_R 249
#define COLOR_DARK_G 186
#define COLOR_DARK_B 30
#define BUBBLE_COLOR_LEVELS 10
#define BUBBLE_MAX_COUNT 50
#define CHANGE_TARGETING_POINT_TIME_SECONDS 12
#define BUBBLE_COUNT_RANGE_DELTA 20

int GetBubbleColor(int n)
{
	return GetColor(n * (COLOR_LIGHT_R - COLOR_DARK_R) / BUBBLE_COLOR_LEVELS + COLOR_DARK_R,
		n * (COLOR_LIGHT_G - COLOR_DARK_G) / BUBBLE_COLOR_LEVELS + COLOR_DARK_G,
		n * (COLOR_LIGHT_B - COLOR_DARK_B) / BUBBLE_COLOR_LEVELS + COLOR_DARK_B);
}

BubbleScene::~BubbleScene()
{
	for (size_t i = 0; i < GetChildCount(); i++)
		delete GetChild(i);
	RemoveAllChilds();
}

int BubbleScene::Init()
{
	GetDrawScreenSize(&resolutionWidth, &resolutionHeight);
	floatingPointX[0] = resolutionWidth / 2 - resolutionHeight * 10 * sinf(DX_PI / 6);
	floatingPointY[0] = resolutionHeight / 2 - resolutionHeight * 10 * cosf(DX_PI / 6);
	floatingPointX[1] = -floatingPointX[0];
	floatingPointY[1] = floatingPointY[0];
	targetingPoint = GetRand(2);
	fps = GetRefreshRate();
	frameCounter = 0;
	if (GetChildCount() == 0)
	{
		for (int i = 0; i < BUBBLE_MAX_COUNT; i++)
		{
			Bubble* bubble = new Bubble();
			bubble->SetPos(GetRand(resolutionWidth), GetRand(resolutionHeight));
			bubble->SetToPos(floatingPointX[targetingPoint], floatingPointY[targetingPoint]);
			bubble->SetRadius(BUBBLE_MIN_RADIUS + GetRand(BUBBLE_MAX_RADIUS - BUBBLE_MIN_RADIUS));
			bubble->SetColor(GetBubbleColor(GetRand(BUBBLE_COLOR_LEVELS)));
			AddChild(bubble);
		}
	}

	return SceneObject::Init();
}

int BubbleScene::RunFrame()
{
	if (SceneObject::RunFrame())
		return -1;
	for (size_t i = 0; i < GetChildCount();)
	{
		Bubble* bubble = (Bubble*)GetChild(i);
		if (bubble->GetPosY() < -BUBBLE_MAX_RADIUS || bubble->GetPosX() < -BUBBLE_MAX_RADIUS || bubble->GetPosX() > resolutionWidth + BUBBLE_MAX_RADIUS)
		{
			delete bubble;
			RemoveChild(i);
		}
		else
		{
			i++;
		}
	}
	//BUG:不知为什么Bubble对象的toY在初始化的时候偶尔会出现为0的情况…然后我把“frameCounter=”那句从这行放到后面这个问题就没了？？
#ifdef _DEBUG
	if (abs(((Bubble*)GetChild(0))->GetToPosY()) < resolutionHeight)
		puts("Unexpected toY.");
#endif
	if (frameCounter == 0)
	{
		targetingPoint = (targetingPoint + 1) % ARRAYSIZE(floatingPointX);
		for (size_t i = 0; i < GetChildCount(); i++)
		{
			Bubble* bubble = (Bubble*)GetChild(i);
			bubble->SetToPos(floatingPointX[targetingPoint], floatingPointY[targetingPoint]);
		}
	}
	//这个判断是瞎写的，勿当真（
	if (frameCounter % (int)ceilf(fps / BUBBLE_MAX_SPEED / BUBBLE_MAX_ACC) == 0 && BUBBLE_MAX_COUNT - BUBBLE_COUNT_RANGE_DELTA / 2 + GetRand(BUBBLE_COUNT_RANGE_DELTA) > GetChildCount())
	{
		Bubble* bubble = new Bubble();
		int rnd = GetRand(resolutionWidth + resolutionHeight);
		if (targetingPoint)//向右
		{
			if (rnd < resolutionHeight)//在左边出现
				bubble->SetPos(-BUBBLE_MAX_RADIUS, rnd);
			else//在下边出现
				bubble->SetPos(rnd - resolutionHeight, resolutionHeight + BUBBLE_MAX_RADIUS);
		}
		else//向左
		{
			if (rnd < resolutionHeight)//在右边出现
				bubble->SetPos(resolutionWidth + BUBBLE_MAX_RADIUS, rnd);
			else//在下边出现
				bubble->SetPos(rnd - resolutionHeight, resolutionHeight + BUBBLE_MAX_RADIUS);
		}
		bubble->SetToPos(floatingPointX[targetingPoint], floatingPointY[targetingPoint]);
		bubble->SetRadius(BUBBLE_MIN_RADIUS + GetRand(BUBBLE_MAX_RADIUS - BUBBLE_MIN_RADIUS));
		bubble->SetColor(GetBubbleColor(GetRand(BUBBLE_COLOR_LEVELS)));
		AddChild(bubble);
	}
#ifdef _DEBUG
	static int showDbgX = 0, showDbgY = 0;
	if (showDbgX == 0)
	{
		int x, y, z;
		GetDrawScreenSize(&showDbgX, &y);
		GetDrawStringSize(&x, &y, &z, TEXT("BUBBLES:000"), 11);
		showDbgX -= x;
		showDbgY += y;
	}
	DrawFormatString(showDbgX, showDbgY, GetColor(255, 0, 255), TEXT("BUBBLES:%3d"), GetChildCount());
#endif
	frameCounter = (frameCounter + 1) % (CHANGE_TARGETING_POINT_TIME_SECONDS * fps);
	return 0;
}
