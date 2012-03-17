
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "Globals.h"
#include "BaseEnity.h"
#include "Enities.h"
#include <vector>

class CGraphicsManager;
class CPhysicsManager;

/* x86 - x64 problem with Water */
class CObjectManager {
private:
	friend class CGameManager;

	//First m_nDynamicObjects of m_Objs are dynamic
	//Next m_nStaticObjects of m_Objs are static
	UINT m_nDynamicObjects;
	UINT m_nStaticObjects;
	std::vector<CBaseEnity*> m_Objs;

	CGraphicsManager * m_pGraphicsManager;
public:
	CObjectManager() {}
	virtual ~CObjectManager() {}

	void Init(CHAR * szSceneFile);

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Simulate();

	std::vector<CBaseEnity*> & GetObjects() {return m_Objs; }

	void Destroy();
};


#endif