
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "InstructionManager.h"
#include "PhysicsManager.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include <crtdbg.h>

class CGameManager {
private:
	friend class CGraphicsManager;

	CInstructionManager	m_InstructionManager;
	CObjectManager		m_ObjectManager;
	CGraphicsManager	m_GraphicsManager;

	UINT m_nSuccess;

	static void GameLoop() {
		GetGameManager().m_ObjectManager.SetForcesToZero();

		KeyState ks;
		MouseState ms;
		GetGameManager().m_GraphicsManager.GetUserInput(ks, ms);
		GetGameManager().m_InstructionManager.ProcessInput(ks, ms);

		//for(int i = 0; i < 256; i++) {
		//	if(g_KeysState[i]) {
		//		int a = 10;
		//	}
		//}

		if(g_KeysState[2]) {
			GetGameManager().m_ObjectManager.LoadLevel(1);
			GetGameManager().m_GraphicsManager.m_Camera.SetRacer(GetGameManager().m_ObjectManager.GetRacer());
		} else if(g_KeysState[3]) {
			GetGameManager().m_ObjectManager.LoadLevel(2);
			GetGameManager().m_GraphicsManager.m_Camera.SetRacer(GetGameManager().m_ObjectManager.GetRacer());
		}

		//check if the user has lost
		Vector3F racerPos = GetGameManager().m_ObjectManager.GetRacer()->GetPos();
		Vector3F finalPlatformPos = GetGameManager().m_ObjectManager.GetFinalPlatform()->GetPos();
		if(racerPos.y - finalPlatformPos.y <= -50) {
			MessageBox(g_hWnd, L"You die", L"You die", 0);
			// use has lost, restart level
			GetGameManager().m_ObjectManager.RestartLevel();
			GetGameManager().m_GraphicsManager.m_Camera.SetRacer(GetGameManager().m_ObjectManager.GetRacer());
		}

		//check if user has won
		if(racerPos.y - finalPlatformPos.y <= 5 && abs(racerPos.x - finalPlatformPos.x) < 20 && abs(racerPos.z - finalPlatformPos.z) < 20) {
			GetGameManager().m_nSuccess++;
		} else {
			GetGameManager().m_nSuccess = 0;
		}
		if(GetGameManager().m_nSuccess >= 300) {
			MessageBox(g_hWnd, L"You win!", L"You win!", 0);
			GetGameManager().m_nSuccess = 0;
			// go to next level
			GetGameManager().m_ObjectManager.NextLevel();
			GetGameManager().m_GraphicsManager.m_Camera.SetRacer(GetGameManager().m_ObjectManager.GetRacer());
		}

		GetGameManager().m_ObjectManager.Simulate();

		GetGameManager().m_GraphicsManager.Render();
	}
	static void OnWindowResize() {
		GetGameManager().m_GraphicsManager.OnResize();
	}

	CGameManager() {}
	~CGameManager() {
		m_GraphicsManager.Destroy();
		m_InstructionManager.Destroy();
		m_ObjectManager.Destroy();
	}
public:
	void Init(HINSTANCE hInst) {
		m_nSuccess = 0;
		// Memory leak checking
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(183);

		m_InstructionManager.m_pObjManager = &m_ObjectManager;
		m_ObjectManager.m_pGraphicsManager = &m_GraphicsManager;
		m_GraphicsManager.m_pObjectManager = &m_ObjectManager;

		//Future Fix: Remove hard coded numbers
		m_GraphicsManager.Init(hInst, L"Gravitron", L"Gravitron", 20, 20, 800, 600, OnWindowResize);
		DxUt::SLightDir light = {
			D3DXCOLOR(.7f, .7f, .7f, 1.f), 
			D3DXCOLOR(.5f, .5f, .5f, 1.f), 
			D3DXCOLOR(.3f, .3f, .3f, 1.f), 
			PhysUt::Vector3F(0, -.707f, .707f)
		};
		m_GraphicsManager.AddLight(light);

		//Instructions
		m_InstructionManager.Init();

		//Objects
		m_ObjectManager.Init("Level0");

		m_GraphicsManager.m_Camera.SetRacer(m_ObjectManager.GetRacer());
	}

	void Run() {
		m_GraphicsManager.BeginGraphicsLoop(GameLoop);
	}

	static CGameManager & GetGameManager() {
		static CGameManager gm;
		return gm;
	}
};



#endif