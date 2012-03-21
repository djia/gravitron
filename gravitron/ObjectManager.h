
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "Globals.h"
#include "BaseEntity.h"
#include "Entities.h"
#include <vector>
#include "RacerEntity.h"

class CGraphicsManager;

/* x86 - x64 problem with Water */
class CObjectManager {
private:
	friend class CGameManager;
	friend class CInstructionManager;

	//First m_nDynamicObjects of m_Objs are dynamic
	//Next m_nStaticObjects of m_Objs are static
	UINT m_nDynamicObjects;
	UINT m_nStaticObjects;
	std::vector<CBaseEntity*> m_Objs;

	CRacerEntity * m_Racer;
	CBaseEntity * m_FinalPlatform;
	// the current level
	UINT m_CurrentLevel;

	CGraphicsManager * m_pGraphicsManager;
public:
	CObjectManager() {}
	virtual ~CObjectManager() {}

	void Init(CHAR * szSceneFile);

	void LoadLevel(UINT level);

	void RestartLevel();

	void NextLevel();
	
	void ResetAll();

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Simulate();

	std::vector<CBaseEntity*> & GetObjects() {return m_Objs; }

	void SetForcesToZero();

	CRacerEntity * GetRacer() {return m_Racer;};
	CBaseEntity * GetFinalPlatform() {return m_FinalPlatform;};

	void Destroy();
};


#endif