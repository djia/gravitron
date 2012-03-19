
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "RacerEntity.h"

void CObjectManager::Init(CHAR * szSceneFile)
{
	m_Objs.resize(3);
	m_nDynamicObjects = 0;
	m_nStaticObjects = 0;

	Matrix4x4F localTransform;
	localTransform.MIdentity();

	m_Objs[0] = new CPointGravityEntity(localTransform, 1);
	m_Objs[0]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	m_Objs[0]->AttachBody(new CBSphere(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride()),
		new CRigidBody(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride(), 10.f));
	m_nDynamicObjects++;

	//localTransform.MTranslation(0.1f, 25.f, 0.1f);
	//m_Objs[1] = new CPointGravityEntity(localTransform, 1);
	//m_Objs[1]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	//m_Objs[1]->AttachBody(new CBSphere(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride()),
	//	new CRigidBody(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride(), 10.f));
	//CBSphere * bSphere = new CBSphere(Vector3F(0, 0, 0), 100.f);
	//m_Objs[1]->AttachForceEnvelope(bSphere);
	//m_nStaticObjects++;


	localTransform.MTranslation(0.1f, 25.f, 0.1f);
	m_Objs[1] = new CRacerEntity(localTransform, 1);
	m_Objs[1]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	m_Objs[1]->AttachBody(new CBSphere(m_Objs[1]->GetID3DX10Mesh(), m_Objs[1]->GetStride()),
		new CRigidBody(m_Objs[1]->GetID3DX10Mesh(), m_Objs[1]->GetStride(), 10.f));
	//CBSphere * bSphere = new CBSphere(Vector3F(0, 0, 0), 100.f);
	m_nDynamicObjects++;


	localTransform.MTranslation(10.1f, 1.f, 10.1f);
	m_Objs[2] = new CPointGravityEntity(localTransform, 1);
	m_Objs[2]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	m_Objs[2]->AttachBody(new CBSphere(m_Objs[2]->GetID3DX10Mesh(), m_Objs[2]->GetStride()),
		new CRigidBody(m_Objs[2]->GetID3DX10Mesh(), m_Objs[2]->GetStride(), 10.f));
	m_nDynamicObjects++;

}

void CObjectManager::ProcessUserInput(KeyState & rKeyState, MouseState & rMouseState)
{
	std::vector<CBaseEntity*> & objects = m_pGraphicsManager->GetObjectsInViewFrustum();
	CBaseEntity ** rgObjects = objects.data();
	for (UINT i=0, end=objects.size(); i<end; i++) {
		rgObjects[i]->ProcessUserInput(rKeyState, rMouseState);
	}
}

void CObjectManager::Simulate()
{
	CBaseEntity ** rgDynamicObject = m_Objs.data();
	//CBaseEntity ** rgStaticObject = m_Objs.data()+m_nDynamicObjects;

	float dt = 0.001f;
	for (UINT i=0; i<m_nDynamicObjects; i++) {
		rgDynamicObject[i]->m_pRigidBody->SavePosAndRot();
		rgDynamicObject[i]->m_pRigidBody->IntegratePos(dt);
	}

	//Deal with contacts
	for (UINT i=0; i<m_nDynamicObjects; i++) {
		for (UINT j=i+1, end=m_nDynamicObjects+m_nStaticObjects; j<end; j++) {
			rgDynamicObject[i]->DoContactCollision(rgDynamicObject[j]);
		}
	}
	//Deal with forces
	for (UINT i=0, end=m_nDynamicObjects+m_nStaticObjects; i<end; i++) {
		if (!rgDynamicObject[i]->HasForceEnvelope()) continue;

		for (UINT j=0, end=i; j<end; j++) {
			rgDynamicObject[i]->DoForceEnvelopeCollision(rgDynamicObject[j]);
		}
		for (UINT j=i+1, end=m_nDynamicObjects+m_nStaticObjects; j<end; j++) {
			rgDynamicObject[i]->DoForceEnvelopeCollision(rgDynamicObject[j]);
		}
	}

	for (UINT i=0; i<m_nDynamicObjects; i++) {
		rgDynamicObject[i]->m_pRigidBody->RestorePosAndRot();
		rgDynamicObject[i]->m_pRigidBody->IntegratePos(dt);
		rgDynamicObject[i]->SetTransform(rgDynamicObject[i]->m_pRigidBody->GetWorldMatrix());
		rgDynamicObject[i]->m_pRigidBody->IntegrateVel(dt, Vector3F(0, 10.0f, 0));
	}
}

void CObjectManager::Destroy() {
	for (UINT i=0; i<m_Objs.size(); i++) {
		delete m_Objs[i];
	}
	m_Objs.clear();
}











/*
	CBaseEntity ** GetDynamicObjects() {return m_rgObjsDynamic; }
	CBaseEntity ** GetStaticObjects() {return m_rgObjsStatic; }

	UINT GetNDynamicObjects() {return m_nDynamicObjects; }
	UINT GetNStaticObjects() {return m_nStaticObjects; }*/