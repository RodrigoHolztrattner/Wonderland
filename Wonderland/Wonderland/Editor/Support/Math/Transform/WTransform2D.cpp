///////////////////////////////////////////////////////////////////////////////
// Filename: WTransform2D.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WTransform2D.h"

WTransform2D::WTransform2D()
{
}

WTransform2D::WTransform2D(const WTransform2D& other)
{
}

WTransform2D::~WTransform2D()
{
}

void WTransform2D::SetPosition(float _x, float _y)
{
	p_Position.x = _x;
	p_Position.y = _y;
}

void WTransform2D::SetPosition(Vector2 _position)
{
	p_Position = _position;
}

void WTransform2D::SetSize(float _x, float _y)
{
	p_Size.x = _x;
	p_Size.y = _y;
}

void WTransform2D::SetSize(Vector2 _size)
{
	p_Size = _size;
}

Vector2 WTransform2D::GetPosition()
{
	return p_Position;
}

Vector2 WTransform2D::GetSize()
{
	return p_Size;
}

//

bool WTransform2D::IsPointInside(Vector2 _point)
{
	// Check if the given point is inside this rect
	if (_point.x < p_Position.x || _point.y < p_Position.y || _point.x >(p_Position.x + p_Size.x) || _point.y >(p_Position.y + p_Size.y))
	{
		return false;
	}

	return true;
}