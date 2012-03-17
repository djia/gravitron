
#ifndef DXUTVECTOR_H
#define DXUTVECTOR_H

#include <d3dx10.h>
#include "DxUtError.h"

namespace PhysUt {

#define DotXY(a, b)    ((a.x*b.x + a.y*b.y))
#define DotXYZ(a, b)   ((a.x*b.x + a.y*b.y + a.z*b.z))
#define CrossXY(a, b)  ((a.x*b.y - b.x*a.y))
#define CrossXYZ(a, b) (Vector3F(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x))

class Vector2F {
public:
	union {
		struct {
			float x;
			float y;
		};
		float c[2];
	};
public:
	Vector2F() {}
	Vector2F(float _x, float _y):x(_x), y(_y) {}
	//Vector2F(float * _c) {memcpy(c, _c, sizeof(float)*2);}
	//~Vector2F() {}

	Vector2F operator+() {return *this;}
	Vector2F operator-() {return Vector2F(-x, -y);}

	Vector2F operator+(Vector2F & v) {return Vector2F(x+v.x, y+v.y);}
	Vector2F operator-(Vector2F & v) {return Vector2F(x-v.x, y-v.y);}
	friend Vector2F operator*(FLOAT flt, Vector2F & v) {return Vector2F(v.x*flt, v.y*flt);}
	//Vector2F operator*(FLOAT flt) {return Vector2F(x*flt, y*flt);}
	Vector2F operator*(Vector2F & v) {return Vector2F(x*v.x, y*v.y);}
	Vector2F operator/(FLOAT flt) {float d = 1.f/flt; return Vector2F(x*d, y*d);}

	Vector2F & operator=(Vector2F & v) {x = v.x, y = v.y; return *this;}
	Vector2F & operator+=(Vector2F & v) {x += v.x, y += v.y; return *this;}
	Vector2F & operator-=(Vector2F & v) {x -= v.x, y -= v.y; return *this;}
	Vector2F & operator*=(FLOAT flt) {x *= flt, y *= flt; return *this;}
	Vector2F & operator/=(FLOAT flt) {float d = 1.f/flt; x *= d, y *= d; return *this;}

	//void operator()(float _x, float _y, float _z) {x = _x, y = _y;}
	//void operator()(float * _c) {memcpy(c, _c, sizeof(float)*2);}

	FLOAT Length() {return sqrtf(x*x + y*y);}
	FLOAT LengthSq() {return x*x + y*y;}
	Vector2F Normalize();
};

class Matrix4x4F;

class Vector3F {
public:
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float c[3];
	};
public:
	Vector3F() {}
	//Vector3F(Vector3F & copy) {memcpy(c, copy.c, sizeof(float)*3);}
	Vector3F(float _x, float _y, float _z):x(_x), y(_y), z(_z) {}
	//Vector3F(float * _c) {memcpy(c, _c, sizeof(float)*3);}
	//~Vector3F() {}

	Vector3F operator+() {return *this;}
	Vector3F operator-() {return Vector3F(-x, -y, -z);}

	Vector3F operator+(Vector3F & v) {return Vector3F(x+v.x, y+v.y, z+v.z);}
	Vector3F operator-(Vector3F & v) {return Vector3F(x-v.x, y-v.y, z-v.z);}
	friend Vector3F operator*(FLOAT flt, Vector3F & v) {return Vector3F(v.x*flt, v.y*flt, v.z*flt);}
	//Vector3F operator*(FLOAT flt) {return Vector3F(x*flt, y*flt, z*flt);}
	Vector3F operator*(Vector3F & v) {return Vector3F(x*v.x, y*v.y, z*v.z);}
	Vector3F operator/(FLOAT flt) {float d = 1.f/flt; return Vector3F(x*d, y*d, z*d);}

	Vector3F & operator=(Vector3F & v) {x = v.x, y = v.y, z = v.z; return *this;}
	Vector3F & operator+=(Vector3F & v) {x += v.x, y += v.y, z += v.z; return *this;}
	Vector3F & operator-=(Vector3F & v) {x -= v.x, y -= v.y, z -= v.z; return *this;}
	Vector3F & operator*=(FLOAT flt) {x *= flt, y *= flt, z *= flt; return *this;}
	Vector3F & operator/=(FLOAT flt) {float d = 1.f/flt; x *= d, y *= d, z *= d; return *this;}

	//void operator()(float _x, float _y, float _z) {x = _x, y = _y, z = _z;}
	//void operator()(float * _c) {memcpy(c, _c, sizeof(float)*3);}

	//v1^v2 should always be enclosed in parentheses (v1^v2)
	//Vector3F operator^(Vector3F & v) {return Vector3F(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);}
	FLOAT Length() {return sqrtf(x*x + y*y + z*z);}
	FLOAT LengthSq() {return x*x + y*y + z*z;}

	Vector3F Normalize();
	Vector3F NormalizeSq();
	Matrix4x4F SkewMatrix3x3F();
	friend Vector3F operator*(Matrix4x4F & A, Vector3F & v);
	friend Vector3F operator*(Vector3F & v, Matrix4x4F & A);
};

class Vector4F {
public:
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float c[4];
	};
public:
	Vector4F() {}
	//Vector4F(Vector4F & copy) {memcpy(c, copy.c, sizeof(float)*4);}
	Vector4F(float _x, float _y, float _z, float _w):x(_x), y(_y), z(_z), w(_w) {}
	//Vector4F(float * _c) {memcpy(c, _c, sizeof(float)*4);}
	//~Vector4F() {}

	Vector4F operator+() {return *this;}
	Vector4F operator-() {return Vector4F(-x, -y, -z, -w);}

	Vector4F operator+(Vector4F & v) {return Vector4F(x+v.x, y+v.y, z+v.z, w+v.w);}
	Vector4F operator-(Vector4F & v) {return Vector4F(x-v.x, y-v.y, z-v.z, w-v.w);}
	friend Vector4F operator*(FLOAT flt, Vector4F & v) {return Vector4F(v.x*flt, v.y*flt, v.z*flt, v.w*flt);}
	//Vector4F operator*(FLOAT flt) {return Vector4F(x*flt, y*flt, z*flt, w*flt);}
	Vector4F operator*(Vector4F & v) {return Vector4F(x*v.x, y*v.y, z*v.z, w*v.w);}
	Vector4F operator/(FLOAT flt) {float d = 1.f/flt; return Vector4F(x*d, y*d, z*d, w*d);}

	Vector4F & operator=(Vector4F & v) {x = v.x, y = v.y, z = v.z, w = v.w; return *this;}
	Vector4F & operator+=(Vector4F & v) {x += v.x, y += v.y, z += v.z, w += v.w; return *this;}
	Vector4F & operator-=(Vector4F & v) {x -= v.x, y -= v.y, z -= v.z, w -= v.w; return *this;}
	Vector4F & operator*=(FLOAT flt) {x *= flt, y *= flt, z *= flt, w *= flt; return *this;}
	Vector4F & operator/=(FLOAT flt) {float d = 1.f/flt; x *= d, y *= d, z *= d, w *= d; return *this;}

	//void operator()(float _x, float _y, float _z, float _w) {x = _x, y = _y, z = _z, w = _w;}
	//void operator()(float * _c) {memcpy(c, _c, sizeof(float)*4);}

	FLOAT Length() {return sqrtf(x*x + y*y + z*z + w*w);}
	FLOAT LengthSq() {return x*x + y*y + z*z + w*w;}

	Vector4F Normalize();
	friend Vector4F operator*(Matrix4x4F & A, Vector4F & v);
	friend Vector4F operator*(Vector4F & v, Matrix4x4F & A);
};

class VectorNF {
public:
	FLOAT * c;
private:
	DWORD m_nSize;
public:
	VectorNF():c(0), m_nSize(0) {}
	//~VectorNF() {}

	void CreateVector(DWORD nElements);
	DWORD Size() {return m_nSize; }

	VectorNF & operator=(VectorNF & v);
	VectorNF & operator+=(VectorNF & v);
	VectorNF & operator-=(VectorNF & v);
	friend VectorNF & operator*=(VectorNF & v, FLOAT flt);
	VectorNF & operator/=(FLOAT flt);

	FLOAT Length();
	FLOAT LengthSq();

	void DestroyVector();
};

inline VectorNF & VectorNF::operator=(VectorNF & v) 
{
	Assert(m_nSize == v.m_nSize, "VectorNF::operator= can not have vectors of different sizes.");

	memcpy(this->c, v.c, sizeof(FLOAT)*m_nSize);
	return *this;
}

inline VectorNF & VectorNF::operator+=(VectorNF & v) 
{
	Assert(m_nSize == v.m_nSize, "VectorNF::operator+= can not add vectors of different sizes.");

	for (DWORD i=0; i<m_nSize; i++)
		c[i] += v.c[i];
	return *this;
}

inline VectorNF & VectorNF::operator-=(VectorNF & v) 
{
	Assert(m_nSize == v.m_nSize, "VectorNF::operator-= can not subtract vectors of different sizes.");

	for (DWORD i=0; i<m_nSize; i++)
		c[i] -= v.c[i];
	return *this;
}

inline VectorNF & operator*=(VectorNF & v, FLOAT flt)
{
	FLOAT * c = v.c;
	for (DWORD i=0, vSize = v.m_nSize; i<vSize; i++)
		c[i] *= flt;
	return v;
}

inline VectorNF & VectorNF::operator/=(FLOAT flt) 
{
	FLOAT mul = 1.f/flt;
	for (DWORD i=0; i<m_nSize; i++)
		c[i] *= mul;
	return *this;
}


};


#endif
