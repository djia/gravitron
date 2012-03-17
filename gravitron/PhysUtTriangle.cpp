
#include "PhysUtTriangle.h"

#define Abs(x) ((x < 0) ? (-x) : x)
#define Cross3D(a, b) (Vector3F((float)(a[1]*b[2] - a[2]*b[1]), \
	(float)(a[2]*b[0] - a[0]*b[2]), (float)(a[0]*b[1] - a[1]*b[0])))

namespace PhysUt {

//vPosW = Matrix4x4 x vPosW
STriangleF & STriangleF::Transform(Matrix4x4F & m)
{ 
	vPosW[0] = m*vPosW[0];
	vPosW[1] = m*vPosW[1];
	vPosW[2] = m*vPosW[2];
	return *this;
}

STriangleF & STriangleF::operator=(STriangleF & tri)
{
	memcpy(this, &tri, sizeof(STriangleF));
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////   Triangle Functions   /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TriangleSegmentIntersect(STriangleF & tri,
	Vector3F & e1, Vector3F & e2, Vector3F & iPos)
{
	//Ericson, Christer, Real Time Collision Detection 
	//5.3.6 Intersecting Ray or Segment Against Triangle

	Vector3F & A = tri.vPosW[0], & B = tri.vPosW[1], & C = tri.vPosW[2];
	Vector3F q1(B - A), q2(C - A), eVec(e1 - e2);

	Vector3F cr1(CrossXYZ(q1,q2));
	float d = DotXYZ(eVec, cr1);
	if (d <= 0.f) return 0;

	Vector3F vAP(e1-A);
	float t = DotXYZ(vAP, cr1);
	if (t < 0.f || t > d) return 0;

	Vector3F cr2(CrossXYZ(eVec,vAP));
	float v = DotXYZ(q2, cr2);
	if (v < 0.f || v > d) return 0;
	float w = -DotXYZ(q1, cr2);
	if (w < 0.f || (v+w) > d) return 0;

	iPos = e1 + (t/d)*(-eVec);

	return 1;
}

bool TriangleRayIntersect(STriangleF & tri, Vector3F & pos,
	Vector3F & vec, Vector3F & iPos)
{
	//Ericson, Christer, Real Time Collision Detection 
	//5.3.6 Intersecting Ray or Segment Against Triangle

	Vector3F & A = tri.vPosW[0], & B = tri.vPosW[1], & C = tri.vPosW[2];
	Vector3F q1(B - A), q2(C - A), eVec(-vec);

	Vector3F cr1(CrossXYZ(q1,q2));
	float d = DotXYZ(eVec, cr1);
	if (d <= 0.f) return 0;

	Vector3F vAP(pos-A);
	float t = DotXYZ(vAP, cr1);
	if (t < 0.f) return 0;

	Vector3F cr2(CrossXYZ(eVec,vAP));
	float v = DotXYZ(q2, cr2);
	if (v < 0.f || v > d) return 0;
	float w = -DotXYZ(q1, cr2);
	if (w < 0.f || (v+w) > d) return 0;

	iPos = pos + (t/d)*(vec);

	return 1;
}


};