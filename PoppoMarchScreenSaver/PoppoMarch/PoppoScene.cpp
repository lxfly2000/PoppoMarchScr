#include "PoppoScene.h"
#include "CharacterDraw.h"
#include "Config.h"
#include <DxLib.h>
#ifdef LONG_PTR
#undef LONG_PTR
#endif

#define DISTANCE_BETWEEN_CHARACTERS 200.0f
#define CHARACTER_Y_TO_BOTTOM 100.0f
#define OTHER_UNITS_START_ORDER 100
#define OTHER_UNITS_NEXT_ORDER 20
#define OTHER_UNITS_NEXT_ORDER_RANGE 40

PoppoScene::~PoppoScene()
{
	for (size_t i = 0; i < GetChildCount(); i++)
		delete GetChild(i);
	RemoveAllChilds();
}

int PoppoScene::Init()
{
	lastClick = FALSE;
	optionAnimationSpeed = ReadInt(KEY_ANIMATION_SPEED);
	otherUnitsOrderCounter = OTHER_UNITS_START_ORDER - OTHER_UNITS_NEXT_ORDER_RANGE / 2 + GetRand(OTHER_UNITS_NEXT_ORDER_RANGE);
	GetDrawScreenSize(&resolutionWidth, &resolutionHeight);
	EnumResourceNames(GetModuleHandle(NULL), TEXT("units"), EnumResNameLoadGraphProcW, (LONG_PTR)this);
	if (hSoftImageOtherUnits.empty())
		EnumResourceNames(GetModuleHandle(NULL), TEXT("units"), EnumResNameLoadSoftImageProcW, (LONG_PTR)this);
	return SceneObject::Init();
}

int PoppoScene::RunFrame()
{
	if (SceneObject::RunFrame())
		return -1;
	if (GetChildCount() == 0 || ((CharacterDraw*)GetChild(GetChildCount() - 1))->GetPosX() + DISTANCE_BETWEEN_CHARACTERS < resolutionWidth + poppoWidth / 2.0f)
	{
		CharacterDraw* c = new CharacterDraw();
		c->SetSpeedX(optionAnimationSpeed + 1.0f);
		c->SetPos(resolutionWidth + poppoWidth / 2, resolutionHeight - CHARACTER_Y_TO_BOTTOM);
		if (otherUnitsOrderCounter <= 0)
		{
			otherUnitsOrderCounter = OTHER_UNITS_NEXT_ORDER - OTHER_UNITS_NEXT_ORDER_RANGE / 2 + GetRand(OTHER_UNITS_NEXT_ORDER_RANGE);
			int index = GetRand(hGraphOtherUnits.size());
			c->SetGraph(hGraphOtherUnits[index], hSoftImageOtherUnits[index]);
		}
		else
		{
			c->SetGraph(hGraphPoppo, hSoftImagePoppo);
		}
		otherUnitsOrderCounter--;
		AddChild(c);
	}
	for (size_t i = 0; i < GetChildCount();)
	{
		CharacterDraw*c = (CharacterDraw*)GetChild(i);
		if ((i == 0 && GetChildCount()>1 && c->GetPosX() < -poppoWidth) || (c->GetStatus() >= 2))
		{
			delete c;
			RemoveChild(i);
		}
		else
		{
			i++;
		}
	}
	int click = GetMouseInput()&MOUSE_INPUT_LEFT;
	if (lastClick == 0 && click)
	{
		int mx, my;
		GetMousePoint(&mx, &my);
		for (size_t i = 0; i < GetChildCount(); i++)
		{
			CharacterDraw* c = (CharacterDraw*)GetChild(i);
			if (c->GetStatus() == 0 && c->HitTest((float)mx, (float)my))
			{
				c->SetLayer(-1);
				c->Explode();
				break;
			}
		}
	}
	lastClick = click;
	return 0;
}

int PoppoScene::End()
{
	for (size_t i = 0; i < hGraphOtherUnits.size(); i++)
		DeleteGraph(hGraphOtherUnits[i]);
	hGraphOtherUnits.clear();
	if (IsRunning() == FALSE)
	{
		for (size_t i = 0; i < hSoftImageOtherUnits.size(); i++)
			DeleteSoftImage(hSoftImageOtherUnits[i]);
		hSoftImageOtherUnits.clear();
	}
	return SceneObject::End();
}

BOOL CALLBACK PoppoScene::EnumResNameLoadGraphProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
	PoppoScene* pThis = (PoppoScene*)lParam;
	int h = LoadGraphToResource(lpName, lpType);
	if (h == 0 || h == -1)
		return FALSE;
	pThis->hGraphOtherUnits.push_back(h);
	if (stricmpDx(lpName, TEXT("poppo_00_00.png")) == 0)
	{
		pThis->hGraphPoppo = h;
		GetGraphSizeF(pThis->hGraphPoppo, &pThis->poppoWidth, &pThis->poppoHeight);
	}
	return TRUE;
}

BOOL CALLBACK PoppoScene::EnumResNameLoadSoftImageProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
	PoppoScene* pThis = (PoppoScene*)lParam;
	LPVOID ptr;
	size_t sz;
	if (GetResourceInfo(lpName, lpType, &ptr, &sz))
		return FALSE;
	int hSI = LoadSoftImageToMem(ptr, sz);
	if (hSI == 0 || hSI == -1)
		return FALSE;
	pThis->hSoftImageOtherUnits.push_back(hSI);
	if (stricmpDx(lpName, TEXT("poppo_00_00.png")) == 0)
	{
		pThis->hSoftImagePoppo = hSI;
	}
	return TRUE;
}
