
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "Globals.h"
#include "BaseObject.h"
#include <vector>

/* x86 - x64 problem with Water */
class CObjectManager {
private:
	std::vector<CBaseObject*> m_Objs;
public:
	CObjectManager();
	~CObjectManager() {}

	void Init(CHAR * szSceneFile);

	void Destroy();
};


#endif