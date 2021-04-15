//WIP
#include "CharacterDraw.h"
#include <DxLib.h>

CharacterDraw::CharacterDraw():SceneObject(),frameCounter(0),hGraph(0),hSoftImage(0),status(0),speedJump(CHARACTER_DRAW_DEFAULT_SPEED_JUMP),
posX(0.0f), posY(0.0f), speedX(CHARACTER_DRAW_DEFAULT_SPEED_X), zoom(CHARACTER_DRAW_DEFAULT_ZOOM)
{
}

int CharacterDraw::RunFrame()
{
	if (status == 0)
	{
		posX -= speedX;
		DrawExtendGraphF(posX - graphWidth*zoom / 2, posY - graphHeight*zoom, posX + graphWidth*zoom / 2, posY, hGraph, TRUE);
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
	float ry = (y - posY) / zoom + graphHeight;
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
