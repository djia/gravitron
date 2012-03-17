
#ifndef DXUTBOUNDINGVOLUME_H
#define DXUTBOUNDINGVOLUME_H

#include "DxUtMesh.h"

namespace PhysUt {

class CBoundingVolume {
public:
	CBoundingVolume() {}
	//~CBSphere() {}

	//It is assumed that a vertex's position is stored
	//in the first 12 bytes of a vertex's data sturcture.
	//Furthermore, the CBoundingVloume will be computed with the
	//vertex buffer before it has been commited to a device.
	virtual void Compute(ID3DX10Mesh * pMesh, DWORD dwStride) = 0;
	virtual void Compute(Vector3F * rgVert, DWORD nVert) = 0;

	virtual bool PointIn(Vector3F & pt) = 0;
	//Determine if two BV's intersect and find the contact point and normal between them
	virtual bool Intersect(CBoundingVolume * pBV, 
		Vector3F & contactPoint, Vector3F & contactNormal) = 0;
	//Transforms the position and orientation of this volume
	//T should be an orthogonal matrix (it does not include scalings)
	virtual void Transform(Matrix4x4F & T) = 0;
};


};


#endif