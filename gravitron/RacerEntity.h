
#ifndef RACER_ENTITY_H
#define RACER_ENTITY_H

#include "BaseEntity.h"
#include "Renderer.h"

class CRacerEntity : public CBaseEntity {
private:
	float m_fGravity;

	bool m_upPressed;
	bool m_rightPressed;
	bool m_downPressed;
	bool m_leftPressed;

	bool m_spacePressed;

	Vector3F m_ForwardVec;
	Vector3F m_RightVec;

public:
	CRacerEntity(PhysUt::Matrix4x4F & localTransform):
	  CBaseEntity(localTransform), m_upPressed(false), m_rightPressed(false), m_downPressed(false), m_leftPressed(false), m_spacePressed(false) {
		gravitySign = true;
		m_ForwardVec = Vector3F(1, 0, 0);
		m_RightVec = Vector3F(0, 0, 1);
	  }
	~CRacerEntity();

	void AttachRenderer(CRenderer * pRenderer);

	void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState);

	void Draw(Matrix4x4F & world, DxUt::CCamera * pCam, SLightDir & light);
	void SetForwardVec(Vector3F vec) {
		m_ForwardVec = vec.Normalize();
	}
	void SetRightVec(Vector3F vec) {
		m_RightVec = vec.Normalize();
	}
};



#endif
