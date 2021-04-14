//WIP
#include "CharacterDraw.h"

CharacterDraw::CharacterDraw():SceneObject(),frameCounter(0),hPic(0),status(0),speedJump(CHARACTER_DRAW_DEFAULT_SPEED_JUMP),
posX(0.0f),posY(0.0f),speedX(CHARACTER_DRAW_DEFAULT_SPEED_X),zoom(1.0f)
{
}

int CharacterDraw::RunFrame()
{
    posX -= speedX;
    return 0;
}

void CharacterDraw::SetGraph(int grHandle)
{
    hPic = grHandle;
}

void CharacterDraw::SetPos(float x, float y)
{
    posX = x;
    posY = y;
}

void CharacterDraw::SetSpeedX(float v)
{
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
    return false;
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
}
