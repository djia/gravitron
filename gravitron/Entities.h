
#ifndef ENTITIES_H
#define ENTITIES_H

#include "BaseEntity.h"
#include "Renderer.h"

class CPointGravityEntity : public CBaseEntity {
private:
	float m_fGravity;
public:
	CPointGravityEntity(PhysUt::Matrix4x4F & localTransform, float fGravity):
	  CBaseEntity(localTransform), m_fGravity(fGravity) {}

	CPointGravityEntity(PhysUt::Matrix4x4F & localTransform, float fGravity, float radius, float thetaVel):
	  CBaseEntity(localTransform), m_fGravity(fGravity) {
		m_Radius = radius;
		m_ThetaVel = thetaVel;
	}

	~CPointGravityEntity() {}

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void SetGravityStrength(float fGravity) {m_fGravity = fGravity; }

	bool DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity);
};

class CDirectionalGravityEntity : public CBaseEntity {
private:
	float m_fGravity;
	Vector3F m_GravityDir;
public:
	CDirectionalGravityEntity(PhysUt::Matrix4x4F & localTransform, float fGravity, Vector3F & gravityDir):
	  CBaseEntity(localTransform), m_fGravity(fGravity), m_GravityDir(gravityDir) {}
	~CDirectionalGravityEntity() {}

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void SetGravityStrength(float fGravity) {m_fGravity = fGravity; }
	void SetGravityDirection(Vector3F & dir) {m_GravityDir = dir; }

	bool DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity);
};


#endif
