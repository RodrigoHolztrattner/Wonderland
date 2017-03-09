///////////////////////////////////////////////////////////////////////////////
// Filename: FCamera.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FCamera.h"

FCamera::FCamera()
{
	// Set the initial data
	m_WorldPosition = WVector3(0, 0, 0);
	m_WorldRotation = WVector3(0, 0, 0);
	m_LookAt = WVector3(0, 0, 1.0f);
}

FCamera::FCamera(const FCamera& other)
{
}

FCamera::~FCamera()
{
}

void FCamera::LookAt(WVector3 _lookAtVector)
{
	m_LookAt = _lookAtVector;
}

WMatrix4* FCamera::ViewMatrix()
{
	return &m_ViewMatrix;
}

WMatrix4* FCamera::ProjectionMatrix()
{
	return &m_ProjectionMatrix;
}

WMatrix4* FCamera::OrthoMatrix()
{
	return &m_OrthoMatrix;
}

void FCamera::Update()
{
	// The update only build the view matrix (ortho and projection are up to you)
	// m_ViewMatrix.BuildView(WVector2(m_WorldPosition.x - m_ViewportSize.x / 2.0, m_WorldPosition.y - m_ViewportSize.y / 2.0), m_WorldRotation, m_LookAt, WVector3(0, 1.0f, 0));
}