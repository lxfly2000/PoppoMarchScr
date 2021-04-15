//WIP
#include "CharacterDraw.h"
#include <DxLib.h>

#define SHADOW_RADIUS_X 50.0f
#define SHADOW_RADIUS_Y 5.0f

CharacterDraw::CharacterDraw():SceneObject(),frameCounter(0),hGraph(0),hSoftImage(0),status(0),speedJump(CHARACTER_DRAW_DEFAULT_SPEED_JUMP),
posX(0.0f), posY(0.0f), speedX(CHARACTER_DRAW_DEFAULT_SPEED_X), zoom(CHARACTER_DRAW_DEFAULT_ZOOM)
{
}

int CharacterDraw::RunFrame()
{
	if (status == 0)
	{
		posX -= speedX;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);
		DrawOvalAA(posX, posY, 50.0f, 5.0f, 50, GetColor(128, 128, 128), TRUE, 0.0f);
		DrawOvalAA(posX, posY, 50.0f, 5.0f, 50, GetColor(190, 190, 190), FALSE, 3.0f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendGraphF(posX - graphWidth*zoom / 2, posY - graphHeight*zoom + blankPixelsBottom*zoom, posX + graphWidth*zoom / 2, posY + blankPixelsBottom*zoom, hGraph, TRUE);
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

void CharacterDraw::SetSpeedJump(float v)
{
}

void CharacterDraw::SetZoom(float z)
{
    zoom = z;
}

bool CharacterDraw::HitTest(float x, float y)
{
	float rx = (x - posX) / zoom + graphWidth / 2;
	float ry = (y - posY) / zoom + graphHeight - blankPixelsBottom*zoom;
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

void CharacterDraw::Explode()
{
	status = 2;
}

void CharacterDraw::SetBlankPixelsBottom(int n)
{
	blankPixelsBottom = n;
}
