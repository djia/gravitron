
#include "PhysUtVector.h"
#include "PhysUtMatrix.h"

namespace PhysUt {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     Vector2F    ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2F Vector2F::Normalize()
{
	double mag = sqrt(x*x + y*y);
	if (mag < 1.e-8)
		return Vector2F(x*1.e-8, y*1.e-8);

	float mul = (float)(1.0/mag);
	return Vector2F(x*mul, y*mul);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     Vector3F    ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3F Vector3F::Normalize()
{
	double mag = sqrt(x*x + y*y + z*z); 
	if (mag == 0) return Vector3F(0, 0, 0);
	//Assert(mag != 0, "Vector3F::Normalize vector of magnitude 0 was requested to be normalized.");
	
	mag = 1.0/mag;
	return Vector3F(x*mag, y*mag, z*mag);
}

Vector3F Vector3F::NormalizeSq()
{
	double mag = x*x + y*y + z*z; 
	Assert(mag != 0, "Vector3F::Normalize vector of magnitude 0 was requested to be normalized.");
	
	mag = 1.0/mag;
	return Vector3F(x*x*mag, y*y*mag, z*z*mag);
}

Vector3F operator*(Matrix4x4F & A, Vector3F & v)
{
	return Vector3F(
		A.m[0][0]*v.x + A.m[0][1]*v.y + A.m[0][2]*v.z + A.m[0][3],
		A.m[1][0]*v.x + A.m[1][1]*v.y + A.m[1][2]*v.z + A.m[1][3],
		A.m[2][0]*v.x + A.m[2][1]*v.y + A.m[2][2]*v.z + A.m[2][3]);
}

Vector3F operator*(Vector3F & v, Matrix4x4F & A)
{
	return Vector3F(
		v.x*A.m[0][0] + v.y*A.m[1][0] + v.z*A.m[2][0] + A.m[3][0],
		v.x*A.m[0][1] + v.y*A.m[1][1] + v.z*A.m[2][1] + A.m[3][1],
		v.x*A.m[0][2] + v.y*A.m[1][2] + v.z*A.m[2][2] + A.m[3][2]);
}

Matrix4x4F Vector3F::SkewMatrix3x3F()
{
	return Matrix4x4F(0, z, -y, 0, -z, 0, x, 0, y, -x, 0, 0, 0, 0, 0, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     Vector4F    ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector4F Vector4F::Normalize()
{
	double mag = sqrt(x*x + y*y + z*z + w*w);
	if (mag < 1.e-8)
		return Vector4F(x*1.e-8, y*1.e-8, z*1.e-8, w*1.e-8);

	float mul = (float)(1.0/mag); 
	return Vector4F(x*mul, y*mul, z*mul, w*mul);
}

Vector4F operator*(Matrix4x4F & A, Vector4F & v)
{
	return Vector4F(
		A.m[0][0]*v.x + A.m[0][1]*v.y + A.m[0][2]*v.z + A.m[0][3]*v.w,
		A.m[1][0]*v.x + A.m[1][1]*v.y + A.m[1][2]*v.z + A.m[1][3]*v.w,
		A.m[2][0]*v.x + A.m[2][1]*v.y + A.m[2][2]*v.z + A.m[2][3]*v.w,
		A.m[3][0]*v.x + A.m[3][1]*v.y + A.m[3][2]*v.z + A.m[3][3]*v.w);
}

Vector4F operator*(Vector4F & v, Matrix4x4F & A)
{
	return Vector4F(
		v.x*A.m[0][0] + v.y*A.m[1][0] + v.z*A.m[2][0] + v.w*A.m[3][0],
		v.x*A.m[0][1] + v.y*A.m[1][1] + v.z*A.m[2][1] + v.w*A.m[3][1],
		v.x*A.m[0][2] + v.y*A.m[1][2] + v.z*A.m[2][2] + v.w*A.m[3][2],
		v.x*A.m[0][3] + v.y*A.m[1][3] + v.z*A.m[2][3] + v.w*A.m[3][3]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////     VectorNF    ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorNF::CreateVector(DWORD nElements)
{
	Assert(!c, "VectorNF::CreateVector must destroy the vector before creating a new one.");
	
	c = new FLOAT[nElements];
	m_nSize = nElements;
}

FLOAT VectorNF::Length() 
{
	double d = 0;
	for (DWORD i=0; i<m_nSize; i++)
		d += c[i] * c[i];
	return (float)sqrt(d);
}

FLOAT VectorNF::LengthSq() 
{
	double d = 0;
	for (DWORD i=0; i<m_nSize; i++)
		d += c[i] * c[i];
	return (float)d;
}

void VectorNF::DestroyVector()
{
	Assert(c, "VectorNF::DestroyVector cannot destroy a vector that has not been created.");
	
	delete[] c;
	c = NULL;
	m_nSize = 0;
}


};



