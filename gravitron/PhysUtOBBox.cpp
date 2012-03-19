
#include "PhysUtOBBox.h"
#include "PhysUtBSphere.h"

//For use in the COBBox Intersect Test
#define _Abs(x, t) ((t=x) < 0 ? -t : t)

namespace PhysUt {

COBBox::COBBox()
{
	DebugBreak();
}

COBBox::COBBox(ID3DX10Mesh * pMesh, DWORD dwStride)
{
	Compute(pMesh, dwStride);
}

//Set the center, orientation, and halfwidths of the OBBox in local space
COBBox::COBBox(Matrix4x4F & TL, Vector3F & halfWidthsL)
{
	m_CenterW = m_CenterL = TL.GetColumnVec3F(3);
	m_RotVecW[0] = m_RotVecL[0] = TL.GetColumnVec3F(0);
	m_RotVecW[1] = m_RotVecL[1] = TL.GetColumnVec3F(1);
	m_RotVecW[2] = m_RotVecL[2] = TL.GetColumnVec3F(2);
	m_HalfWidthsL = m_HalfWidthsW = halfWidthsL;
}

void COBBox::Compute(ID3DX10Mesh * pMesh, DWORD dwStride)
{
	DWORD nVert = 0;
	Vector3F * rgVert = NULL;

	nVert = 3*pMesh->GetFaceCount();
	rgVert = new Vector3F[nVert];

	DxUt::ExtractVertexTriangleListFromMesh(pMesh, rgVert, dwStride);

	Compute(rgVert, nVert);

	delete[] rgVert;
	rgVert = NULL;
}

void COBBox::Compute(Vector3F * rgVert, DWORD nVert)
{
	if (nVert % 3)
		DxUtSendError("COBBox::Compute nVert must be divisible by 3.");

	Matrix4x4F cov;
	Vector3F mean;
	CovarianceTriangles3x3F(rgVert, nVert, cov, mean);

	Matrix4x4F A;								//Eigen vectors
	Vector3F lambda;							//Eigen values
	JacobiTransformation3x3F(cov, A, lambda);

	m_RotVecL[0] = m_RotVecW[0] = (A.GetColumnVec3F(0)).Normalize();
	m_RotVecL[1] = m_RotVecW[1] = (A.GetColumnVec3F(1)).Normalize();
	m_RotVecL[2] = m_RotVecW[2] = (A.GetColumnVec3F(2)).Normalize();

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
	m_HalfWidthsL = m_HalfWidthsW;

	m_CenterW = 
		.5f*(dMax[0] + dMin[0])*m_RotVecW[0] + 
		.5f*(dMax[1] + dMin[1])*m_RotVecW[1] + 
		.5f*(dMax[2] + dMin[2])*m_RotVecW[2];
	m_CenterL = m_CenterW;
}

bool COBBox::PointIn(Vector3F & pt)
{
	float t;
	if (_Abs(DotXYZ(m_RotVecW[0], pt), t) > m_HalfWidthsW.x)
		return FALSE;
	if (_Abs(DotXYZ(m_RotVecW[1], pt), t) > m_HalfWidthsW.y)
		return FALSE;
	if (_Abs(DotXYZ(m_RotVecW[2], pt), t) > m_HalfWidthsW.z)
		return 0;

	return 1;
}

bool COBBox::Intersect(COBBox & oBB)
{
	//See Ericson, Christer, Real Time Collision Detection, page 101, and
	//See Gottschalk, Stefan, Collision Queries using Oriented Bounding Boxes

	//a is assumed to be the this COBBox
	//b is assumed to be oBB
	FLOAT fRA=0, fRB=0, t=0;
	const FLOAT ep = 1e-4f;
	Vector3F * rVA = m_RotVecW;
	Vector3F * rVB = oBB.m_RotVecW;
	Vector3F & hWA = m_HalfWidthsW;
	Vector3F & hWB = oBB.m_HalfWidthsW;

	//Rotation matrices in a's coordinate frame
    Matrix4x4F rot, aRt;
	rot.m[0][0] = DotXYZ(rVA[0], rVB[0]); aRt.m[0][0] = Abs(rot.m[0][0]) + ep;
	rot.m[0][1] = DotXYZ(rVA[0], rVB[1]); aRt.m[0][1] = Abs(rot.m[0][1]) + ep;
	rot.m[0][2] = DotXYZ(rVA[0], rVB[2]); aRt.m[0][2] = Abs(rot.m[0][2]) + ep;

	rot.m[1][0] = DotXYZ(rVA[1], rVB[0]); aRt.m[1][0] = Abs(rot.m[1][0]) + ep;
	rot.m[1][1] = DotXYZ(rVA[1], rVB[1]); aRt.m[1][1] = Abs(rot.m[1][1]) + ep;
	rot.m[1][2] = DotXYZ(rVA[1], rVB[2]); aRt.m[1][2] = Abs(rot.m[1][2]) + ep;

	rot.m[2][0] = DotXYZ(rVA[2], rVB[0]); aRt.m[2][0] = Abs(rot.m[2][0]) + ep;
	rot.m[2][1] = DotXYZ(rVA[2], rVB[1]); aRt.m[2][1] = Abs(rot.m[2][1]) + ep;
	rot.m[2][2] = DotXYZ(rVA[2], rVB[2]); aRt.m[2][2] = Abs(rot.m[2][2]) + ep;

    //Translation vector T in a's coordinate frame
	Vector3F T(oBB.m_CenterW - m_CenterW);
	T = Vector3F(DotXYZ(T, rVA[0]), DotXYZ(T, rVA[1]), DotXYZ(T, rVA[2]));

	//Axias rotVecA[0]
	fRB = hWB.c[0] * aRt.m[0][0] + hWB.c[1] * aRt.m[0][1] + hWB.c[2] * aRt.m[0][2];
	if (Abs(T.c[0]) > (hWA.c[0] + fRB)) return 0;

	//Axias rotVecA[1]
	fRB = hWB.c[0] * aRt.m[1][0] + hWB.c[1] * aRt.m[1][1] + hWB.c[2] * aRt.m[1][2];
	if (Abs(T.c[1]) > (hWA.c[1] + fRB)) return 0;

	//Axias rotVecA[2]
	fRB = hWB.c[0] * aRt.m[2][0] + hWB.c[1] * aRt.m[2][1] + hWB.c[2] * aRt.m[2][2];
	if (Abs(T.c[2]) > (hWA.c[2] + fRB)) return 0;

	//Axias rotVecB[0]
	fRA = hWA.c[0] * aRt.m[0][0] + hWA.c[1] * aRt.m[1][0] + hWA.c[2] * aRt.m[2][0];
	if (_Abs(T.c[0] * rot.m[0][0] + T.c[1] * rot.m[1][0] + T.c[2] * rot.m[2][0], t) > (fRA + hWB.c[0])) return 0;

	//Axias rotVecB[1]
	fRA = hWA.c[0] * aRt.m[0][1] + hWA.c[1] * aRt.m[1][1] + hWA.c[2] * aRt.m[2][1];
	if (_Abs(T.c[0] * rot.m[0][1] + T.c[1] * rot.m[1][1] + T.c[2] * rot.m[2][1], t) > (fRA + hWB.c[1])) return 0;

	//Axias rotVecB[2]
	fRA = hWA.c[0] * aRt.m[0][2] + hWA.c[1] * aRt.m[1][2] + hWA.c[2] * aRt.m[2][2];
	if (_Abs(T.c[0] * rot.m[0][2] + T.c[1] * rot.m[1][2] + T.c[2] * rot.m[2][2], t) > (fRA + hWB.c[2])) return 0;

	//Axes rotVecA[0] X rotVecB[0];
	fRA = hWA.c[1] * aRt.m[2][0] + hWA.c[2] * aRt.m[1][0];
	fRB = hWB.c[1] * aRt.m[0][2] + hWB.c[2] * aRt.m[0][1];
	if (_Abs(T.c[2] * rot.m[1][0] - T.c[1] * rot.m[2][0], t) > (fRA + fRB)) return 0;

    //Axes rotVecA[0] X rotVecB[1];
	fRA = hWA.c[1] * aRt.m[2][1] + hWA.c[2] * aRt.m[1][1];
	fRB = hWB.c[0] * aRt.m[0][2] + hWB.c[2] * aRt.m[0][0];
	if (_Abs(T.c[2] * rot.m[1][1] - T.c[1] * rot.m[2][1], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[0] X rotVecB[2];
	fRA = hWA.c[1] * aRt.m[2][2] + hWA.c[2] * aRt.m[1][2];
	fRB = hWB.c[0] * aRt.m[0][1] + hWB.c[1] * aRt.m[0][0];
	if (_Abs(T.c[2] * rot.m[1][2] - T.c[1] * rot.m[2][2], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[0];
	fRA = hWA.c[0] * aRt.m[2][0] + hWA.c[2] * aRt.m[0][0];
	fRB = hWB.c[1] * aRt.m[1][2] + hWB.c[2] * aRt.m[1][1];
	if (_Abs(T.c[0] * rot.m[2][0] - T.c[2] * rot.m[0][0], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[1];
	fRA = hWA.c[0] * aRt.m[2][1] + hWA.c[2] * aRt.m[0][1];
	fRB = hWB.c[0] * aRt.m[1][2] + hWB.c[2] * aRt.m[1][0];
	if (_Abs(T.c[0] * rot.m[2][1] - T.c[2] * rot.m[0][1], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[1] X rotVecB[2];
	fRA = hWA.c[0] * aRt.m[2][2] + hWA.c[2] * aRt.m[0][2];
	fRB = hWB.c[0] * aRt.m[1][1] + hWB.c[1] * aRt.m[1][0];
	if (_Abs(T.c[0] * rot.m[2][2] - T.c[2] * rot.m[0][2], t) > (fRA + fRB)) return 0;

	//Axes rotVecA[2] X rotVecB[0];
    fRA = hWA.c[0] * aRt.m[1][0] + hWA.c[1] * aRt.m[0][0];
    fRB = hWB.c[1] * aRt.m[2][2] + hWB.c[2] * aRt.m[2][1];
    if (_Abs(T.c[1] * rot.m[0][0] - T.c[0] * rot.m[1][0], t) > fRA + fRB) return 0;

    //Axes rotVecA[2] X rotVecB[1];
    fRA = hWA.c[0] * aRt.m[1][1] + hWA.c[1] * aRt.m[0][1];
    fRB = hWB.c[0] * aRt.m[2][2] + hWB.c[2] * aRt.m[2][0];
    if (_Abs(T.c[1] * rot.m[0][1] - T.c[0] * rot.m[1][1], t) > fRA + fRB) return 0;

    //Axes rotVecA[2] X rotVecB[2];
    fRA = hWA.c[0] * aRt.m[1][2] + hWA.c[1] * aRt.m[0][2];
    fRB = hWB.c[0] * aRt.m[2][1] + hWB.c[1] * aRt.m[2][0];
    if (_Abs(T.c[1] * rot.m[0][2] - T.c[0] * rot.m[1][2], t) > fRA + fRB) return 0;

	return 1;
}

//Rotation, Translation, Scaling must be expressed in this oBB's cordinate frame
bool COBBox::Intersect(COBBox & oBB, Matrix4x4F & rot, Vector3F & tns, FLOAT fScl)
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

bool COBBox::Intersect(CBoundingVolume * pBV, 
		Vector3F & contactPoint, Vector3F & contactNormal)
{
	//Assume it is a sphere
	CBSphere * pBSph = (CBSphere*)pBV;

	Vector3F d(pBSph->PosW() - m_CenterW);
	Vector3F q(m_CenterW);
	float r = pBSph->RadiusW();

	float dist = DotXYZ(d,  m_RotVecW[0]);
	if (Abs(dist) > (m_HalfWidthsW.x + r)) return 0;
	if (dist > m_HalfWidthsW.x) dist = m_HalfWidthsW.x;
	if (dist < -m_HalfWidthsW.x) dist = -m_HalfWidthsW.x;
	q += dist * m_RotVecW[0];

	dist = DotXYZ(d,  m_RotVecW[1]);
	if (Abs(dist) > (m_HalfWidthsW.y + r)) return 0;
	if (dist > m_HalfWidthsW.y) dist = m_HalfWidthsW.y;
	if (dist < -m_HalfWidthsW.y) dist = -m_HalfWidthsW.y;
	q += dist * m_RotVecW[1];

	dist = DotXYZ(d,  m_RotVecW[2]);
	if (Abs(dist) > (m_HalfWidthsW.z + r)) return 0;
	if (dist > m_HalfWidthsW.z) dist = m_HalfWidthsW.z;
	if (dist < -m_HalfWidthsW.z) dist = -m_HalfWidthsW.z;
	q += dist * m_RotVecW[2];

	contactPoint = q;
	contactNormal = (q - pBSph->PosW()).Normalize();

	return 1;
}

COBBox & COBBox::operator=(COBBox & ref)
{
	memcpy(this, &ref, sizeof(COBBox));
	return *this;
}


};
