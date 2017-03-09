///////////////////////////////////////////////////////////////////////////////
// Filename: Vector3.cpp
///////////////////////////////////////////////////////////////////////////////
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
}

Vector3::Vector3(Vector2 _vector2)
{
	v[0] = _vector2.v[0];
	v[1] = _vector2.v[1];
	v[2] = 0;
}

Vector3::Vector3(Vector4 _vector4)
{
	v[0] = _vector4.v[0];
	v[1] = _vector4.v[1];
	v[2] = _vector4.v[2];
}

Vector3::Vector3(const Vector3& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
}

Vector3::~Vector3()
{

}

Vector3 Vector3::TransformToScreenPosition(Vector3 _position, Vector3 _size)
{
	// Invert the y space
	_position.y = (1.0f - _size.y) - _position.y;

	// Transform to screen coordinates
	_position.x *= 2.0f;
	_position.x -= 1;
	_position.y *= 2.0f;
	_position.y -= 1;

	return _position;
}

Vector3 Vector3::TransformToScreenSize(Vector3 _size)
{
	// Transform to screen size
	_size.x *= 2.0f;
	_size.y *= 2.0f;

	return _size;
}