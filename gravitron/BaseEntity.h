
#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "Globals.h"
#include "DxUtCamera.h"
#include "DxUtLight.h"
#include "PhysUtBSphere.h"
#include "PhysUtRigidBody.h"
#include "Renderer.h"

class CBaseEntity {
protected:
	//Transform from local space to world space
	PhysUt::Matrix4x4F m_LocalTransform;

	//Rendering
	CRenderer * m_pRenderer;

	//Physics
	friend class CObjectManager;
	//Defining a force envelope for each body is optional
	CBoundingVolume * m_pFoceEnvelopeBV;
	//Dealing with contact between rigid bodies is optional
	CBoundingVolume * m_pContactBV;
	CRigidBody * m_pRigidBody;
	
	bool m_bIsStatic;

	CBaseEntity() {}
public:
	CBaseEntity(PhysUt::Matrix4x4F & localTransform, bool bIsStatic):
	  m_LocalTransform (localTransform), m_bIsStatic(bIsStatic),  m_pFoceEnvelopeBV(0), m_pContactBV(0) {}
	virtual ~CBaseEntity() {}

	virtual void AttachRenderer(CRenderer * pRenderer) {}
	virtual void AttachForceEnvelope(CBoundingVolume * pFoceEnvelopeBV);
	virtual void AttachBody(CBoundingVolume * pContactBV, CRigidBody * pContactRigidBody);

	virtual void ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState) {}
	virtual void Draw(PhysUt::Matrix4x4F & world, DxUt::CCamera * pCam, DxUt::SLightDir & light) {};

	//Determine if pCollidingEntity and this are within each 
	//other's force envelope's and update the force on a RigidBody if so
	virtual bool DoForceEnvelopeCollision(CBaseEntity * pCollidingEntity) {return 0; }

	void DoContactCollision(CBaseEntity * pCollidingEntity);

	void SetTransform(Matrix4x4F & T);
	void SetForce(Vector3F & force) {m_pRigidBody->GetForce() = force; }
	void SetTorque(Vector3F & torque) {m_pRigidBody->GetTorque() = torque; }

	virtual ID3DX10Mesh * GetID3DX10Mesh() {return m_pRenderer->GetID3DX10Mesh(); }
	virtual DWORD GetStride() {return m_pRenderer->GetStride(); }

	float GetMass() {return m_pRigidBody->GetMass(); }
	bool HasForceEnvelope() {return m_pFoceEnvelopeBV ? 1 : 0; }

	CRenderer * GetRenderer() {return m_pRenderer; }
	PhysUt::Matrix4x4F & GetLocalTransform() {return m_LocalTransform; }
	CBoundingVolume * GetBoundingVolume() {return m_pContactBV; }
	bool IsStatic() {return m_bIsStatic; }
};


#endif