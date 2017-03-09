///////////////////////////////////////////////////////////////////////////////
// Filename: WVector2.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WVector2.h"
#include "WVector3.h"
#include "WVector4.h"
#include <math.h>       /* sin / cos */

WVector2::WVector2()
{
}

WVector2::WVector2(float _x, float _y)
{
	v[0] = _x;
	v[1] = _y;
}

WVector2::WVector2(WVector3 _vector3)
{
	v[0] = _vector3.v[0];
	v[1] = _vector3.v[1];
}

WVector2::WVector2(WVector4 _vector4)
{
	v[0] = _vector4.v[0];
	v[1] = _vector4.v[1];
}

WVector2::WVector2(const WVector2& other)
{
	v[0] = other.v[0];
	v[1] = other.v[1];
}

WVector2::~WVector2()
{

}

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>


WVector2 WVector2::PolarCoordinateWithOffset(WVector2 _current, float _direction, float _offset)
{
	return WVector2(_current.x + _offset * cos(_direction / 180.0f * glm::pi<float>()), _current.y + _offset * sin(_direction / 180.0f * glm::pi<float>()));
}