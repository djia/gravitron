
#include "PhysicsManager.h"
#include "ObjectManager.h"
#include "BaseObject.h"

void CPhysicsManager::Init()
{
	//Binds the local transform of enities to the physics manager
	//CBaseObject ** rgObjsDynamic = m_pObjectManager->GetDynamicObjects();
	//for (int i=0, end=m_pObjectManager->GetNDynamicObjects(); i<end; i++) {
	//	rgObjsDynamic[i]->GetLocalTransform();
	//}
}

void CPhysicsManager::Simulate()
{
	CBaseObject ** rgDynamicObject = m_pObjectManager->GetDynamicObjects();
	CBaseObject ** rgStaticObject = m_pObjectManager->GetStaticObjects();

	UINT nDynamic = m_pObjectManager->GetNDynamicObjects();
	UINT nStatic = m_pObjectManager->GetNStaticObjects();

	float dt = 0.001f;
	for (UINT i=0; i<nDynamic; i++) {
		rgDynamicObject[i]->m_pRigidBody->SavePosAndRot();
		rgDynamicObject[i]->m_pRigidBody->IntegratePos(dt);
	}

	for (UINT i=0; i<nDynamic; i++) {//reset the force of the rb's. also fix this code
		for (UINT j=i+1, end=nDynamic+nStatic; j<end; j++) {
			rgDynamicObject[j]->DoContactCollision(rgDynamicObject[i]);
		}
	}
	for (UINT i=0; i<nDynamic; i++) {//reset the force of the rb's
		for (UINT j=i+1, end=nDynamic+nStatic; j<end; j++) {
			rgDynamicObject[j]->DoForceEnvelopeCollision(rgDynamicObject[i]);
		}
	}

	for (UINT i=0; i<nDynamic; i++) {
		rgDynamicObject[i]->m_pRigidBody->RestorePosAndRot();
		rgDynamicObject[i]->m_pRigidBody->IntegratePos(dt);
		rgDynamicObject[i]->SetTransform(rgDynamicObject[i]->m_pRigidBody->GetWorldMatrix());
		rgDynamicObject[i]->m_pRigidBody->IntegrateVel(dt, Vector3F(0, 3.8f, 0));
	}
}