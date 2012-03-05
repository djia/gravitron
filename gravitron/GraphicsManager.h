
#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "Globals.h"
#include "DxUtD3DApp.h"

class CGameManager;

class CGraphicsManager {
private:
	DxUt::CD3DApp * m_D3DApp;
public:
	void Init(HINSTANCE hInst, TCHAR * szClassName, TCHAR * szTitleText,
		WORD wWndPosX, WORD wWndPosY, WORD wWndWidth, WORD wWndHeight, VoidCallback onResizeWindowFunction);

	void BeginGraphicsLoop(VoidCallback GraphicsLoop);

	void GetUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Render();

	void OnResize();

	void Destroy();
};


#endif