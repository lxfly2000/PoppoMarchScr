#include "Game\SceneObject.h"
#include <Windows.h>

class PoppoScene :public SceneObject
{
public:
	PoppoScene();
	virtual ~PoppoScene();
	virtual int Init()override;
	virtual int RunFrame()override;
	virtual int End()override;
private:
	int resolutionWidth, resolutionHeight;
	int indexPoppo;
	int otherUnitsOrderCounter;
	int lastClick;
	int optionAnimationSpeed;
	int hSE;
	float poppoWidth, poppoHeight;
	std::vector<int>hGraphUnits;
	std::vector<int>hSoftImageUnits;
	std::vector<int>bottomBlankPixelsUnits;
	static BOOL CALLBACK EnumResNameLoadGraphProcW(HMODULE hModule,LPCWSTR lpType,LPWSTR lpName,LONG_PTR lParam);
	static BOOL CALLBACK EnumResNameLoadSoftImageProcW(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);
};
