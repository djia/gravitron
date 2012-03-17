
#ifndef DXUTBSPHERE_H
#define DXUTBSPHERE_H

#include "PhysUtBoundingVolume.h"

namespace PhysUt {

class CBSphere : public CBoundingVolume {
private:
	friend class CCamera;

	/* The world space BS 
	 * Note that all tests will be preformed on world space */
	Vector3F m_PosW;
	float m_fRadiusW;

	/* The local space BS */
	Vector3F m_PosL;
	float m_fRadiusL;
public:
	CBSphere();
	CBSphere(Vector3F & posL, float fRadiusL);
	CBSphere(ID3DX10Mesh * pMesh, DWORD dwStride); 
	//~CBSphere() {}

	void Compute(ID3DX10Mesh * pMesh, DWORD dwStride);
	void Compute(Vector3F * rgVert, DWORD nVert);

	bool PointIn(Vector3F & pt);
	bool Intersect(CBoundingVolume * pBSph, 
		Vector3F & contactPoint, Vector3F & contactNormal);
	void Transform(Matrix4x4F & T) {
		m_PosW = T*m_PosL;
	}

	Vector3F & PosW() {return m_PosW;}
	FLOAT RadiusW() {return m_fRadiusW;}
};


};

#endif