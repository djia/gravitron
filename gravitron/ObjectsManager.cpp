
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "RacerEntity.h"
#include <fstream>

void CObjectManager::Init(CHAR * szSceneFile)
{
	m_CurrentLevel = (UINT)1;
	LoadLevel(m_CurrentLevel);
	//std::ifstream fileStream("Levels/level2.txt" , std::ifstream::in);

	//char buf[256];
	//fileStream >> buf;
	//UINT numObjects = atoi(buf);
	//fileStream >> buf;
	//m_nDynamicObjects = atoi(buf);
	//m_nStaticObjects = numObjects - m_nDynamicObjects;

	//m_Objs.resize(numObjects);

	//int i = 0;
	//while(true) {
	//	if (!fileStream) break;

	//	// get the next set of values
	//	char values[10][256];
	//	for(int j = 0; j < 9; j++) {
	//		fileStream >> values[j];
	//	}

	//	// racer
	//	if(strcmp(values[0], "CRacerEntity") == 0) {
	//		Matrix4x4F localTransform;
	//		localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
	//		m_Objs[i] = new CRacerEntity(localTransform);
	//		m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
	//		m_Objs[i]->AttachBody(new CBSphere(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
	//			new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(), atof(values[2]), atof(values[3]), Vector3F(0,0,0), Vector3F(0,0,0)), NULL);
	//		//set the racer
	//		m_Racer = (CRacerEntity *)m_Objs[i];
	//	} else if(strcmp(values[0], "CPointGravityEntity") == 0) {
	//		Matrix4x4F localTransform;
	//		localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
	//		m_Objs[i] = new CPointGravityEntity(localTransform, atof(values[4]));
	//		m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
	//		m_Objs[i]->AttachBody(new CBSphere(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
	//			new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(), atof(values[2]), atof(values[3])), new CBSphere(Vector3F(0, 0, 0), atof(values[5])));
	//	} else if(strcmp(values[0], "CPlatformEntity") == 0) {
	//		Matrix4x4F localTransform;
	//		localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
	//		m_Objs[i] = new CBaseEntity(localTransform);
	//		m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
	//		m_Objs[i]->AttachBody(new COBBox(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
	//			new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(),  atof(values[2]), atof(values[3])), NULL);
	//	} else {
	//		break;
	//	}
	//	i++;
	//}

	//fileStream.close();

	//m_Objs.resize(3);
	//m_nDynamicObjects = 0;
	//m_nStaticObjects = 0;

	//Matrix4x4F localTransform;
	//localTransform.MIdentity();

	////localTransform.MTranslation(1.f, 15.f, 1.1f);
	////m_Objs[0] = new CBaseEntity(localTransform);
	////m_Objs[0]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	////m_Objs[0]->AttachBody(new CBSphere(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride()),
	////	new CRigidBody(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride(), 10.f, .5f), NULL);
	////m_nDynamicObjects++;

	//localTransform.MTranslation(-10.f, 25.f, 10.1f);
	//m_Objs[0] = new CRacerEntity(localTransform);
	//m_Objs[0]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	//m_Objs[0]->AttachBody(new CBSphere(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride()),
	//	new CRigidBody(m_Objs[0]->GetID3DX10Mesh(), m_Objs[0]->GetStride(), 10.f, .5f, Vector3F(0,0,0), Vector3F(0,0,0)), NULL);
	//m_nDynamicObjects++;

	//m_Racer = (CRacerEntity *)m_Objs[0];


	//localTransform.MTranslation(-1.f, 25.f, 1.1f);
	//m_Objs[1] = new CPointGravityEntity(localTransform, -200.f);
	//m_Objs[1]->AttachRenderer(new CPNTPhongRenderer("/Models/Sphere.txt", D3DX10_MESH_32_BIT));
	//m_Objs[1]->AttachBody(new CBSphere(m_Objs[1]->GetID3DX10Mesh(), m_Objs[1]->GetStride()),
	//	new CRigidBody(m_Objs[1]->GetID3DX10Mesh(), m_Objs[1]->GetStride(), -10.f, .5f), new CBSphere(Vector3F(0, 0, 0), 100.f));
	////m_nDynamicObjects++;
	//m_nStaticObjects++;

	//Matrix4x4F idenity; 
	//idenity.MIdentity();
	//idenity.MTranslation(-10.f, -10.f, 10.1f);
	////idenity.MScaling(20.f, 0, 20.f);
	//m_Objs[2] = new CBaseEntity(idenity);
	//m_Objs[2]->AttachRenderer(new CPNTPhongRenderer("/Models/Platform.txt", D3DX10_MESH_32_BIT));
	//m_Objs[2]->AttachBody(new COBBox(m_Objs[2]->GetID3DX10Mesh(), m_Objs[2]->GetStride()),
	//	new CRigidBody(m_Objs[2]->GetID3DX10Mesh(), m_Objs[2]->GetStride(), -1.f, 0.f), NULL);//new COBBox(idenity, Vector3F(10.f, 1.f, 10.f)));//CBSphere(Vector3F(0, 0, 0), 100.f));
	//m_nStaticObjects++;
	////m_nDynamicObjects++;

}

void CObjectManager::RestartLevel() {
	LoadLevel(m_CurrentLevel);
}

void CObjectManager::NextLevel() {
	m_CurrentLevel += 2;
	m_CurrentLevel = m_CurrentLevel % 2;
	m_CurrentLevel++;
	LoadLevel(m_CurrentLevel);
}

void CObjectManager::LoadLevel(UINT level) {
	m_CurrentLevel = level;
	// clear everything
	ResetAll();

	char levelName[256];
	sprintf(levelName, "Levels/level%d.txt", level);
	std::ifstream fileStream(levelName , std::ifstream::in);

	char buf[256];
	fileStream >> buf;
	UINT numObjects = atoi(buf);
	fileStream >> buf;
	m_nDynamicObjects = atoi(buf);
	m_nStaticObjects = numObjects - m_nDynamicObjects;

	m_Objs.resize(numObjects);

	int i = 0;
	while(true) {
		if (!fileStream) break;

		// get the next set of values
		char values[11][256];
		for(int j = 0; j < 11; j++) {
			fileStream >> values[j];
		}

		// racer
		if(strcmp(values[0], "CRacerEntity") == 0) {
			Matrix4x4F localTransform;
			localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
			m_Objs[i] = new CRacerEntity(localTransform);
			m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
			m_Objs[i]->AttachBody(new CBSphere(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
				new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(), atof(values[2]), atof(values[3]), Vector3F(0,0,0), Vector3F(0,0,0)), NULL);
			//set the racer
			m_Racer = (CRacerEntity *)m_Objs[i];
		} else if(strcmp(values[0], "CPointGravityEntity") == 0) {
			Matrix4x4F localTransform;
			localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
			m_Objs[i] = new CPointGravityEntity(localTransform, atof(values[4]), atof(values[9]), atof(values[10]));
			m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
			m_Objs[i]->AttachBody(new CBSphere(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
				new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(), atof(values[2]), atof(values[3])), new CBSphere(Vector3F(0, 0, 0), atof(values[5])));
		} else if(strcmp(values[0], "CPlatformEntity") == 0) {
			Matrix4x4F localTransform;
			localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
			m_Objs[i] = new CBaseEntity(localTransform);
			m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
			m_Objs[i]->AttachBody(new COBBox(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
				new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(),  atof(values[2]), atof(values[3])), NULL);
		} else if(strcmp(values[0], "CFinalPlatformEntity") == 0) {
			Matrix4x4F localTransform;
			localTransform.MTranslation(atof(values[6]), atof(values[7]), atof(values[8]));
			m_Objs[i] = new CBaseEntity(localTransform);
			m_Objs[i]->AttachRenderer(new CPNTPhongRenderer(values[1], D3DX10_MESH_32_BIT));
			m_Objs[i]->AttachBody(new COBBox(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride()),
				new CRigidBody(m_Objs[i]->GetID3DX10Mesh(), m_Objs[i]->GetStride(),  atof(values[2]), atof(values[3])), NULL);
			// set the final platform
			m_FinalPlatform = m_Objs[i];
		} else {
			break;
		}
		i++;
	}

	fileStream.close();
}

void CObjectManager::ResetAll() {
	m_nDynamicObjects = 0;
	m_nStaticObjects = 0;

	m_Objs.clear();
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
		rgDynamicObject[i]->m_pRigidBody->IntegrateVel(dt, Vector3F(0, -9.80f, 0));
	}
}

void CObjectManager::SetForcesToZero()
{
	CBaseEntity ** rgDynamicObject = m_Objs.data();
	for (UINT i=0; i<m_nDynamicObjects; i++) {
		rgDynamicObject[i]->SetForce(Vector3F(0, 0, 0));
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