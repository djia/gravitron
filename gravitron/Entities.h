
#ifndef ENTITIES_H
#define ENTITIES_H

#include "BaseEntity.h"
#include "Renderer.h"

class CPointGravityEntity : public CBaseEntity {
private:
	float m_fGravity;
public:
	CPointGravityEntity(PhysUt::Matrix4x4F & localTransform, bool bIsStatic):
	  CBaseEntity(localTransform, bIsStatic), m_fGravity(9.8f) {}
	~CPointGravityEntity();

	void AttachRenderer(CRenderer * pRenderer);

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light);

	void SetGravityStrength(float fGravity) {m_fGravity = fGravity; }

	bool DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity);
};



#endif
