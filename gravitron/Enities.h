
#ifndef ENITIES_H
#define ENITIES_H

#include "BaseEnity.h"
#include "Renderer.h"

class CPointGravityEnity : public CBaseEnity {
private:
	float m_fGravity;
public:
	CPointGravityEnity(PhysUt::Matrix4x4F & localTransform, bool bIsStatic):
	  CBaseEnity(localTransform, bIsStatic), m_fGravity(9.8f) {}
	~CPointGravityEnity();

	void AttachRenderer(CRenderer * pRenderer);

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light);

	void SetGravityStrength(float fGravity) {m_fGravity = fGravity; }

	bool DoForceEnvelopeCollision(CBaseEnity * pCollidingEnity);
};



#endif
