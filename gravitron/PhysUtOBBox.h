
#ifndef DXUTOBBOX_H
#define DXUTOBBOX_H

#include "DxUtMesh.h"

namespace PhysUt {

class COBBox { 
protected:
	friend class BVTree;

	/* The OBB is defined in world space only */
	/* This class should never be used except for BVTree's use of it */
	Vector3F m_CenterW;			//The center of the OBB
	Vector3F m_HalfWidthsW;		//The axis length of the OBB
	Vector3F m_RotVecW[3];		//The axis vectors of the OBB
private:
	COBBox();
	//~COBBox() {}

	void Compute(ID3DX10Mesh * pMesh, DWORD dwStride);
	void ComputeOBB(Vector3F * rgVert, DWORD nVert);

	BOOL PointIn(Vector3F & pt);
	//Rotation, Translation, Scaling of oBB must be expressed relative to the function caller's OBB frame
	BOOL Intersect(COBBox & oBB, Matrix4x4F & rot, Vector3F & trans, FLOAT fScl);
	
	/* Converts the axis vectors into a rotation matrix of column form */
	void Rotation(Matrix4x4F & rot);
	/* Converts the axis vectors into a rotation matrix of row form */
	void RotationT(Matrix4x4F & rot);

	COBBox & operator=(COBBox & ref);
};

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
