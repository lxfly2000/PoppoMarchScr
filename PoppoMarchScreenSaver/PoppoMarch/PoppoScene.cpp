#include "PoppoScene.h"
#include "CharacterDraw.h"
#include <DxLib.h>
#ifdef LONG_PTR
#undef LONG_PTR
#endif

#define DISTANCE_BETWEEN_CHARACTERS 100.0f
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
	otherUnitsOrderCounter = OTHER_UNITS_START_ORDER - OTHER_UNITS_NEXT_ORDER_RANGE / 2 + GetRand(OTHER_UNITS_NEXT_ORDER_RANGE);
	GetDrawScreenSize(&resolutionWidth, &resolutionHeight);
	GetGraphSizeF(hGraphPoppo, &poppoWidth, &poppoHeight);
	if (hGraphOtherUnits.empty())
		EnumResourceNames(GetModuleHandle(NULL), TEXT("units"), EnumResnameProcW, (LONG_PTR)this);
	return SceneObject::Init();
}

int PoppoScene::RunFrame()
{
	if (SceneObject::RunFrame())
		return -1;
	if (GetChildCount() == 0 || ((CharacterDraw*)GetChild(GetChildCount() - 1))->GetPosX() + DISTANCE_BETWEEN_CHARACTERS < (float)resolutionWidth)
	{
		CharacterDraw* c = new CharacterDraw();
		c->SetPos(resolutionWidth + poppoWidth / 2, resolutionHeight - CHARACTER_Y_TO_BOTTOM);
		if (otherUnitsOrderCounter <= 0)
		{
			otherUnitsOrderCounter = OTHER_UNITS_NEXT_ORDER - OTHER_UNITS_NEXT_ORDER_RANGE / 2 + GetRand(OTHER_UNITS_NEXT_ORDER_RANGE);
			c->SetGraph(hGraphOtherUnits[GetRand(hGraphOtherUnits.size())]);
		}
		else
		{
			c->SetGraph(hGraphPoppo);
		}
		otherUnitsOrderCounter--;
		AddChild(c);
	}
	if (GetChildCount() > 1)
	{
		CharacterDraw* c = (CharacterDraw*)GetChild(0);
		if (c->GetPosX() < -poppoWidth)
		{
			delete c;
			RemoveChild(0);
		}
	}
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
	return 0;
}

int PoppoScene::End()
{
	if (IsRunning() == 0)
	{
		for (size_t i = 0; i < hGraphOtherUnits.size(); i++)
			DeleteGraph(hGraphOtherUnits[i]);
		hGraphOtherUnits.clear();
	}
	return SceneObject::End();
}

BOOL CALLBACK PoppoScene::EnumResnameProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
	PoppoScene* pThis = (PoppoScene*)lParam;
	int h = LoadGraphToResource(lpName, lpType);
	if (h == 0 || h == -1)
		return FALSE;
	pThis->hGraphOtherUnits.push_back(h);
	if (stricmpDx(lpName, TEXT("poppo_00_00.png")) == 0)
		pThis->hGraphPoppo = h;
	return TRUE;
}
