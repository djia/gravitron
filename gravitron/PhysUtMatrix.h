
#ifndef DXUTMATRTIX_H
#define DXUTMATRIX_H

#include <d3dx10.h>
#include "DxUtError.h"

#include "PhysUtVector.h"

namespace PhysUt {

//VERY IMPORTANT!
//Matrix4x4F assumes that its columns are vectors
//not its rows. All its member functions and all
//other functions and class assume this except for 
//the camera class which assumes row vectors. Note
//also that D3D10 likes a left handed coordinate
//system in which matrices are row vector form where
//as OpenGL prefers a right handed coordinate system
//where all of its matrices should be in column form.

class Vector3F;
struct STriangleF;

class Matrix4x4F {
public:
	float m[4][4];
public:
	Matrix4x4F() {}
	//Matrix4x4F(Matrix4x4F & copy) {
	//	memcpy(m, copy.m, sizeof(float)*16);}
	Matrix4x4F(float m11, float m21, float m31, float m41,
		float m12, float m22, float m32, float m42,
		float m13, float m23, float m33, float m43,
		float m14, float m24, float m34, float m44);
	Matrix4x4F(float * _c) {memcpy(m, _c, sizeof(float)*16);}
	//Matrix4x4F(float _c[4][4]) {memcpy(m, _c, sizeof(float)*16);}
	//~Matrix4x4F() {}

	Matrix4x4F operator+() {return *this;}
	Matrix4x4F operator-() {return (-1.f)*(*this);}

	Matrix4x4F operator+(Matrix4x4F & A);
	Matrix4x4F operator-(Matrix4x4F & A);
	Matrix4x4F operator*(Matrix4x4F & A);
	friend Matrix4x4F operator*(FLOAT flt, Matrix4x4F & A);
	Matrix4x4F operator*(FLOAT flt);

	Matrix4x4F & operator=(Matrix4x4F & A);
	Matrix4x4F & operator+=(Matrix4x4F & A);
	Matrix4x4F & operator-=(Matrix4x4F & A);
	Matrix4x4F & operator*=(Matrix4x4F & A);
	Matrix4x4F & operator*=(FLOAT flt);

	Matrix4x4F Inverse();
	Matrix4x4F Transpose();
	Matrix4x4F InverseTranspose();

	/* Each operation applies to myself */
	Matrix4x4F & MZero();
	Matrix4x4F & MIdenity();
	Matrix4x4F & MInverse();
	Matrix4x4F & MTranspose();
	Matrix4x4F & MInverseTranspose();
	Matrix4x4F & MScaling(Vector3F & scl);
	Matrix4x4F & MScaling(float x, float y, float z);
	Matrix4x4F & MTranslation(Vector3F trans);
	Matrix4x4F & MTranslation(float x, float y, float z);
	Matrix4x4F & MRotationXLH(float fTheta);
	Matrix4x4F & MRotationYLH(float fTheta);
	Matrix4x4F & MRotationZLH(float fTheta);
	Matrix4x4F & MRotationAxisLH(Vector3F & v, float fTheta);
	Matrix4x4F & MConstruct(Vector3F & translation, Matrix4x4F & rot);

	Vector3F GetColumnVec3F(DWORD c) {return Vector3F(m[0][c], m[1][c], m[2][c]); }
	Vector3F GetRowVec3F(DWORD c) {return Vector3F(m[c][0], m[c][1], m[c][2]); }
};

inline Matrix4x4F::Matrix4x4F(
	float m11, float m21, float m31, float m41,
	float m12, float m22, float m32, float m42,
	float m13, float m23, float m33, float m43,
	float m14, float m24, float m34, float m44)
{
	m[0][0] = m11, m[1][0] = m21, m[2][0] = m31, m[3][0] = m41;
	m[0][1] = m12, m[1][1] = m22, m[2][1] = m32, m[3][1] = m42;
	m[0][2] = m13, m[1][2] = m23, m[2][2] = m33, m[3][2] = m43;
	m[0][3] = m14, m[1][3] = m24, m[2][3] = m34, m[3][3] = m44;
}

inline Matrix4x4F & Matrix4x4F::operator=(Matrix4x4F & A)
{
	m[0][0] = A.m[0][0], m[1][0] = A.m[1][0], m[2][0] = A.m[2][0], m[3][0] = A.m[3][0];
	m[0][1] = A.m[0][1], m[1][1] = A.m[1][1], m[2][1] = A.m[2][1], m[3][1] = A.m[3][1];
	m[0][2] = A.m[0][2], m[1][2] = A.m[1][2], m[2][2] = A.m[2][2], m[3][2] = A.m[3][2];
	m[0][3] = A.m[0][3], m[1][3] = A.m[1][3], m[2][3] = A.m[2][3], m[3][3] = A.m[3][3];
	return *this;
}

inline Matrix4x4F & Matrix4x4F::MZero()
{
	m[0][0] = m[1][0] = m[2][0] = m[3][0] = 0;
	m[0][1] = m[1][1] = m[2][1] = m[3][2] = 0;
	m[0][2] = m[1][2] = m[2][2] = m[3][3] = 0;
	m[0][3] = m[1][3] = m[2][3] = m[3][3] = 0;
	return *this;
}

inline Matrix4x4F & Matrix4x4F::MIdenity()
{
	m[0][0] = 1.f; m[1][0] = m[2][0] = m[3][0] = 0;
	m[1][1] = 1.f; m[0][1] = m[2][1] = m[3][1] = 0;
	m[2][2] = 1.f; m[0][2] = m[1][2] = m[3][2] = 0;
	m[3][3] = 1.f; m[0][3] = m[1][3] = m[2][3] = 0;
	return *this;
}

inline Matrix4x4F _Idenity4x4F()
{
	return Matrix4x4F(
		1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f);
}


inline Matrix4x4F & Matrix4x4F::MConstruct(Vector3F & t, Matrix4x4F & r)
{
	m[0][0] = r.m[0][0], m[1][0] = r.m[1][0], m[2][0] = r.m[2][0], m[3][0] = t.x;
	m[0][1] = r.m[0][1], m[1][1] = r.m[1][1], m[2][1] = r.m[2][1], m[3][1] = t.y;
	m[0][2] = r.m[0][2], m[1][2] = r.m[1][2], m[2][2] = r.m[2][2], m[3][2] = t.z;
	m[0][3] = 0.f,		 m[1][3] = 0.f,		  m[2][3] = 0.f,	   m[3][3] = 1.f;
	return *this;
}

};


#endif
