
#ifndef RACER_ENTITY_H
#define RACER_ENTITY_H

#include "BaseEntity.h"
#include "Renderer.h"

class CRacerEntity : public CBaseEntity {
private:
	float m_fGravity;
public:
	CRacerEntity(PhysUt::Matrix4x4F & localTransform, bool bIsStatic):
	  CBaseEntity(localTransform, bIsStatic) {}
	~CRacerEntity();

	void AttachRenderer(CRenderer * pRenderer);

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light);
};



#endif
