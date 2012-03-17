
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

	static void GameLoop() {
		KeyState ks;
		MouseState ms;
		GetGameManager().m_GraphicsManager.GetUserInput(ks, ms);
		GetGameManager().m_InstructionManager.ProcessInput(ks, ms);

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

		m_InstructionManager.Init();
		m_ObjectManager.Init("Level0");
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