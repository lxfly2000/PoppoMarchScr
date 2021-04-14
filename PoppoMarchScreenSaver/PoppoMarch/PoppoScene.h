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
	int hGraphPoppo;
	int otherUnitsOrderCounter;
	float poppoWidth, poppoHeight;
	std::vector<int>hGraphOtherUnits;
	static BOOL CALLBACK EnumResnameProcW(HMODULE hModule,LPCWSTR lpType,LPWSTR lpName,LONG_PTR lParam);
};
