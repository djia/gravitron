
#ifndef DXUTTRIANGLE_H
#define DXUTTRIANGLE_H

#include "PhysUtVector.h"

namespace PhysUt {

struct STriangleF {
	STriangleF() {}
	STriangleF(Vector3F & v1, Vector3F & v2, Vector3F & v3) {
		vPosW[0] = v1; vPosW[1] = v2; vPosW[2] = v3; 
	}
	//~STriangleF() {}

	Vector3F vPosW[3];

	//vPosW = Matrix4x4 * vPosW
	STriangleF & Transform(Matrix4x4F & m);
	STriangleF & operator=(STriangleF & tri); 

	FLOAT Area() {
		Vector3F v1(vPosW[1] - vPosW[0]);
		Vector3F v2(vPosW[2] - vPosW[0]);
		return Vector3F(CrossXYZ(v1, v2)).Length()/2.f;
	}
	Vector3F Centroid() {
		Vector3F v(vPosW[0]+vPosW[1]+vPosW[2]);
		return v/3.f;
	}
	Vector3F Normal() {
		Vector3F v1(vPosW[1] - vPosW[0]);
		Vector3F v2(vPosW[2] - vPosW[0]);
		return Vector3F(CrossXYZ(v1,v2)).Normalize();
	}
	Vector3F NormalSq() {
		Vector3F v1(vPosW[1] - vPosW[0]);
		Vector3F v2(vPosW[2] - vPosW[0]);
		return Vector3F(CrossXYZ(v1,v2));
	}
};

bool TriSegmentIntersect(STriangleF & tri,Vector3F & e1, Vector3F & e2, Vector3F & iPos);
bool TriRayIntersect(STriangleF & tri, Vector3F & pos, Vector3F & vec, Vector3F & iPos);

};


#endif

