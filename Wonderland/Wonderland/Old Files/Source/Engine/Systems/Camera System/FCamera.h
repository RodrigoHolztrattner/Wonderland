////////////////////////////////////////////////////////////////////////////////
// Filename: FCamera.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FCamera_H_
#define _FCamera_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "Math\WMath.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FCamera
////////////////////////////////////////////////////////////////////////////////
class FCamera
{
private:

	// The far and near planes
	const float FarPlane = 1000.0f;
	const float NearPlane = 0.1f;

	// The PI value
	const float pi = 3.14159265358979323846f;

public:
	FCamera();
	FCamera(const FCamera&);
	~FCamera();

	// Update the camera (only the view matrix)
	void Update();

	// Create the projection matrix
	void CreateProjectionMatrix()
	{
		m_ProjectionMatrix.BuildPerspective(pi / 4.0f, m_ViewportSize.x / m_ViewportSize.y, NearPlane, FarPlane);
	}

	// Create the ortho matrix
	void CreateOrthoMatrix()
	{
		m_OrthoMatrix.BuildOrtho(pi / 4.0f, m_ViewportSize.x, m_ViewportSize.y, NearPlane, FarPlane);
	}

	// Set the look at vector
	void LookAt(WVector3 _lookAtVector);

	// Set the camera position
	void SetLocation(WVector3 _location)
	{
		m_WorldPosition = _location;
	}

	// Set the camera rotation
	void SetRotation(WVector3 _rotation)
	{
		m_WorldRotation = _rotation;
	}

	// Set the viewport size
	void SetViewportSize(WVector2 _viewportSize)
	{
		m_ViewportSize = _viewportSize;
	}

	// Return the view matrix
	WMatrix4* ViewMatrix();

	// Return the projection matrix
	WMatrix4* ProjectionMatrix();

	// Return the ortho matrix
	WMatrix4* OrthoMatrix();

private:

	// The view matrix
	WMatrix4 m_ViewMatrix;

	// The projection matrix
	WMatrix4 m_ProjectionMatrix;

	// The ortho matrix
	WMatrix4 m_OrthoMatrix;

	// The camera world position
	WVector3 m_WorldPosition;

	// The camera world rotation
	WVector3 m_WorldRotation;

	// The look at vector
	WVector3 m_LookAt;

	// The viewport size
	WVector2 m_ViewportSize;
};

#endif
