
#ifndef RIGIDBODYWORLD_H
#define RIGIDBODYWORLD_H

#include "DxUtInclude.h"
#include "DxUtRigidBody.h"
#include <vector>

namespace DxUt {

class CRigidBodyWorld {
private:
	/* A contact point between two rigid bodies */
	/* The structure is size BVTree::SContactPoint */
	struct SRBObject;
	struct SRBContact {
		SRBObject * rBOk;
		SRBObject * rBOl;
		Vector3F iPos;
		Vector3F iNor;
	};
	struct SRBObject {
		WORD bUsed;
		WORD bActive;
		CRigidBody rB;
		//std::vector<SRBContact> rgCP;
	};

	std::vector<SRBObject> m_rgRBObject;
	/* This is the pointer to the head of the RBObject array */
	SRBObject * m_pRBObject;

	std::vector<SRBContact> m_rgContactPoint;

	DWORD FindContacts();
	void SolveConstraints(DWORD nContacts);
public:
	CRigidBodyWorld();
	//~CRigidBodyWorld() {}

	/* Give a nonzero hint as to how many RBs and contacts among them there will be */
	void CreateRigidBodyWorld(DWORD nHintRBs, DWORD nHintContacts);

	/* Note that once a rigidbody has been added there is no way to remove it. It can at */
	/* most be disabled from taking part further in the the rigidbody world. Because */
	/* of this one should first destroy the rigidbody world if simulating a much smaller */
	/* collection of bodies than the total number that were added to it before recreating it. */

	/* The funciton returns the id for this rigidbody */
	/* Any future changes to a body's characteristics can be changed by way of calling */
	/* GetRigidBody on that id to obtain the CRigidBody and using its getters and setters */
	DWORD AddRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, float fScale, float fMass, Vector3F & pos, Matrix4x4F & rot,
		Vector3F & linVel, Vector3F & angVel, float fElasticity, float fMu, Vector3F & force, Vector3F & torque);
	void DisableRigidBody(DWORD dwId);
	void EnableRigidBody(DWORD dwId);

	void UpdateRigidBodies(FLOAT dt, Vector3F & gAcel);

	/* Returns the world matrix for the body with dwId*/
	Matrix4x4F GetRBWorld(DWORD dwId);
	CRigidBody * GetRigidBody(DWORD dwId);

	void DestroyRigidBodyWorld();
};


inline Matrix4x4F CRigidBodyWorld::GetRBWorld(DWORD dwId) 
{
	Assert(dwId < m_rgRBObject.size(), "CRigidBodyWorld::GetRBWorld "
		"an id was specifed which does not exist for any body.");

	return m_pRBObject[dwId].rB.GetWorldMatrix();
}
inline CRigidBody * CRigidBodyWorld::GetRigidBody(DWORD dwId) 
{
	Assert(dwId < m_rgRBObject.size(), "CRigidBodyWorld::GetRigidBody "
		"an id was specifed which does not exist for any body.");

	return &m_rgRBObject[dwId].rB;
}


};


#endif


