//WIP
#include "CharacterDraw.h"
#include "Spark.h"
#include "Game/DxCommon.h"
#include <DxLib.h>

#define SHADOW_RADIUS_X 72.0f
#define SHADOW_RADIUS_Y 10.0f
#define SHADOW_COLOR_FILL_R 128
#define SHADOW_COLOR_FILL_G 128
#define SHADOW_COLOR_FILL_B 128
#define SHADOW_COLOR_EDGE_R 190
#define SHADOW_COLOR_EDGE_G 190
#define SHADOW_COLOR_EDGE_B 190
#define SHADOW_EDGE_WIDTH 3.0f
#define SHADOW_ALPHA 240
#define EXPLODE_EFFECT_TIME_FRAMES 30
#define EXPLODE_EFFECT_MAX_RADIUS 160.0f
#define EXPLODE_EFFECT_MIN_RADIUS 100.0f
#define EXPLODE_EFFECT_MIN_OBJECTS 5
#define EXPLODE_EFFECT_MAX_OBJECTS 10
#define EXPLODE_EFFECT_OBJECT_MIN_ZOOM 0.2f
#define EXPLODE_EFFECT_OBJECT_MAX_ZOOM 1.0f

int CharacterDraw::hGraphSpark = 0;

CharacterDraw::CharacterDraw():SceneObject(),frameCounter(0),hGraph(0),hSoftImage(0),status(0),jumpFrames(CHARACTER_DRAW_DEFAULT_SPEED_JUMP_FRAMES),
posX(0.0f), posY(0.0f), speedX(CHARACTER_DRAW_DEFAULT_SPEED_X), zoom(CHARACTER_DRAW_DEFAULT_ZOOM),
blankPixelsBottom(0),graphWidth(0),graphHeight(0),jumpHeight(0)
{
}

int CharacterDraw::RunFrame()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (EXPLODE_EFFECT_TIME_FRAMES - frameCounter) * 255 / EXPLODE_EFFECT_TIME_FRAMES);
	SceneObject::RunFrame();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (status == 0)
	{
		posX -= speedX;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SHADOW_ALPHA);
		DrawOvalAA(posX, posY, SHADOW_RADIUS_X, SHADOW_RADIUS_Y, 50, GetColor(SHADOW_COLOR_FILL_R, SHADOW_COLOR_FILL_G, SHADOW_COLOR_FILL_B), TRUE, 0.0f);
		DrawOvalAA(posX, posY, SHADOW_RADIUS_X, SHADOW_RADIUS_Y, 50, GetColor(SHADOW_COLOR_EDGE_R, SHADOW_COLOR_EDGE_G, SHADOW_COLOR_EDGE_B), FALSE, SHADOW_EDGE_WIDTH);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendGraphF(posX - graphWidth * zoom / 2, posY - graphHeight * zoom + blankPixelsBottom * zoom - jumpHeight,
			posX + graphWidth * zoom / 2, posY + blankPixelsBottom * zoom - jumpHeight, hGraph, TRUE);

		float dt = abs(frameCounter - jumpFrames / 2.0f);
		jumpHeight = CHARACTER_DRAW_DEFAULT_JUMP_HEIGHT_PIXELS - 4.0f * CHARACTER_DRAW_DEFAULT_JUMP_HEIGHT_PIXELS / jumpFrames / jumpFrames * dt * dt;
		frameCounter = (frameCounter + 1) % jumpFrames;
	}
	else if (status == 1)
	{
		for (size_t i = 0; i < GetChildCount();)
		{
			Spark* s = (Spark*)GetChild(i);
			if (s->IsDisappeared())
			{
				delete s;
				RemoveChild(i);
			}
			else
			{
				i++;
			}
		}
		if (GetChildCount() == 0)
			status = 2;
		frameCounter++;
	}
#ifdef _DEBUG
	DrawTriangleAA(posX, posY, posX - graphWidth*zoom / 2, posY - graphHeight*zoom, posX + graphWidth*zoom / 2, posY - graphHeight*zoom, 0xFF000000, FALSE);
#endif
    return 0;
}

void CharacterDraw::SetGraph(int grHandle,int siHandle)
{
    hGraph = grHandle;
	hSoftImage = siHandle;
	GetGraphSizeF(hGraph, &graphWidth, &graphHeight);
}

void CharacterDraw::SetPos(float x, float y)
{
    posX = x;
    posY = y;
}

void CharacterDraw::SetSpeedX(float v)
{
	speedX = v;
}

void CharacterDraw::SetJumpFrames(int n)
{
	jumpFrames = n;
}

void CharacterDraw::SetZoom(float z)
{
    zoom = z;
}

bool CharacterDraw::HitTest(float x, float y)
{
	float rx = (x - posX) / zoom + graphWidth / 2;
	float ry = (y - posY) / zoom + graphHeight - blankPixelsBottom * zoom + jumpHeight;
	int r, g, b, a;
	GetPixelSoftImage(hSoftImage, rx, ry, &r, &g, &b, &a);
	return a > 0;
}

float CharacterDraw::GetPosX()
{
    return posX;
}

int CharacterDraw::GetStatus()
{
    return status;
}

void CharacterDraw::Explode(int x, int y)
{
	status = 1;
	frameCounter = 0;

	int nObj = GetRand(EXPLODE_EFFECT_MAX_OBJECTS - EXPLODE_EFFECT_MIN_OBJECTS + 1) + EXPLODE_EFFECT_MIN_OBJECTS;
	for (int i = 0; i < nObj; i++)
	{
		float zoom = GetRandFloat(EXPLODE_EFFECT_OBJECT_MAX_ZOOM - EXPLODE_EFFECT_OBJECT_MIN_ZOOM, 100) + EXPLODE_EFFECT_OBJECT_MIN_ZOOM;
		float r = GetRandFloat(EXPLODE_EFFECT_MAX_RADIUS - EXPLODE_EFFECT_MIN_RADIUS, 100) + EXPLODE_EFFECT_MIN_RADIUS;
		float angle = DegToRad(GetRand(360));
		float v = r / EXPLODE_EFFECT_TIME_FRAMES;
		Spark* s = new Spark((float)x, (float)y, v * cosf(angle), v * sinf(angle), angle, zoom, EXPLODE_EFFECT_TIME_FRAMES);
		s->SetGraph(hGraphSpark);
		AddChild(s);
	}
}

void CharacterDraw::SetBlankPixelsBottom(int n)
{
	blankPixelsBottom = n;
}

void CharacterDraw::SetSparkGraph(int gr)
{
	hGraphSpark = gr;
}

int CharacterDraw::GetSparkGraph()
{
	return hGraphSpark;
}
