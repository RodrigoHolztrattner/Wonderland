///////////////////////////////////////////////////////////////////////////////
// Filename: WTransform3D.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WTransform3D.h"

WTransform3D::WTransform3D()
{
}

WTransform3D::WTransform3D(const WTransform3D& other)
{
}

WTransform3D::~WTransform3D()
{
}

void WTransform3D::SetPosition(float _x, float _y, float _z)
{
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
}

void WTransform3D::SetPosition(WVector3 _position)
{
	m_Position = _position;
}

void WTransform3D::SetSize(float _x, float _y, float _z)
{
	m_Size.x = _x;
	m_Size.y = _y;
	m_Size.z = _z;
}

void WTransform3D::SetSize(WVector3 _size)
{
	m_Size = _size;
}

void WTransform3D::SetRotation(WQuaternion _rotation)
{
	m_Rotation = _rotation;
}

WVector3 WTransform3D::GetPosition()
{
	return m_Position;
}

WVector3 WTransform3D::GetSize()
{
	return m_Size;
}

WQuaternion WTransform3D::GetRotation()
{
	return m_Rotation;
}