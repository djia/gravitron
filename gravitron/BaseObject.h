
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <Windows.h>

class CBaseObject {
protected:
public:
	CBaseObject() {}
	virtual ~CBaseObject() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif