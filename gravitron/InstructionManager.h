
#ifndef INSTRUCTION_MANAGER_H
#define INSTRUCTION_MANAGER_H

#include "Globals.h"

class CObjectManager;
class CPhysicsManager;

class CInstructionManager {
private:
	friend class CGameManager;

	CObjectManager * m_pObjManager;
	CPhysicsManager * m_pPhysicsManager;
public:
	CInstructionManager() {}
	~CInstructionManager() {}

	void Init() {}

	void ProcessInput(KeyState & rKeyState, MouseState & rMouseState);

	void Destroy() {}
};




#endif