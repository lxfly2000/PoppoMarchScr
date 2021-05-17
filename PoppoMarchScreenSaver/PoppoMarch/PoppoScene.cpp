#include "PoppoScene.h"
#include "CharacterDraw.h"
#include "Config.h"
#include <DxLib.h>
#ifdef LONG_PTR
#undef LONG_PTR
#endif

#define DISTANCE_BETWEEN_CHARACTERS 250.0f
#define CHARACTER_Y_TO_BOTTOM 80.0f
#define OTHER_UNITS_START_ORDER 100
#define OTHER_UNITS_NEXT_ORDER 20
#define OTHER_UNITS_NEXT_ORDER_RANGE 40
#define FADE_SCREEN_TIME_MS 250

static int hFadeScreenGraph[13];//其中有一个用于实时显示
static int hFadeScreen;
static int iFadeScreen;
static int frameCounter;

PoppoScene::PoppoScene():hSE(0),indexPoppo(0),lastClick(0),optionAnimationSpeed(0),otherUnitsOrderCounter(0),poppoWidth(0),poppoHeight(0),
resolutionWidth(0),resolutionHeight(0)
{
}

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
	int h = LoadGraphToResource(TEXT("spark.png"), TEXT("png"));
	if (h == 0 || h == -1)
		return -2;
	CharacterDraw::SetSparkGraph(h);
	if (hSoftImageUnits.empty())
		EnumResourceNames(GetModuleHandle(NULL), TEXT("units"), EnumResNameLoadSoftImageProcW, (LONG_PTR)this);
	if (hSE == 0)
	{
		hSE = LoadSoundMemByResource(TEXT("click.wav"), TEXT("se"));
		if (hSE == 0 || hSE == -1)
			return -1;
	}
	if (optionAnimationSpeed > 3)
	{
		hFadeScreen = MakeScreen(resolutionWidth, resolutionHeight, TRUE);
		for (int i = 0; i < ARRAYSIZE(hFadeScreenGraph); i++)
			hFadeScreenGraph[i] = MakeGraph(resolutionWidth, resolutionHeight);
		iFadeScreen = 0;
		frameCounter = 0;
	}
	return SceneObject::Init();
}

int PoppoScene::RunFrame()
{
	int previousDrawScreen = GetDrawScreen();
	if (optionAnimationSpeed >3)
	{
		SetDrawScreen(hFadeScreen);
		ClearDrawScreen();
	}
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
			int index = GetRand(hGraphUnits.size());
			c->SetGraph(hGraphUnits[index], hSoftImageUnits[index]);
			c->SetBlankPixelsBottom(bottomBlankPixelsUnits[index]);
		}
		else
		{
			c->SetGraph(hGraphUnits[indexPoppo], hSoftImageUnits[indexPoppo]);
			c->SetBlankPixelsBottom(bottomBlankPixelsUnits[indexPoppo]);
		}
		otherUnitsOrderCounter--;
		AddChild(c);
	}
	for (size_t i = 0; i < GetChildCount();)
	{
		CharacterDraw*c = (CharacterDraw*)GetChild(i);
		if ((i == 0 && GetChildCount()>1 && c->GetPosX() < -poppoWidth/2) || (c->GetStatus() >= 2))
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
				c->Explode(mx, my);
				PlaySoundMem(hSE, DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
	lastClick = click;
	if (optionAnimationSpeed >3)
	{
		GetDrawScreenGraph(0, 0, resolutionWidth, resolutionHeight, hFadeScreenGraph[iFadeScreen]);
		SetDrawScreen(previousDrawScreen);
		int previousBlend, previousParam;
		GetDrawBlendMode(&previousBlend, &previousParam);
		if (optionAnimationSpeed == 5)//倒序显示
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawGraph(0, 0, hFadeScreenGraph[iFadeScreen], TRUE);
			for (int i = ARRAYSIZE(hFadeScreenGraph) - 1; i >= 1; i--)
			{
				//255/(ARRAYSIZE(hFadeScreenGraph)-1)*(i-1)+255/(ARRAYSIZE(hFadeScreenGraph)-1)*(1-frameCounter/(FADE_SCREEN_TIME_MS*GetRefreshRate()/(ARRAYSIZE(hFadeScreenGraph)-1)/1000))
				int alpha = 255 * i / (ARRAYSIZE(hFadeScreenGraph) - 1) - 255 * frameCounter * 1000 / (FADE_SCREEN_TIME_MS*GetRefreshRate());
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(0.0007*(exp(alpha*0.05) - 1)));//指数变化
				DrawGraph(0, 0, hFadeScreenGraph[(iFadeScreen + i) % ARRAYSIZE(hFadeScreenGraph)], TRUE);
			}
		}
		else//顺序显示
		{
			for (int i = 1; i < ARRAYSIZE(hFadeScreenGraph); i++)
			{
				//255/(ARRAYSIZE(hFadeScreenGraph)-1)*(i-1)+255/(ARRAYSIZE(hFadeScreenGraph)-1)*(1-frameCounter/(FADE_SCREEN_TIME_MS*GetRefreshRate()/(ARRAYSIZE(hFadeScreenGraph)-1)/1000))
				int alpha = 255 * i / (ARRAYSIZE(hFadeScreenGraph) - 1) - 255 * frameCounter * 1000 / (FADE_SCREEN_TIME_MS*GetRefreshRate());
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(0.0007*(exp(alpha*0.05) - 1)));//指数变化
				DrawGraph(0, 0, hFadeScreenGraph[(iFadeScreen + i) % ARRAYSIZE(hFadeScreenGraph)], TRUE);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawGraph(0, 0, hFadeScreenGraph[iFadeScreen], TRUE);
		}
		SetDrawBlendMode(previousBlend, previousParam);
		if (ARRAYSIZE(hFadeScreenGraph) > 1)
		{
			frameCounter++;
			if (frameCounter *(ARRAYSIZE(hFadeScreenGraph) - 1) * 1000 >= FADE_SCREEN_TIME_MS * GetRefreshRate())
			{
				frameCounter = 0;
				iFadeScreen = (iFadeScreen + 1) % ARRAYSIZE(hFadeScreenGraph);
			}
		}
	}
	return 0;
}

int PoppoScene::End()
{
	for (size_t i = 0; i < hGraphUnits.size(); i++)
		DeleteGraph(hGraphUnits[i]);
	hGraphUnits.clear();
	DeleteGraph(CharacterDraw::GetSparkGraph());
	if (IsRunning() == FALSE)
	{
		DeleteSoundMem(hSE);
		for (size_t i = 0; i < hSoftImageUnits.size(); i++)
			DeleteSoftImage(hSoftImageUnits[i]);
		hSoftImageUnits.clear();
	}
	return SceneObject::End();
}

BOOL CALLBACK PoppoScene::EnumResNameLoadGraphProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam)
{
	PoppoScene* pThis = (PoppoScene*)lParam;
	int h = LoadGraphToResource(lpName, lpType);
	if (h == 0 || h == -1)
		return FALSE;
	if (stricmpDx(lpName, TEXT("poppo_00_00.png")) == 0)
	{
		pThis->indexPoppo = pThis->hGraphUnits.size();
		GetGraphSizeF(h, &pThis->poppoWidth, &pThis->poppoHeight);
	}
	pThis->hGraphUnits.push_back(h);
	return TRUE;
}

int GetBlankPixelsBottom(int siHandle)
{
	int w, h;
	GetSoftImageSize(siHandle, &w, &h);
	int cx = w / 2, cy = h - 1;
	int r, g, b, a;
	//先从下方中间点往上找，再逐行往下
	while (cy >= 0)
	{
		GetPixelSoftImage(siHandle, cx, cy, &r, &g, &b, &a);
		if (a)
			break;
		cy--;
	}
	int &x = cx;
	for (int y = cy; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			GetPixelSoftImage(siHandle, x, y, &r, &g, &b, &a);
			if (a)
				cy = y;
		}
	}
	return h - cy - 1;
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
	pThis->hSoftImageUnits.push_back(hSI);
	pThis->bottomBlankPixelsUnits.push_back(GetBlankPixelsBottom(hSI));
	return TRUE;
}
