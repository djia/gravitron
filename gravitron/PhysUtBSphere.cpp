

#include "PhysUtBSphere.h"

namespace PhysUt {

CBSphere::CBSphere():m_PosL(0, 0, 0), m_fRadiusL(1.f), m_PosW(0, 0, 0), m_fRadiusW(1.f)
{
}

CBSphere::CBSphere(Vector3F & posL, float fRadiusL):
	m_PosL(posL), m_fRadiusL(fRadiusL), m_PosW(posL), m_fRadiusW(fRadiusL)
{
}

CBSphere::CBSphere(ID3DX10Mesh * pMesh, DWORD dwStride) 
{
	Compute(pMesh, dwStride);
}

void CBSphere::Compute(ID3DX10Mesh * pMesh, DWORD dwStride)
{
	UINT nVert = pMesh->GetVertexCount();
	Vector3F * rgVert = new Vector3F[nVert];
	DxUt::ExtractVerticesFromMesh(pMesh, rgVert, dwStride);

	Compute(rgVert, nVert);
	delete[] rgVert;
}

void CBSphere::Compute(Vector3F * rgVert, DWORD nVert)
{
	//See Christer, Ericson, Real Time Collision Detection, page 89
	DWORD minX=0, maxX=0, minY=0, maxY=0, minZ=0, maxZ=0;
	for (DWORD i=1; i<nVert; i++) {
		if (rgVert[i].x < rgVert[minX].x) minX = i;
		if (rgVert[i].x > rgVert[maxX].x) maxX = i;
		if (rgVert[i].y < rgVert[minY].y) minY = i;
		if (rgVert[i].y > rgVert[maxY].y) maxY = i;
		if (rgVert[i].z < rgVert[minZ].z) minZ = i;
		if (rgVert[i].z > rgVert[maxZ].z) maxZ = i;
	}

	float dX = (rgVert[maxX] - rgVert[minX]).LengthSq();
	float dY = (rgVert[maxY] - rgVert[minY]).LengthSq();
	float dZ = (rgVert[maxZ] - rgVert[minZ]).LengthSq();

	Vector3F minD, maxD;
	if (dX > dY) {
		if (dX > dZ) {
			minD = rgVert[minX];
			maxD = rgVert[maxX]; }
		else {
			minD = rgVert[minZ];
			maxD = rgVert[maxZ]; }
	} else if (dY > dZ){
		minD = rgVert[minY];
		maxD = rgVert[maxY]; }
	else {
		minD = rgVert[minZ];
		maxD = rgVert[maxZ]; 
	}

	m_PosW = .5f*(minD + maxD);
	m_fRadiusW = (m_PosW - maxD).Length();
	
	float len = 0;
	for (DWORD i=0; i<nVert; i++) {
		Vector3F vec(rgVert[i] - m_PosW);
		if ((len = vec.LengthSq()) > m_fRadiusW*m_fRadiusW) {
			float dist = (float)sqrt((double)len);
			float newR = .5f*(m_fRadiusW + dist);
			m_PosW += (newR - m_fRadiusW)*vec/dist;
			m_fRadiusW = newR;
		}
	}

	m_PosL = m_PosW;
	m_fRadiusL = m_fRadiusL;
}

bool CBSphere::PointIn(Vector3F & pt)
{
	return ((pt-m_PosW).LengthSq() <= (m_fRadiusW*m_fRadiusW));
}

bool CBSphere::Intersect(CBoundingVolume * v, Vector3F & contactPoint, Vector3F & contactNormal)
{
	CBSphere * pBSph = (CBSphere*)v;
	float d = (m_PosW - pBSph->m_PosW).LengthSq();
	float r = m_fRadiusW + pBSph->m_fRadiusW;

	if (d <= r*r) {
		Vector3F dir(m_PosW - pBSph->m_PosW);
		contactPoint = .5f*dir + pBSph->m_PosW;
		contactNormal = dir.Normalize();
		return 1;
	}
	return 0;
}


};