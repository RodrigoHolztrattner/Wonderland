///////////////////////////////////////////////////////////////////////////////
// Filename: Vector2.cpp
///////////////////////////////////////////////////////////////////////////////
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>       /* sin / cos */

Vector2::Vector2()
{
}

Vector2::Vector2(float _x, float _y)
{
	v[0] = _x;
	v[1] = _y;
}

Vector2::Vector2(Vector3 _vector3)
{
	v[0] = _vector3.v[0];
	v[1] = _vector3.v[1];
}

Vector2::Vector2(Vector4 _vector4)
{
	v[0] = _vector4.v[0];
	v[1] = _vector4.v[1];
}

Vector2::Vector2(const Vector2& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
}

Vector2::~Vector2()
{

}

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>


Vector2 Vector2::PolarCoordinateWithOffset(Vector2 _current, float _direction, float _offset)
{
	return Vector2(_current.x + _offset * cos(_direction / 180.0f * glm::pi<float>()), _current.y + _offset * sin(_direction / 180.0f * glm::pi<float>()));
}

Vector2 Vector2::Clamp(Vector2 _val, Vector2 _min, Vector2 _max)
{
	if (_val.x > _max.x)
	{
		_val.x = _max.x;
	}
	else if(_val.x < _min.x)
	{
		_val.x = _min.x;
	}

	if (_val.y > _max.y)
	{
		_val.y = _max.y;
	}
	else if (_val.y < _min.y)
	{
		_val.y = _min.y;
	}

	return _val;
}