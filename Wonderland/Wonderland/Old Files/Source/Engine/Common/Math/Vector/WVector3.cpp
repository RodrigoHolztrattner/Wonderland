///////////////////////////////////////////////////////////////////////////////
// Filename: WVector3.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WVector3.h"
#include "WVector2.h"
#include "WVector4.h"

WVector3::WVector3()
{
}

WVector3::WVector3(float _x, float _y, float _z)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
}

WVector3::WVector3(WVector2 _vector2)
{
	v[0] = _vector2.v[0];
	v[1] = _vector2.v[1];
	v[2] = 0;
}

WVector3::WVector3(WVector4 _vector4)
{
	v[0] = _vector4.v[0];
	v[1] = _vector4.v[1];
	v[2] = _vector4.v[2];
}

WVector3::WVector3(const WVector3& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
}

WVector3::~WVector3()
{

}