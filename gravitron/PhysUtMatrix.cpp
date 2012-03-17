
#include "PhysUtMatrix.h"
#include "PhysUtVector.h"

namespace PhysUt {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////   Matrix4x4F    ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix4x4F Matrix4x4F::operator+(Matrix4x4F & A)
{
	return Matrix4x4F(
		m[0][0] + A.m[0][0], m[1][0] + A.m[1][0], m[2][0] + A.m[2][0], m[3][0] + A.m[3][0],
		m[0][1] + A.m[0][1], m[1][1] + A.m[1][1], m[2][1] + A.m[2][1], m[3][1] + A.m[3][1],
		m[0][2] + A.m[0][2], m[1][2] + A.m[1][2], m[2][2] + A.m[2][2], m[3][2] + A.m[3][2],
		m[0][3] + A.m[0][3], m[1][3] + A.m[1][3], m[2][3] + A.m[2][3], m[3][3] + A.m[3][3]);
}

Matrix4x4F Matrix4x4F::operator-(Matrix4x4F & A)
{
	return Matrix4x4F(
		m[0][0] - A.m[0][0], m[1][0] - A.m[1][0], m[2][0] - A.m[2][0], m[3][0] - A.m[3][0],
		m[0][1] - A.m[0][1], m[1][1] - A.m[1][1], m[2][1] - A.m[2][1], m[3][1] - A.m[3][1],
		m[0][2] - A.m[0][2], m[1][2] - A.m[1][2], m[2][2] - A.m[2][2], m[3][2] - A.m[3][2],
		m[0][3] - A.m[0][3], m[1][3] - A.m[1][3], m[2][3] - A.m[2][3], m[3][3] - A.m[3][3]);
}

Matrix4x4F Matrix4x4F::operator*(Matrix4x4F & A)
{
	return Matrix4x4F(
		m[0][0] * A.m[0][0] + m[0][1] * A.m[1][0] + m[0][2] * A.m[2][0] + m[0][3] * A.m[3][0],
		m[1][0] * A.m[0][0] + m[1][1] * A.m[1][0] + m[1][2] * A.m[2][0] + m[1][3] * A.m[3][0],
		m[2][0] * A.m[0][0] + m[2][1] * A.m[1][0] + m[2][2] * A.m[2][0] + m[2][3] * A.m[3][0],
		m[3][0] * A.m[0][0] + m[3][1] * A.m[1][0] + m[3][2] * A.m[2][0] + m[3][3] * A.m[3][0],

		m[0][0] * A.m[0][1] + m[0][1] * A.m[1][1] + m[0][2] * A.m[2][1] + m[0][3] * A.m[3][1],
		m[1][0] * A.m[0][1] + m[1][1] * A.m[1][1] + m[1][2] * A.m[2][1] + m[1][3] * A.m[3][1],
		m[2][0] * A.m[0][1] + m[2][1] * A.m[1][1] + m[2][2] * A.m[2][1] + m[2][3] * A.m[3][1],
		m[3][0] * A.m[0][1] + m[3][1] * A.m[1][1] + m[3][2] * A.m[2][1] + m[3][3] * A.m[3][1],

		m[0][0] * A.m[0][2] + m[0][1] * A.m[1][2] + m[0][2] * A.m[2][2] + m[0][3] * A.m[3][2],
		m[1][0] * A.m[0][2] + m[1][1] * A.m[1][2] + m[1][2] * A.m[2][2] + m[1][3] * A.m[3][2],
		m[2][0] * A.m[0][2] + m[2][1] * A.m[1][2] + m[2][2] * A.m[2][2] + m[2][3] * A.m[3][2],
		m[3][0] * A.m[0][2] + m[3][1] * A.m[1][2] + m[3][2] * A.m[2][2] + m[3][3] * A.m[3][2],

		m[0][0] * A.m[0][3] + m[0][1] * A.m[1][3] + m[0][2] * A.m[2][3] + m[0][3] * A.m[3][3],
		m[1][0] * A.m[0][3] + m[1][1] * A.m[1][3] + m[1][2] * A.m[2][3] + m[1][3] * A.m[3][3],
		m[2][0] * A.m[0][3] + m[2][1] * A.m[1][3] + m[2][2] * A.m[2][3] + m[2][3] * A.m[3][3],
		m[3][0] * A.m[0][3] + m[3][1] * A.m[1][3] + m[3][2] * A.m[2][3] + m[3][3] * A.m[3][3]);
}

Matrix4x4F operator*(FLOAT flt, Matrix4x4F & A)
{
	return Matrix4x4F(
		A.m[0][0] * flt, A.m[1][0] * flt, A.m[2][0] * flt, A.m[3][0] * flt,
		A.m[0][1] * flt, A.m[1][1] * flt, A.m[2][1] * flt, A.m[3][1] * flt,
		A.m[0][2] * flt, A.m[1][2] * flt, A.m[2][2] * flt, A.m[3][2] * flt,
		A.m[0][3] * flt, A.m[1][3] * flt, A.m[2][3] * flt, A.m[3][3] * flt);
}

Matrix4x4F Matrix4x4F::operator*(FLOAT flt)
{
	return Matrix4x4F(
		m[0][0] * flt, m[1][0] * flt, m[2][0] * flt, m[3][0] * flt,
		m[0][1] * flt, m[1][1] * flt, m[2][1] * flt, m[3][1] * flt,
		m[0][2] * flt, m[1][2] * flt, m[2][2] * flt, m[3][2] * flt,
		m[0][3] * flt, m[1][3] * flt, m[2][3] * flt, m[3][3] * flt);
}

Matrix4x4F & Matrix4x4F::operator+=(Matrix4x4F & A)
{
	m[0][0] += A.m[0][0], m[1][0] += A.m[1][0], m[2][0] += A.m[2][0], m[3][0] += A.m[3][0];
	m[0][1] += A.m[0][1], m[1][1] += A.m[1][1], m[2][1] += A.m[2][1], m[3][1] += A.m[3][1];
	m[0][2] += A.m[0][2], m[1][2] += A.m[1][2], m[2][2] += A.m[2][2], m[3][2] += A.m[3][2];
	m[0][3] += A.m[0][3], m[1][3] += A.m[1][3], m[2][3] += A.m[2][3], m[3][3] += A.m[3][3];
	return *this;
}

Matrix4x4F & Matrix4x4F::operator-=(Matrix4x4F & A)
{
	m[0][0] -= A.m[0][0], m[1][0] -= A.m[1][0], m[2][0] -= A.m[2][0], m[3][0] -= A.m[3][0];
	m[0][1] -= A.m[0][1], m[1][1] -= A.m[1][1], m[2][1] -= A.m[2][1], m[3][1] -= A.m[3][1];
	m[0][2] -= A.m[0][2], m[1][2] -= A.m[1][2], m[2][2] -= A.m[2][2], m[3][2] -= A.m[3][2];
	m[0][3] -= A.m[0][3], m[1][3] -= A.m[1][3], m[2][3] -= A.m[2][3], m[3][3] -= A.m[3][3];
	return *this;
}

Matrix4x4F & Matrix4x4F::operator*=(Matrix4x4F & A)
{
	Matrix4x4F B(*this);
	m[0][0] = B.m[0][0] * A.m[0][0] + B.m[0][1] * A.m[1][0] + B.m[0][2] * A.m[2][0] + B.m[0][3] * A.m[3][0];
	m[1][0] = B.m[1][0] * A.m[0][0] + B.m[1][1] * A.m[1][0] + B.m[1][2] * A.m[2][0] + B.m[1][3] * A.m[3][0];
	m[2][0] = B.m[2][0] * A.m[0][0] + B.m[2][1] * A.m[1][0] + B.m[2][2] * A.m[2][0] + B.m[2][3] * A.m[3][0];
	m[3][0] = B.m[3][0] * A.m[0][0] + B.m[3][1] * A.m[1][0] + B.m[3][2] * A.m[2][0] + B.m[3][3] * A.m[3][0];

	m[0][1] = B.m[0][0] * A.m[0][1] + B.m[0][1] * A.m[1][1] + B.m[0][2] * A.m[2][1] + B.m[0][3] * A.m[3][1];
	m[1][1] = B.m[1][0] * A.m[0][1] + B.m[1][1] * A.m[1][1] + B.m[1][2] * A.m[2][1] + B.m[1][3] * A.m[3][1];
	m[2][1] = B.m[2][0] * A.m[0][1] + B.m[2][1] * A.m[1][1] + B.m[2][2] * A.m[2][1] + B.m[2][3] * A.m[3][1];
	m[3][1] = B.m[3][0] * A.m[0][1] + B.m[3][1] * A.m[1][1] + B.m[3][2] * A.m[2][1] + B.m[3][3] * A.m[3][1];

	m[0][2] = B.m[0][0] * A.m[0][2] + B.m[0][1] * A.m[1][2] + B.m[0][2] * A.m[2][2] + B.m[0][3] * A.m[3][2];
	m[1][2] = B.m[1][0] * A.m[0][2] + B.m[1][1] * A.m[1][2] + B.m[1][2] * A.m[2][2] + B.m[1][3] * A.m[3][2];
	m[2][2] = B.m[2][0] * A.m[0][2] + B.m[2][1] * A.m[1][2] + B.m[2][2] * A.m[2][2] + B.m[2][3] * A.m[3][2];
	m[3][2] = B.m[3][0] * A.m[0][2] + B.m[3][1] * A.m[1][2] + B.m[3][2] * A.m[2][2] + B.m[3][3] * A.m[3][2];

	m[0][3] = B.m[0][0] * A.m[0][3] + B.m[0][1] * A.m[1][3] + B.m[0][2] * A.m[2][3] + B.m[0][3] * A.m[3][3];
	m[1][3] = B.m[1][0] * A.m[0][3] + B.m[1][1] * A.m[1][3] + B.m[1][2] * A.m[2][3] + B.m[1][3] * A.m[3][3];
	m[2][3] = B.m[2][0] * A.m[0][3] + B.m[2][1] * A.m[1][3] + B.m[2][2] * A.m[2][3] + B.m[2][3] * A.m[3][3];
	m[3][3] = B.m[3][0] * A.m[0][3] + B.m[3][1] * A.m[1][3] + B.m[3][2] * A.m[2][3] + B.m[3][3] * A.m[3][3];
	return *this;
}

Matrix4x4F & Matrix4x4F::operator*=(FLOAT flt)
{
	m[0][0] *= flt, m[1][0] *= flt, m[2][0] *= flt, m[3][0] *= flt;
	m[0][1] *= flt, m[1][1] *= flt, m[2][1] *= flt, m[3][1] *= flt;
	m[0][2] *= flt, m[1][2] *= flt, m[2][2] *= flt, m[3][2] *= flt;
	m[0][3] *= flt, m[1][3] *= flt, m[2][3] *= flt, m[3][3] *= flt;
	return *this;
}

Matrix4x4F Matrix4x4F::Inverse()
{
	Matrix4x4F A;
	float a00 = m[0][0]; float a01 = m[0][1]; float a02 = m[0][2]; float a03 = m[0][3];
	float a10 = m[1][0]; float a11 = m[1][1]; float a12 = m[1][2]; float a13 = m[1][3];
	float a20 = m[2][0]; float a21 = m[2][1]; float a22 = m[2][2]; float a23 = m[2][3];
	float a30 = m[3][0]; float a31 = m[3][1]; float a32 = m[3][2]; float a33 = m[3][3];

	A.m[0][0] =      a11*a22*a33 - a11*a23*a32 - a21*a12*a33 + a21*a13*a32 + a31*a12*a23 - a31*a13*a22;
	A.m[0][1] =    - a01*a22*a33 + a01*a23*a32 + a21*a02*a33 - a21*a03*a32 - a31*a02*a23 + a31*a03*a22;
	A.m[0][2] =      a01*a12*a33 - a01*a13*a32 - a11*a02*a33 + a11*a03*a32 + a31*a02*a13 - a31*a03*a12;
	A.m[0][3] =    - a01*a12*a23 + a01*a13*a22 + a11*a02*a23 - a11*a03*a22 - a21*a02*a13 + a21*a03*a12;
	A.m[1][0] =    - a10*a22*a33 + a10*a23*a32 + a20*a12*a33 - a20*a13*a32 - a30*a12*a23 + a30*a13*a22;
	A.m[1][1] =      a00*a22*a33 - a00*a23*a32 - a20*a02*a33 + a20*a03*a32 + a30*a02*a23 - a30*a03*a22;
	A.m[1][2] =    - a00*a12*a33 + a00*a13*a32 + a10*a02*a33 - a10*a03*a32 - a30*a02*a13 + a30*a03*a12;
	A.m[1][3] =      a00*a12*a23 - a00*a13*a22 - a10*a02*a23 + a10*a03*a22 + a20*a02*a13 - a20*a03*a12;
	A.m[2][0] =      a10*a21*a33 - a10*a23*a31 - a20*a11*a33 + a20*a13*a31 + a30*a11*a23 - a30*a13*a21;
	A.m[2][1] =    - a00*a21*a33 + a00*a23*a31 + a20*a01*a33 - a20*a03*a31 - a30*a01*a23 + a30*a03*a21;
	A.m[2][2] =      a00*a11*a33 - a00*a13*a31 - a10*a01*a33 + a10*a03*a31 + a30*a01*a13 - a30*a03*a11;
	A.m[2][3] =    - a00*a11*a23 + a00*a13*a21 + a10*a01*a23 - a10*a03*a21 - a20*a01*a13 + a20*a03*a11;
	A.m[3][0] =    - a10*a21*a32 + a10*a22*a31 + a20*a11*a32 - a20*a12*a31 - a30*a11*a22 + a30*a12*a21;
	A.m[3][1] =      a00*a21*a32 - a00*a22*a31 - a20*a01*a32 + a20*a02*a31 + a30*a01*a22 - a30*a02*a21;
	A.m[3][2] =    - a00*a11*a32 + a00*a12*a31 + a10*a01*a32 - a10*a02*a31 - a30*a01*a12 + a30*a02*a11;
	A.m[3][3] =      a00*a11*a22 - a00*a12*a21 - a10*a01*a22 + a10*a02*a21 + a20*a01*a12 - a20*a02*a11;

	float d = a00*A.m[0][0] + a10*A.m[0][1] +  a20*A.m[0][2] + a30*A.m[0][3];
	if (!d) d += 1e-8f;

	float div = 1.f/d;
	A.m[0][0] *= div; A.m[0][1] *= div; A.m[0][2] *= div; A.m[0][3] *= div;
	A.m[1][0] *= div; A.m[1][1] *= div; A.m[1][2] *= div; A.m[1][3] *= div;
	A.m[2][0] *= div; A.m[2][1] *= div; A.m[2][2] *= div; A.m[2][3] *= div;
	A.m[3][0] *= div; A.m[3][1] *= div; A.m[3][2] *= div; A.m[3][3] *= div;
	return A;

}

Matrix4x4F Matrix4x4F::Transpose()
{
	return Matrix4x4F(
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3]);
}

Matrix4x4F Matrix4x4F::InverseTranspose()
{
	Matrix4x4F A(Inverse());

	float t = 0;
	t = A.m[0][1]; A.m[0][1] = A.m[1][0]; A.m[1][0] = t;
	t = A.m[0][2]; A.m[0][2] = A.m[2][0]; A.m[2][0] = t;
	t = A.m[0][3]; A.m[0][3] = A.m[3][0]; A.m[3][0] = t;
	t = A.m[1][2]; A.m[1][2] = A.m[2][1]; A.m[2][1] = t;
	t = A.m[1][3]; A.m[1][3] = A.m[3][1]; A.m[3][1] = t;
	t = A.m[2][3]; A.m[2][3] = A.m[3][2]; A.m[3][2] = t;
	return A;
}

Matrix4x4F & Matrix4x4F::MInverse()
{
	float a00 = m[0][0]; float a01 = m[0][1]; float a02 = m[0][2]; float a03 = m[0][3];
	float a10 = m[1][0]; float a11 = m[1][1]; float a12 = m[1][2]; float a13 = m[1][3];
	float a20 = m[2][0]; float a21 = m[2][1]; float a22 = m[2][2]; float a23 = m[2][3];
	float a30 = m[3][0]; float a31 = m[3][1]; float a32 = m[3][2]; float a33 = m[3][3];

	m[0][0] =      a11*a22*a33 - a11*a23*a32 - a21*a12*a33 + a21*a13*a32 + a31*a12*a23 - a31*a13*a22;
	m[0][1] =    - a01*a22*a33 + a01*a23*a32 + a21*a02*a33 - a21*a03*a32 - a31*a02*a23 + a31*a03*a22;
	m[0][2] =      a01*a12*a33 - a01*a13*a32 - a11*a02*a33 + a11*a03*a32 + a31*a02*a13 - a31*a03*a12;
	m[0][3] =    - a01*a12*a23 + a01*a13*a22 + a11*a02*a23 - a11*a03*a22 - a21*a02*a13 + a21*a03*a12;
	m[1][0] =    - a10*a22*a33 + a10*a23*a32 + a20*a12*a33 - a20*a13*a32 - a30*a12*a23 + a30*a13*a22;
	m[1][1] =      a00*a22*a33 - a00*a23*a32 - a20*a02*a33 + a20*a03*a32 + a30*a02*a23 - a30*a03*a22;
	m[1][2] =    - a00*a12*a33 + a00*a13*a32 + a10*a02*a33 - a10*a03*a32 - a30*a02*a13 + a30*a03*a12;
	m[1][3] =      a00*a12*a23 - a00*a13*a22 - a10*a02*a23 + a10*a03*a22 + a20*a02*a13 - a20*a03*a12;
	m[2][0] =      a10*a21*a33 - a10*a23*a31 - a20*a11*a33 + a20*a13*a31 + a30*a11*a23 - a30*a13*a21;
	m[2][1] =    - a00*a21*a33 + a00*a23*a31 + a20*a01*a33 - a20*a03*a31 - a30*a01*a23 + a30*a03*a21;
	m[2][2] =      a00*a11*a33 - a00*a13*a31 - a10*a01*a33 + a10*a03*a31 + a30*a01*a13 - a30*a03*a11;
	m[2][3] =    - a00*a11*a23 + a00*a13*a21 + a10*a01*a23 - a10*a03*a21 - a20*a01*a13 + a20*a03*a11;
	m[3][0] =    - a10*a21*a32 + a10*a22*a31 + a20*a11*a32 - a20*a12*a31 - a30*a11*a22 + a30*a12*a21;
	m[3][1] =      a00*a21*a32 - a00*a22*a31 - a20*a01*a32 + a20*a02*a31 + a30*a01*a22 - a30*a02*a21;
	m[3][2] =    - a00*a11*a32 + a00*a12*a31 + a10*a01*a32 - a10*a02*a31 - a30*a01*a12 + a30*a02*a11;
	m[3][3] =      a00*a11*a22 - a00*a12*a21 - a10*a01*a22 + a10*a02*a21 + a20*a01*a12 - a20*a02*a11;

	float d = a00*m[0][0] + a10*m[0][1] +  a20*m[0][2] + a30*m[0][3];
	if (!d) d += 1e-8f;

	float div = 1.f/d;
	m[0][0] *= div; m[0][1] *= div; m[0][2] *= div; m[0][3] *= div;
	m[1][0] *= div; m[1][1] *= div; m[1][2] *= div; m[1][3] *= div;
	m[2][0] *= div; m[2][1] *= div; m[2][2] *= div; m[2][3] *= div;
	m[3][0] *= div; m[3][1] *= div; m[3][2] *= div; m[3][3] *= div;
	return *this;
}

Matrix4x4F & Matrix4x4F::MTranspose()
{
	float t = 0;
	t = m[0][1]; m[0][1] = m[1][0]; m[1][0] = t;
	t = m[0][2]; m[0][2] = m[2][0]; m[2][0] = t;
	t = m[0][3]; m[0][3] = m[3][0]; m[3][0] = t;
	t = m[1][2]; m[1][2] = m[2][1]; m[2][1] = t;
	t = m[1][3]; m[1][3] = m[3][1]; m[3][1] = t;
	t = m[2][3]; m[2][3] = m[3][2]; m[3][2] = t;
	return *this;
}

Matrix4x4F & Matrix4x4F::MInverseTranspose()
{
	MInverse();

	float t = 0;
	t = m[0][1]; m[0][1] = m[1][0]; m[1][0] = t;
	t = m[0][2]; m[0][2] = m[2][0]; m[2][0] = t;
	t = m[0][3]; m[0][3] = m[3][0]; m[3][0] = t;
	t = m[1][2]; m[1][2] = m[2][1]; m[2][1] = t;
	t = m[1][3]; m[1][3] = m[3][1]; m[3][1] = t;
	t = m[2][3]; m[2][3] = m[3][2]; m[3][2] = t;
	return *this;
}

Matrix4x4F & Matrix4x4F::MScaling(Vector3F & scl)
{
	m[0][0] = scl.x, m[1][0] = 0,	  m[2][0] = 0,		m[3][0] = 0;
	m[0][1] = 0,	 m[1][1] = scl.y, m[2][1] = 0,		m[3][1] = 0;
	m[0][2] = 0,	 m[1][2] = 0,	  m[2][2] = scl.z,	m[3][2] = 0;
	m[0][3] = 0,	 m[1][3] = 0,	  m[2][3] = 0,		m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MScaling(float x, float y, float z)
{
	m[0][0] = x,	m[1][0] = 0,	m[2][0] = 0,	m[3][0] = 0;
	m[0][1] = 0,	m[1][1] = y,	m[2][1] = 0,	m[3][1] = 0;
	m[0][2] = 0,	m[1][2] = 0,	m[2][2] = z,	m[3][2] = 0;
	m[0][3] = 0,	m[1][3] = 0,	m[2][3] = 0,	m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MTranslation(Vector3F trans)
{
	m[0][0] = 1,		m[1][0] = 0,		m[2][0] = 0,		m[3][0] = 0;
	m[0][1] = 0,		m[1][1] = 1,		m[2][1] = 0,		m[3][1] = 0;
	m[0][2] = 0,		m[1][2] = 0,		m[2][2] = 1,		m[3][2] = 0;
	m[0][3] = trans.x,	m[1][3] = trans.y,	m[2][3] = trans.z,	m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MTranslation(float x, float y, float z)
{
	m[0][0] = 1,	m[1][0] = 0,	m[2][0] = 0,	m[3][0] = 0;
	m[0][1] = 0,	m[1][1] = 1,	m[2][1] = 0,	m[3][1] = 0;
	m[0][2] = 0,	m[1][2] = 0,	m[2][2] = 1,	m[3][2] = 0;
	m[0][3] = x,	m[1][3] = y,	m[2][3] = z,	m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MRotationXLH(float fTheta)
{ 
	m[0][0] = 1,	m[1][0] = 0,			m[2][0] = 0,			m[3][0] = 0;
	m[0][1] = 0,	m[1][1] = cosf(fTheta),	m[2][1] = sinf(fTheta),	m[3][1] = 0;
	m[0][2] = 0,	m[1][2] = -sinf(fTheta),	m[2][2] = cosf(fTheta),	m[3][2] = 0;
	m[0][3] = 0,	m[1][3] = 0,			m[2][3] = 0,			m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MRotationYLH(float fTheta)
{
	m[0][0] = cosf(fTheta),	m[1][0] = 0,	m[2][0] = -sinf(fTheta),	m[3][0] = 0;
	m[0][1] = 0,			m[1][1] = 1,	m[2][1] = 0,			m[3][1] = 0;
	m[0][2] = sinf(fTheta),	m[1][2] = 0,	m[2][2] = cosf(fTheta),	m[3][2] = 0;
	m[0][3] = 0,			m[1][3] = 0,	m[2][3] = 0,			m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MRotationZLH(float fTheta)
{
	m[0][0] = cosf(fTheta),	m[1][0] = sinf(fTheta),	m[2][0] = 0,	m[3][0] = 0;
	m[0][1] = -sinf(fTheta),	m[1][1] = cosf(fTheta),	m[2][1] = 0,	m[3][1] = 0;
	m[0][2] = 0,			m[1][2] = 0,			m[2][2] = 1,	m[3][2] = 0;
	m[0][3] = 0,			m[1][3] = 0,			m[2][3] = 0,	m[3][3] = 1;
	return *this;
}

Matrix4x4F & Matrix4x4F::MRotationAxisLH(Vector3F & v, float fTheta)
{
	Vector3F vn = v.Normalize();
	float c = cosf(fTheta);
	float s = sinf(fTheta);
	float t = 1.f - cosf(fTheta);

	m[0][0] = t*vn.x*vn.x + c,		m[1][0] = t*vn.x*vn.y - s*vn.z,	m[2][0] = t*vn.x*vn.z + s*vn.y,	m[3][0] = 0;
	m[0][1] = t*vn.x*vn.y + s*vn.z, m[1][1] = t*vn.y*vn.y + c,		m[2][1] = t*vn.y*vn.z - s*vn.x,	m[3][1] = 0;
	m[0][2] = t*vn.x*vn.z - s*vn.y,	m[1][2] = t*vn.y*vn.z + s*vn.x,	m[2][2] = t*vn.z*vn.z + c,		m[3][2] = 0;
	m[0][3] = 0,					m[1][3] = 0,					m[2][3] = 0,					m[3][3] = 1;
	return *this;
}


};
