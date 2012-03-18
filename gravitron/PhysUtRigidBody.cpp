
#include "PhysUtRigidBody.h"
#include "PhysUtTriangle.h"
#include "DxUtMesh.h"

namespace PhysUt {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////     CRigidBody    /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRigidBody::CRigidBody():m_LinVel(0, 0, 0), m_AngVel(0, 0, 0), m_Force(0, 0, 0), m_Torque(0, 0, 0), m_fElasticity(0.f)
{
}


CRigidBody::CRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, FLOAT fMass):m_LinVel(0, 0, 0),
	m_AngVel(0, 0, 0), m_Force(0, 0, 0), m_Torque(0, 0, 0), m_fElasticity(0.f)
{
	CreateRigidBody(pMesh, dwStride, fMass);
}

CRigidBody::CRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride,
	FLOAT fMass, Vector3F & linVel, Vector3F & angVel):m_LinVel(0, 0, 0),
	m_AngVel(0, 0, 0), m_Force(0, 0, 0), m_Torque(0, 0, 0), m_fElasticity(0.f)
{
	CreateRigidBody(pMesh, dwStride, fMass);
	m_LinVel = linVel;
	m_AngVel = angVel;
}

void CRigidBody::CreateRigidBody(ID3DX10Mesh * pMesh, DWORD dwStride, FLOAT fMass)
{
	DWORD nVert = 3*pMesh->GetFaceCount();
	Vector3F * rgVert = new Vector3F[nVert];
	DxUt::ExtractVertexTriangleListFromMesh(pMesh, rgVert, dwStride);

	Vector3F cm;
	double dDensity = 0;
	if (fMass < 0) m_IBody.MZero();
	else ComputeInertiaTensor(rgVert, nVert, fMass, m_IBody, cm, dDensity);

	DWORD * rgAdj = new DWORD[3*nVert];
	DxUt::ExtractAdjanceyFromMesh(pMesh, rgAdj);

	m_InvMass = 1.f/fMass;
	m_Density = (float)dDensity;
	if (fMass < 0) {
		m_InvMass = 0;
		m_InvIBody.MZero();
		m_InvI.MZero();
		m_Pos = m_CenterOfMass = Vector3F(0, 0, 0);
	} else {
		m_InvMass = 1.f/fMass;
		m_InvIBody = m_IBody.Inverse();
		m_Pos = m_CenterOfMass = cm;
	}
	
	delete[] rgVert;
	rgVert = NULL;
	delete[] rgAdj;
	rgAdj = NULL;
}

void CRigidBody::CreateRigidBody(STriangleF * rgTri,
	DWORD nTri, DWORD * rgAdj, FLOAT fMass)
{
	DWORD nVert = 3*nTri;
	Vector3F cm;
	double dDensity = 0;
	if (fMass < 0) m_IBody.MZero();
	else ComputeInertiaTensor((Vector3F*)rgTri, nVert, fMass, m_IBody, cm, dDensity);

	m_InvMass = 1.f/fMass;
	m_Density = (float)dDensity;
	if (fMass < 0) {
		m_InvMass = 0;
		m_InvIBody.MZero();
		m_InvI.MZero();
		m_Pos = m_CenterOfMass = Vector3F(0, 0, 0);
	} else {
		m_InvMass = 1.f/fMass;
		m_InvIBody = m_IBody.Inverse();
		m_Pos = m_CenterOfMass = cm;
	}
}

void CRigidBody::IntegratePos(FLOAT dt)
{
	//Static bodies
	if (m_InvMass == 0.f) return;

	/* p(t+dt) = p(t) + v*dt */
	/* q(t+dt) = q(t) + w* * R */

	m_Pos += dt*m_LinVel;
	m_Rot += dt*m_AngVel.SkewMatrix3x3F()*m_Rot;

	/* Make m_Rot orthogonal */
	/* x */
	float div = (float)(1.0/sqrt(m_Rot.m[0][0]*m_Rot.m[0][0] + m_Rot.m[1][0]*m_Rot.m[1][0] + m_Rot.m[2][0]*m_Rot.m[2][0]));
	m_Rot.m[0][0] *= div, m_Rot.m[1][0] *= div, m_Rot.m[2][0] *= div;
	m_Rot.m[3][0] = 0.f;

	/* z */
	m_Rot.m[0][2] = m_Rot.m[1][0]*m_Rot.m[2][1] - m_Rot.m[2][0]*m_Rot.m[1][1];
	m_Rot.m[1][2] = m_Rot.m[2][0]*m_Rot.m[0][1] - m_Rot.m[0][0]*m_Rot.m[2][1];
	m_Rot.m[2][2] = m_Rot.m[0][0]*m_Rot.m[1][1] - m_Rot.m[1][0]*m_Rot.m[0][1];
	div = (float)(1.0/sqrt(m_Rot.m[0][2]*m_Rot.m[0][2] + m_Rot.m[1][2]*m_Rot.m[1][2] + m_Rot.m[2][2]*m_Rot.m[2][2]));
	m_Rot.m[0][2] *= div, m_Rot.m[1][2] *= div, m_Rot.m[2][2] *= div;
	m_Rot.m[3][2] = 0.f;

	/* y */
	m_Rot.m[0][1] = m_Rot.m[1][2]*m_Rot.m[2][0] - m_Rot.m[2][2]*m_Rot.m[1][0];
	m_Rot.m[1][1] = m_Rot.m[2][2]*m_Rot.m[0][0] - m_Rot.m[0][2]*m_Rot.m[2][0];
	m_Rot.m[2][1] = m_Rot.m[0][2]*m_Rot.m[1][0] - m_Rot.m[1][2]*m_Rot.m[0][0];
	m_Rot.m[3][1] = 0.f;

	/* w */
	m_Rot.m[0][3] = 0.f;
	m_Rot.m[1][3] = 0.f;
	m_Rot.m[2][3] = 0.f;
	m_Rot.m[3][3] = 1.f;

	Matrix4x4F m = m_Rot.Transpose();
	m_I = m_Rot*m_IBody*m;
	m_InvI = m_Rot*m_InvIBody*m;
}

void CRigidBody::IntegrateVel(FLOAT dt, Vector3F & gAcel)
{
	//Static bodies
	if (m_InvMass == 0.f) return;

	if (m_InvMass != 0)
		m_LinVel = m_LinVel + dt*(m_InvMass*m_Force + gAcel);

	m_AngVel = m_AngVel + m_InvI*(
		-dt*(m_AngVel.SkewMatrix3x3F()*m_I*m_AngVel) + m_Torque);
}

Vector3F CRigidBody::ComputeLinVel(Vector3F & impulse)
{
	return m_InvMass*impulse;
}

Vector3F CRigidBody::ComputeAngVel(Vector3F & impulse, Vector3F & r)
{
	return  m_InvI*CrossXYZ(r, impulse);
}
/*

Vector3F CRigidBody::GetImpulseCoefficient(Vector3F & jthCt, Vector3F & ithCt, Vector3F & iNor)
{
	return  -m_InvMass*iNor - (m_InvI*((ithCt - m_Pos).SkewMatrix3x3F()*iNor)).SkewMatrix3x3F()*(jthCt - m_Pos);
}

float CRigidBody::GetVelocityAtContactPoint(Vector3F & jthCt, Vector3F & jthNor)
{
	Vector3F vel(m_LinVel - (jthCt - m_Pos).SkewMatrix3x3F()*m_AngVel);
	return DotXYZ(vel, jthNor);
}*/


void CRigidBody::ApplyImpulse(Vector3F & impulse, Vector3F & r)
{
	m_AngVel += m_InvI*CrossXYZ(r, impulse);
	m_LinVel += m_InvMass*impulse;
}

void CRigidBody::ResolveCollision(CRigidBody & collidingBody, Vector3F & contactPoint, Vector3F & contactNormal)
{
	//Compute quantities
	Vector3F & nor = contactNormal;
	Vector3F r1(contactPoint - m_Pos);
	Vector3F u1 = m_LinVel + CrossXYZ(m_AngVel, r1);
	Vector3F r2(contactPoint - collidingBody.m_Pos);
	Vector3F u2 = collidingBody.m_LinVel + CrossXYZ(collidingBody.m_AngVel, r2);
	Vector3F u = u1-u2;

	float un = DotXYZ(u, nor);
	if (un > -.0001f) return;
	float e = max(m_fElasticity, collidingBody.m_fElasticity);
	float mu = 0;//max(m_Mu, rB->m_Mu);
		
	//Collision matrix K
	float invM1 = m_InvMass;
	float invM2 = collidingBody.m_InvMass;

	Matrix4x4F m1(r1.SkewMatrix3x3F()); m1 = m1*m_InvI*m1;
	Matrix4x4F m2(r2.SkewMatrix3x3F()); m2 = m2*collidingBody.m_InvI*m2;

	Matrix4x4F id; id.MIdentity();
	Matrix4x4F K((invM1 + invM2)*id - m1 - m2);
	Matrix4x4F KInv(K.Inverse()); 

	//Compute impulse
	Vector3F J = KInv*(-e*un*nor - u);
	float dot = DotXYZ(J, nor);
	if (((J - dot*nor).LengthSq()) <= (mu*dot * mu*dot)) {
		ApplyImpulse(J, r1);
		collidingBody.ApplyImpulse(-J, r2);

		return;
	}

	float n = -(1.f + e)*un;
	Vector3F vT(u - un*nor);
	vT = vT.Normalize();
	Vector3F v = K*(nor - mu*vT);
	float d = DotXYZ(nor, v); 
	float jn = n/(d + .0001f);
	J = jn*nor - mu*jn*vT;

	ApplyImpulse(J, r1);
	collidingBody.ApplyImpulse(-J, r2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////    CRigidBody Functions    /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeVolume(STriangleF * rgTri, DWORD nTri, double & dVol)
{
	double f1x;
	double intg = 0;
	for (DWORD i=0; i<nTri; i++) {
		double x0 = rgTri[i].vPosW[0].x, y0 = rgTri[i].vPosW[0].y, z0 = rgTri[i].vPosW[0].z;
		double x1 = rgTri[i].vPosW[1].x, y1 = rgTri[i].vPosW[1].y, z1 = rgTri[i].vPosW[1].z;
		double x2 = rgTri[i].vPosW[2].x, y2 = rgTri[i].vPosW[2].y, z2 = rgTri[i].vPosW[2].z;

		// get edges (1(a,b,c), 2(a,b,c)) and cross product of edges
		double b1 = y1-y0, c1 = z1-z0, b2 = y2-y0, c2 = z2-z0;
		double d0 = b1*c2-b2*c1;

		// compute integral term
		f1x = x0+x1+x2;							

		// update integral
		intg += d0*f1x;
	}

	// volume of polyhedron
	dVol = intg/6.0;
}

//The vertices must be in a triangle list order
void ComputeVolume(Vector3F * rgVert, DWORD nVert, double & dVol)
{
	if (nVert % 3) {DxUtSendError("ComputeVolume the rgVert must be divisible by 3.");}
	DWORD nTri = nVert/3;

	ComputeVolume((STriangleF*)rgVert, nTri, dVol);
}

#define Subexpressions(w0,w1,w2,f1,f2,f3,g0,g1,g2,temp0,temp1,temp2)		\
{																			\
	temp0 = w0+w1; f1 = temp0+w2; temp1 = w0*w0; temp2 = temp1+w1*temp0;	\
	f2 = temp2+w2*f1; f3 = w0*temp1+w1*temp2+w2*f2;							\
	g0 = f2+w0*(f1+w0); g1 = f2+w1*(f1+w1); g2 = f2+w2*(f1+w2);				\
}

void ComputeInertiaTensor(STriangleF * rgTri, DWORD nTri, double fMass, Matrix4x4F & I, Vector3F & cm, double & dDensity)
{
	double temp0, temp1, temp2;
	double f1x, f2x, f3x, g0x, g1x, g2x;
	double f1y, f2y, f3y, g0y, g1y, g2y;
	double f1z, f2z, f3z, g0z, g1z, g2z;
	const double mult[10] = {1.f/6,1.f/24,1.f/24,1.f/24,1.f/60,1.f/60,1.f/60,1.f/120,1.f/120,1.f/120};
	double intg[10] = {0,0,0,0,0,0,0,0,0,0}; // order: 1, x, y, z, x^2, y^2, z^2, xy, yz, zx

	for (DWORD i=0; i<nTri; i++) {
		double x0 = rgTri[i].vPosW[0].x, y0 = rgTri[i].vPosW[0].y, z0 = rgTri[i].vPosW[0].z;
		double x1 = rgTri[i].vPosW[1].x, y1 = rgTri[i].vPosW[1].y, z1 = rgTri[i].vPosW[1].z;
		double x2 = rgTri[i].vPosW[2].x, y2 = rgTri[i].vPosW[2].y, z2 = rgTri[i].vPosW[2].z;

		// get edges (1(a,b,c), 2(a,b,c)) and cross product of edges
		double a1 = x1-x0, b1 = y1-y0, c1 = z1-z0, a2 = x2-x0, b2 = y2-y0, c2 = z2-z0;
		double d0 = b1*c2-b2*c1,  d1 = a2*c1-a1*c2,  d2 = a1*b2-a2*b1;

		// compute integral terms
		Subexpressions(x0,x1,x2,f1x,f2x,f3x,g0x,g1x,g2x,temp0,temp1,temp2);
		Subexpressions(y0,y1,y2,f1y,f2y,f3y,g0y,g1y,g2y,temp0,temp1,temp2);
		Subexpressions(z0,z1,z2,f1z,f2z,f3z,g0z,g1z,g2z,temp0,temp1,temp2);

		// update integrals
		intg[0] += d0*f1x;
		intg[1] += d0*f2x; intg[2] += d1*f2y; intg[3] += d2*f2z;
		intg[4] += d0*f3x; intg[5] += d1*f3y; intg[6] += d2*f3z;
		intg[7] += d0*(y0*g0x+y1*g1x+y2*g2x);
		intg[8] += d1*(z0*g0y+z1*g1y+z2*g2y);
		intg[9] += d2*(x0*g0z+x1*g1z+x2*g2z);
	}
	for (WORD i=0; i<10; i++)
		intg[i] *= mult[i];

	// dDensity of polyhedron
	dDensity = fMass/intg[0];

	// center of fMass
	cm.x = (float)(intg[1]/intg[0]);
	cm.y = (float)(intg[2]/intg[0]);
	cm.z = (float)(intg[3]/intg[0]);

	// inertia tensor relative to center of fMass
	I.m[0][0] = (float)(dDensity*(intg[5]+intg[6]) - fMass*(cm.y*cm.y+cm.z*cm.z));
	I.m[1][1] = (float)(dDensity*(intg[4]+intg[6]) - fMass*(cm.z*cm.z+cm.x*cm.x));
	I.m[2][2] = (float)(dDensity*(intg[4]+intg[5]) - fMass*(cm.x*cm.x+cm.y*cm.y));
	I.m[0][1] = I.m[1][0] = (float)(-dDensity*intg[7] + fMass*cm.x*cm.y);
	I.m[1][2] = I.m[2][1] = (float)(-dDensity*intg[8] + fMass*cm.y*cm.z);
	I.m[2][0] = I.m[0][2] = (float)(-dDensity*intg[9] + fMass*cm.z*cm.x);

	I.m[3][3] = 1.f;
	I.m[0][3] = I.m[1][3] = I.m[2][3] = I.m[3][0] = I.m[3][1] = I.m[3][2] = 0;
}

//The vertices must be in a triangle list order
void ComputeInertiaTensor(Vector3F * rgVert, DWORD nVert, double fMass,
	Matrix4x4F & I, Vector3F & cm, double & dDensity)
{
	if (nVert % 3) {DxUtSendError("ComputeInertiaTensor the rgVert must be divisible by 3.");}
	DWORD nTri = nVert/3;

	ComputeInertiaTensor((STriangleF*)rgVert, nTri, fMass,  I, cm, dDensity);
}


};



	/*D3DXQUATERNION w(-m_AngVel.x, -m_AngVel.y, -m_AngVel.z, 0);
	D3DXQuaternionMultiply(&w, &w, &m_QRot);
	m_QRot = m_QRot + .5f*w*dt;
	D3DXQuaternionNormalize(&m_QRot, &m_QRot);

	D3DXMATRIX rot;
	D3DXMatrixRotationQuaternion(&rot, &m_QRot);
	m_Rot.m[0][0] = rot._11, m_Rot.m[1][0] = rot._21, m_Rot.m[2][0] = rot._31;
	m_Rot.m[0][1] = rot._12, m_Rot.m[1][1] = rot._22, m_Rot.m[2][1] = rot._32;
	m_Rot.m[0][2] = rot._13, m_Rot.m[1][2] = rot._23, m_Rot.m[2][2] = rot._33;*/