////////////////////////////////////////////////////////////////////////////////
// Filename: WTransform3D.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WTransform3D_H_
#define _WTransform3D_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Vector\WVector2.h"
#include "..\Vector\WVector3.h"
#include "..\Quaternion\WQuaternion.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: WTransform3D
////////////////////////////////////////////////////////////////////////////////
class WTransform3D
{
private:

public:
	WTransform3D();
	WTransform3D(const WTransform3D&);
	~WTransform3D();

	// Set the position
	void SetPosition(float _x, float _y, float _z);
	void SetPosition(WVector3 _position);

	// Set the size
	void SetSize(float _x, float _y, float _z);
	void SetSize(WVector3 _size);

	// Set the rotation
	void SetRotation(WQuaternion _rotation);

	// Return the position / size / rotation
	WVector3 GetPosition();
	WVector3 GetSize();
	WQuaternion GetRotation();

protected:

	// The position
	WVector3 m_Position;

	// The size
	WVector3 m_Size;

	// The rotation
	WQuaternion m_Rotation;
};

#endif
