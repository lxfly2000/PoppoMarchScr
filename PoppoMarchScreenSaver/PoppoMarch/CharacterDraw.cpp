//WIP
#include "CharacterDraw.h"
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
#define EXPLODE_EFFECT_MAX_RADIUS 200

CharacterDraw::CharacterDraw():SceneObject(),frameCounter(0),hGraph(0),hSoftImage(0),status(0),jumpFrames(CHARACTER_DRAW_DEFAULT_SPEED_JUMP_FRAMES),
posX(0.0f), posY(0.0f), speedX(CHARACTER_DRAW_DEFAULT_SPEED_X), zoom(CHARACTER_DRAW_DEFAULT_ZOOM),
blankPixelsBottom(0),graphWidth(0),graphHeight(0),jumpHeight(0),mouseX(0),mouseY(0)
{
}

int CharacterDraw::RunFrame()
{
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
		if (frameCounter >= EXPLODE_EFFECT_TIME_FRAMES)
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

void CharacterDraw::Explode(int mouse_x, int mouse_y)
{
	status = 1;
	frameCounter = 0;
	mouseX = mouse_x;
	mouseY = mouse_y;
}

void CharacterDraw::SetBlankPixelsBottom(int n)
{
	blankPixelsBottom = n;
}
