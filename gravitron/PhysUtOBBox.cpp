
#include "PhysUtOBBox.h"

//For use in the COBBox Intersect Test
#define _Abs(x, t) ((t=x) < 0 ? -t : t)

namespace PhysUt {

COBBox::COBBox():m_CenterW(0, 0, 0), m_HalfWidthsW(0, 0, 0)
{
	ZeroMemory(&m_RotVecW[0], sizeof(Vector3F));
	ZeroMemory(&m_RotVecW[1], sizeof(Vector3F));
	ZeroMemory(&m_RotVecW[2], sizeof(Vector3F));
}

void COBBox::Compute(ID3DX10Mesh * pMesh, DWORD dwStride)
{
	DWORD nVert = 0;
	Vector3F * rgVert = NULL;

	nVert = 3*pMesh->GetFaceCount();
	rgVert = new Vector3F[nVert];

	DxUt::ExtractVertexTriangleListFromMesh(pMesh, rgVert, dwStride);

	ComputeOBB(rgVert, nVert);

	delete[] rgVert;
	rgVert = NULL;
}

void COBBox::ComputeOBB(Vector3F * rgVert, DWORD nVert)
{
	if (nVert % 3)
		DxUtSendError("COBBox::Compute nVert must be divisible by 3.");

	Matrix4x4F cov;
	Vector3F mean;
	/*if (method == CVVertices) 
		CovarianceVertices3x3F(rgVert, nVert, cov, mean);	
	else CovarianceTriangles3x3F(rgVert, nVert, cov, mean);*/

	Matrix4x4F A;								//Eigen vectors
	Vector3F lambda;							//Eigen values
	//JacobiTransformation3x3F(cov, A, lambda);

	m_RotVecW[0] = (A.GetColumnVec3F(0)).Normalize();
	m_RotVecW[1] = (A.GetColumnVec3F(1)).Normalize();
	m_RotVecW[2] = (A.GetColumnVec3F(2)).Normalize();

	FLOAT dot = 0;
	FLOAT dMin[3] = {FLT_MAX, FLT_MAX, FLT_MAX};
	FLOAT dMax[3] = {-FLT_MAX, -FLT_MAX, -FLT_MAX};
	for (DWORD i=0; i<nVert; i++) {
		Vector3F & v = rgVert[i];
		dot = DotXYZ(m_RotVecW[0], v);
		if (dot < dMin[0]) 
			dMin[0] = dot;
		if (dot > dMax[0])
			dMax[0] = dot;

		dot = DotXYZ(m_RotVecW[1], v);
		if (dot < dMin[1]) 
			dMin[1] = dot;
		if (dot > dMax[1])
			dMax[1] = dot;

		dot = DotXYZ(m_RotVecW[2], v);
		if (dot < dMin[2]) 
			dMin[2] = dot;
		if (dot > dMax[2])
			dMax[2] = dot;
	}

	m_HalfWidthsW.x = .5f*(dMax[0] - dMin[0]);
	m_HalfWidthsW.y = .5f*(dMax[1] - dMin[1]);
	m_HalfWidthsW.z = .5f*(dMax[2] - dMin[2]);

	m_CenterW = 
		.5f*(dMax[0] + dMin[0])*m_RotVecW[0] + 
		.5f*(dMax[1] + dMin[1])*m_RotVecW[1] + 
		.5f*(dMax[2] + dMin[2])*m_RotVecW[2];
}

BOOL COBBox::PointIn(Vector3F & pt)
{
	if (fabs(DotXYZ(m_RotVecW[0], pt)) > m_HalfWidthsW.x)
		return FALSE;
	if (fabs(DotXYZ(m_RotVecW[1], pt)) > m_HalfWidthsW.y)
		return FALSE;
	if (fabs(DotXYZ(m_RotVecW[2], pt)) > m_HalfWidthsW.z)
		return FALSE;

	return TRUE;
}

//Rotation, Translation, Scaling must be expressed in this oBB's cordinate frame
BOOL COBBox::Intersect(COBBox & oBB, Matrix4x4F & rot, Vector3F & tns, FLOAT fScl)
{
	//See Ericson, Christer, Real Time Collision Detection, page 101, and
	//Gottschalk, Stefan, Collision Queries using Oriented Bounding Boxes

	//a is assumed to be the this COBBox
	//b is assumed to be oBB
	float fRA=0, fRB=0, t=0;
	const float ep = 1e-4f;
	Vector3F & hWA = m_HalfWidthsW;
	Vector3F hWB(fScl*oBB.m_HalfWidthsW);

	//Rotation matrices in a's coordinate frame
    Matrix4x4F aRt;
	aRt.m[0][0] = Abs(rot.m[0][0]) + ep;
	aRt.m[0][1] = Abs(rot.m[0][1]) + ep;
	aRt.m[0][2] = Abs(rot.m[0][2]) + ep;

	aRt.m[1][0] = Abs(rot.m[1][0]) + ep;
	aRt.m[1][1] = Abs(rot.m[1][1]) + ep;
	aRt.m[1][2] = Abs(rot.m[1][2]) + ep;

	aRt.m[2][0] = Abs(rot.m[2][0]) + ep;
	aRt.m[2][1] = Abs(rot.m[2][1]) + ep;
	aRt.m[2][2] = Abs(rot.m[2][2]) + ep;

	//Axias rotVecA[0]
	fRB = hWB.c[0] * aRt.m[0][0] + hWB.c[1] * aRt.m[0][1] + hWB.c[2] * aRt.m[0][2];
	if (Abs(tns.c[0]) > (hWA.c[0] + fRB)) return 0;

	//Axias rotVecA[1]
	fRB = hWB.c[0] * aRt.m[1][0] + hWB.c[1] * aRt.m[1][1] + hWB.c[2] * aRt.m[1][2];
	if (Abs(tns.c[1]) > (hWA.c[1] + fRB)) return 0;

	//Axias rotVecA[2]
	fRB = hWB.c[0] * aRt.m[2][0] + hWB.c[1] * aRt.m[2][1] + hWB.c[2] * aRt.m[2][2];
	if (Abs(tns.c[2]) > (hWA.c[2] + fRB)) return 0;

	//Axias rotVecB[0]
	fRA = hWA.c[0] * aRt.m[0][0] + hWA.c[1] * aRt.m[1][0] + hWA.c[2] * aRt.m[2][0];
	if (_Abs(tns.c[0] * rot.m[0][0] + tns.c[1] * rot.m[1][0] + tns.c[2] * rot.m[2][0], t) > (fRA + hWB.c[0])) return 0;

	//Axias rotVecB[1]
	fRA = hWA.c[0] * aRt.m[0][1] + hWA.c[1] * aRt.m[1][1] + hWA.c[2] * aRt.m[2][1];
	if (_Abs(tns.c[0] * rot.m[0][1] + tns.c[1] * rot.m[1][1] + tns.c[2] * rot.m[2][1], t) > (fRA + hWB.c[1])) return 0;

	//Axias rotVecB[2]
	fRA = hWA.c[0] * aRt.m[0][2] + hWA.c[1] * aRt.m[1][2] + hWA.c[2] * aRt.m[2][2];
	if (_Abs(tns.c[0] * rot.m[0][2] + tns.c[1] * rot.m[1][2] + tns.c[2] * rot.m[2][2], t) > (fRA + hWB.c[2])) return 0;

	//Axes rotVecA[0] X rotVecB[0];
	fRA = hWA.c[1] * aRt.m[2][0] + hWA.c[2] * aRt.m[1][0];
	fRB = hWB.c[1] * aRt.m[0][2] + hWB.c[2] * aRt.m[0][1];
	if (_Abs(tns.c[2] * rot.m[1][0] - tns.c[1] * rot.m[2][0], t) > (fRA + fRB)) return 0;

    //Axes rotVecA[0] X rotVecB[1];
	fRA = hWA.c[1] * aRt.m[2][1] + hWA.c[2] * aRt.m[1][1];
	fRB = hWB.c[0] * aRt.m[0][2] + hWB.c[2] * aRt.m[0][0];
	if (_Abs(tns.c[2] * rot.m[1][1] - tns.c[1] * rot.m[2][1], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[0] X rotVecB[2];
	fRA = hWA.c[1] * aRt.m[2][2] + hWA.c[2] * aRt.m[1][2];
	fRB = hWB.c[0] * aRt.m[0][1] + hWB.c[1] * aRt.m[0][0];
	if (_Abs(tns.c[2] * rot.m[1][2] - tns.c[1] * rot.m[2][2], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[0];
	fRA = hWA.c[0] * aRt.m[2][0] + hWA.c[2] * aRt.m[0][0];
	fRB = hWB.c[1] * aRt.m[1][2] + hWB.c[2] * aRt.m[1][1];
	if (_Abs(tns.c[0] * rot.m[2][0] - tns.c[2] * rot.m[0][0], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[1];
	fRA = hWA.c[0] * aRt.m[2][1] + hWA.c[2] * aRt.m[0][1];
	fRB = hWB.c[0] * aRt.m[1][2] + hWB.c[2] * aRt.m[1][0];
	if (_Abs(tns.c[0] * rot.m[2][1] - tns.c[2] * rot.m[0][1], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[2];
	fRA = hWA.c[0] * aRt.m[2][2] + hWA.c[2] * aRt.m[0][2];
	fRB = hWB.c[0] * aRt.m[1][1] + hWB.c[1] * aRt.m[1][0];
	if (_Abs(tns.c[0] * rot.m[2][2] - tns.c[2] * rot.m[0][2], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[2] X rotVecB[0];
    fRA = hWA.c[0] * aRt.m[1][0] + hWA.c[1] * aRt.m[0][0];
    fRB = hWB.c[1] * aRt.m[2][2] + hWB.c[2] * aRt.m[2][1];
    if (_Abs(tns.c[1] * rot.m[0][0] - tns.c[0] * rot.m[1][0], t) > fRA + fRB) return 0;

    //Axes rotVecA[2] X rotVecB[1];
    fRA = hWA.c[0] * aRt.m[1][1] + hWA.c[1] * aRt.m[0][1];
    fRB = hWB.c[0] * aRt.m[2][2] + hWB.c[2] * aRt.m[2][0];
    if (_Abs(tns.c[1] * rot.m[0][1] - tns.c[0] * rot.m[1][1], t) > fRA + fRB) return 0;

    //Axes rotVecA[2] X rotVecB[2];
    fRA = hWA.c[0] * aRt.m[1][2] + hWA.c[1] * aRt.m[0][2];
    fRB = hWB.c[0] * aRt.m[2][1] + hWB.c[1] * aRt.m[2][0];
    if (_Abs(tns.c[1] * rot.m[0][2] - tns.c[0] * rot.m[1][2], t) > fRA + fRB) return 0;

	return 1;
}

COBBox & COBBox::operator=(COBBox & ref)
{
	memcpy(this, &ref, sizeof(COBBox));
	return *this;
}


};
