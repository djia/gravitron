
#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "Globals.h"
#include "DxUtD3DApp.h"
#include "BaseEntity.h"
//#include "DxUtFPCamera.h"
#include "DxUtLight.h"
#include "DxUtOrbitCamera.h"

class CGameManager;
class CObjectManager;

class CGraphicsManager {
private:
	friend class CGameManager;

	DxUt::CD3DApp * m_D3DApp;

	std::vector<CBaseEntity*> m_ObjsInFrustum;

	CObjectManager * m_pObjectManager;

	//DxUt::CFPCamera m_Camera;
	DxUt::COrbitCamera m_Camera;

	std::vector<DxUt::SLightDir> m_Lights;
public:
	void Init(HINSTANCE hInst, TCHAR * szClassName, TCHAR * szTitleText,
		WORD wWndPosX, WORD wWndPosY, WORD wWndWidth, WORD wWndHeight, VoidCallback onResizeWindowFunction);

	void BeginGraphicsLoop(VoidCallback GraphicsLoop);

	void GetUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void AddLight(DxUt::SLightDir & light) {m_Lights.push_back(light); }

	void Render();

	std::vector<CBaseEntity*> & GetObjectsInViewFrustum() {return m_ObjsInFrustum; }

	void OnResize();
	void Destroy();
};


#endif