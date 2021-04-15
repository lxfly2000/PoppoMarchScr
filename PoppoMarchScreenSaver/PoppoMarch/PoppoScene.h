#include "Game\SceneObject.h"
#include <Windows.h>

class PoppoScene :public SceneObject
{
public:
	virtual ~PoppoScene();
	virtual int Init()override;
	virtual int RunFrame()override;
	virtual int End()override;
private:
	int resolutionWidth, resolutionHeight;
	int hGraphPoppo,hSoftImagePoppo;
	int otherUnitsOrderCounter;
	int lastClick;
	int optionAnimationSpeed;
	float poppoWidth, poppoHeight;
	std::vector<int>hGraphOtherUnits;
	std::vector<int>hSoftImageOtherUnits;
	static BOOL CALLBACK EnumResNameLoadGraphProcW(HMODULE hModule,LPCWSTR lpType,LPWSTR lpName,LONG_PTR lParam);
	static BOOL CALLBACK EnumResNameLoadSoftImageProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);
};
