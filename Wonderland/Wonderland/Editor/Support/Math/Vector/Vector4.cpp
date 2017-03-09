///////////////////////////////////////////////////////////////////////////////
// Filename: Vector4.cpp
///////////////////////////////////////////////////////////////////////////////
#include "Vector4.h"
#include "Vector2.h"

Vector4::Vector4()
{
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
	v[3] = _w;
}

Vector4::Vector4(Vector2 _vectorA, Vector2 _vectorB)
{
	v[0] = _vectorA.x;
	v[1] = _vectorA.y;
	v[2] = _vectorB.x;
	v[3] = _vectorB.y;
}

Vector4::Vector4(const Vector4& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];
}

Vector4::~Vector4()
{
}
