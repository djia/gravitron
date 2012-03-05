
#include "GameManager.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, PSTR line, int show)
{
	CGameManager::GetGameManager().Init(hInst);

	CGameManager::GetGameManager().Run();

	return 0;
}