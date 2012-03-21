
#ifndef PHYSUTRIGIDBODY_H
#define PHYSUTRIGIDBODY_H

#include "DxUtMesh.h"

namespace PhysUt {

struct STriangleF;

class CRigidBody {
protected:
	Vector3F m_CenterOfMass;
	Vector3F m_Pos,		m_PrePos;
	Matrix4x4F m_Rot,	m_PreRot;
	Vector3F m_LinVel;
	Vector3F m_AngVel;

	Matrix4x4F m_IBody,	m_InvIBody;
	Matrix4x4F m_I,		m_InvI;

	FLOAT m_InvMass,		m_Density;
	FLOAT m_fElasticity,	m_fMu;

	Vector3F m_Force;
	Vector3F m_Torque;

	Vector3F ComputeLinVel(Vector3F & impulse);
	Vector3F ComputeAngVel(Vector3F & impulse, Vector3F & iPos);
	void ApplyImpulse(Vector3F & impulse, Vector3F & r); 
public:
	CRigidBody();
	CRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, FLOAT fMass, FLOAT fElasticity);
	CRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, FLOAT fMass, FLOAT fElasticity, Vector3F & linVel, Vector3F & angVel);
	//~CRigidBody() {}

	/* Mass < 0 represents an infinitely heavy object */
	void CreateRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, FLOAT fMass);
	void CreateRigidBody(STriangleF * rgTri, DWORD nTri, DWORD * rgAdj, FLOAT fMass);

	void IntegratePos(FLOAT dt);
	void IntegrateVel(FLOAT dt, Vector3F & gAcel);

	void ResolveCollision(CRigidBody & collidingBody, Vector3F & contactPoint, Vector3F & contactNormal);

	void SavePosAndRot() {m_PrePos = m_Pos; m_PreRot = m_Rot;}
	void RestorePosAndRot() {m_Pos = m_PrePos; m_Rot = m_PreRot;}

	//T is assumed to consist of a rotation and translation only
	void Transform(Matrix4x4F & T) {
		m_Pos = T * Vector3F(0, 0, 0) + m_CenterOfMass;
		m_Rot.m[0][0] = T.m[0][0], m_Rot.m[0][1] = T.m[0][1], m_Rot.m[0][2] = T.m[0][2];
		m_Rot.m[1][0] = T.m[1][0], m_Rot.m[1][1] = T.m[1][1], m_Rot.m[1][2] = T.m[1][2];
		m_Rot.m[2][0] = T.m[2][0], m_Rot.m[2][1] = T.m[2][1], m_Rot.m[2][2] = T.m[2][2];
	}

	Vector3F const & GetPos() {return m_Pos;}
	Matrix4x4F const & GetRot() {return m_Rot; }
	Matrix4x4F GetWorldMatrix() {
		Matrix4x4F m(m_Rot);
		m.m[0][3] = m_Pos.x - m_CenterOfMass.x;
		m.m[1][3] = m_Pos.y - m_CenterOfMass.y;
		m.m[2][3] = m_Pos.z - m_CenterOfMass.z;
		return m;
	}
	Vector3F & GetLinVel() {return m_LinVel;}
	Vector3F & GetAngVel() {return m_AngVel;}
	Vector3F & GetForce() {return m_Force;}
	void SetForce(Vector3F &force) {m_Force = force;}
	void SetLinAcc(Vector3F &acc) {m_Force = (1.0f / m_InvMass) * acc;}
	void AddToForce(Vector3F &force) {
		m_Force.x = m_Force.x + force.x;
		m_Force.y = m_Force.y + force.y;
		m_Force.z = m_Force.z + force.z;
	}
	void AddToAcc(Vector3F &acc) {
		AddToForce((1.0f / m_InvMass) * acc);
	}
	Vector3F & GetTorque() {return m_Torque;}

	FLOAT GetMass() {return 1.0f / m_InvMass;}
	FLOAT & GetElasticity() {return m_fElasticity;}
	FLOAT & GetFriction() {return m_fMu;}
};
	
void ComputeVolume(STriangleF * rgTri, DWORD nTri, double & dVol);
//The vertices must be in a triangle list order
void ComputeVolume(Vector3F * rgVert, DWORD nVert, double & dVol);

void ComputeInertiaTensor(STriangleF * rgTri, DWORD nTri, double fMass, Matrix4x4F & I, Vector3F & cm, double & dDensity);
void ComputeInertiaTensor(Vector3F * rgVert, DWORD nVert, double fMass, Matrix4x4F & I, Vector3F & cm, double & dDensity);


};


#endif


