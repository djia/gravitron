
#ifndef PHYSUTOBBOX_H
#define PHYSUTOBBOX_H

#include "PhysUtBoundingVolume.h"

namespace PhysUt {

class COBBox : public CBoundingVolume {
protected:
	//friend class BVTree;

	/* The world space 
	 * Note that all tests will be preformed on world space */
	Vector3F m_CenterW;			//The center of the OBB
	Vector3F m_HalfWidthsW;		//The axis length of the OBB
	Vector3F m_RotVecW[3];		//The axis vectors of the OBB

	/* The local space BS */
	Vector3F m_CenterL;
	Vector3F m_HalfWidthsL;
	Vector3F m_RotVecL[3];
public:
	COBBox();
	COBBox(ID3DX10Mesh * pMesh, DWORD dwStride);
	//Set the center, orientation, and halfwidths of the OBBox in local space
	COBBox(Matrix4x4F & TL, Vector3F & halfWidthsL);
	//~COBBox() {}

	void Compute(ID3DX10Mesh * pMesh, DWORD dwStride);
	void Compute(Vector3F * rgVert, DWORD nVert);

	bool PointIn(Vector3F & pt);
	bool Intersect(COBBox & oBB);
	//Rotation, Translation, Scaling of oBB must be expressed relative to the function caller's OBB frame
	bool Intersect(COBBox & oBB, Matrix4x4F & rot, Vector3F & trans, FLOAT fScl);
	bool Intersect(CBoundingVolume * pBSph, 
		Vector3F & contactPoint, Vector3F & contactNormal);

	//TransformOBB is done as follows:
	//m_CenterW = trans + m_CenterL,
	//m_RotVecW[i] = rot*m_RotVecL[i],
	//The transformation is clearly from local space to world space
	void Transform(Matrix4x4F & T);
	
	/* Converts the axis vectors into a rotation matrix of column form */
	void Rotation(Matrix4x4F & rot);
	/* Converts the axis vectors into a rotation matrix of row form */
	void RotationT(Matrix4x4F & rot);

	COBBox & operator=(COBBox & ref);
};

inline void COBBox::Transform(Matrix4x4F & T)
{
	m_CenterW = T*m_CenterL;
	m_RotVecW[0] = T^m_RotVecL[0];
	m_RotVecW[1] = T^m_RotVecL[1];
	m_RotVecW[2] = T^m_RotVecL[2];
}

inline void COBBox::Rotation(Matrix4x4F & rot)
{
	rot.m[0][0] = m_RotVecW[0].x, rot.m[1][0] = m_RotVecW[0].y, rot.m[2][0] = m_RotVecW[0].z, rot.m[3][0] = 0;
	rot.m[0][1] = m_RotVecW[1].x, rot.m[1][1] = m_RotVecW[1].y, rot.m[2][1] = m_RotVecW[1].z, rot.m[3][1] = 0;
	rot.m[0][2] = m_RotVecW[2].x, rot.m[1][2] = m_RotVecW[2].y, rot.m[2][2] = m_RotVecW[2].z, rot.m[3][2] = 0;
	rot.m[0][3] = 0,              rot.m[1][3] = 0,              rot.m[2][3] = 0,              rot.m[3][3] = 1.f;
}

inline void COBBox::RotationT(Matrix4x4F & rot)
{
	rot.m[0][0] = m_RotVecW[0].x, rot.m[0][1] = m_RotVecW[0].y, rot.m[0][2] = m_RotVecW[0].z, rot.m[0][3] = 0;
	rot.m[1][0] = m_RotVecW[1].x, rot.m[1][1] = m_RotVecW[1].y, rot.m[1][2] = m_RotVecW[1].z, rot.m[1][3] = 0;
	rot.m[2][0] = m_RotVecW[2].x, rot.m[2][1] = m_RotVecW[2].y, rot.m[2][2] = m_RotVecW[2].z, rot.m[2][3] = 0;
	rot.m[3][0] = 0,              rot.m[3][1] = 0,              rot.m[3][2] = 0,              rot.m[3][3] = 1.f;
}


};

#endif
