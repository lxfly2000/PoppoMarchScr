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
#define CHANGE_TARGETING_POINT_TIME_SECONDS 10

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
		if (bubble->GetPosY() < -BUBBLE_MAX_RADIUS * 2 || bubble->GetPosX() < -BUBBLE_MAX_RADIUS * 2 || bubble->GetPosX() > resolutionWidth + BUBBLE_MAX_RADIUS * 2)
		{
			delete bubble;
			RemoveChild(i);
		}
		else
		{
			i++;
		}
	}
	frameCounter = (frameCounter + 1) % (CHANGE_TARGETING_POINT_TIME_SECONDS * fps);
	if (frameCounter == 0)
	{
		targetingPoint = (targetingPoint + 1) % ARRAYSIZE(floatingPointX);
		for (size_t i = 0; i < GetChildCount(); i++)
		{
			Bubble* bubble = (Bubble*)GetChild(i);
			bubble->SetToPos(floatingPointX[targetingPoint], floatingPointY[targetingPoint]);
		}
	}
	if (frameCounter % (fps / 10) == 0 && BUBBLE_MAX_COUNT - 10 + GetRand(20) > GetChildCount())
	{
		Bubble* bubble = new Bubble();
		bubble->SetPos(GetRand(resolutionWidth), GetRand(resolutionHeight));
		if (targetingPoint)
		{
			if (bubble->GetPosX() > resolutionWidth / 2)
				bubble->SetPos(-BUBBLE_MAX_RADIUS * 2, bubble->GetPosY());
			else
				bubble->SetPos(bubble->GetPosX(), resolutionHeight + BUBBLE_MAX_RADIUS * 2);
		}
		else
		{
			if (bubble->GetPosX() < resolutionWidth / 2)
				bubble->SetPos(resolutionWidth + BUBBLE_MAX_RADIUS * 2, bubble->GetPosY());
			else
				bubble->SetPos(bubble->GetPosX(), resolutionHeight + BUBBLE_MAX_RADIUS * 2);
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
	return 0;
}
