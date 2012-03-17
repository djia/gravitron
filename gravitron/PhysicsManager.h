
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Globals.h"

class CObjectManager;

class CPhysicsManager {
private:
	friend class CGameManager;
	CObjectManager * m_pObjectManager;
public:
	CPhysicsManager() {}
	~CPhysicsManager() {}

	void AddBody();

	// Must be called after EnityManager has been initialized
	void Init();
	void Simulate();
};


#endif