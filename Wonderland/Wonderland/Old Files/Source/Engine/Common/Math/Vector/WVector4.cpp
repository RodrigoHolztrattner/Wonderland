///////////////////////////////////////////////////////////////////////////////
// Filename: WVector4.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WVector4.h"

WVector4::WVector4()
{
}

WVector4::WVector4(float _x, float _y, float _z, float _w)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
	v[3] = _w;
}

WVector4::WVector4(const WVector4& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];
}

WVector4::~WVector4()
{
}
