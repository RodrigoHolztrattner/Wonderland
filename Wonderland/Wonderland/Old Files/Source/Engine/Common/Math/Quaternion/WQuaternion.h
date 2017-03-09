////////////////////////////////////////////////////////////////////////////////
// Filename: WQuaternion.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WQuaternion_H_
#define _WQuaternion_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Primitive\WPrimitives.h"

/////////////
// DEFINES //
/////////////

// Pre declarations
class WVector2;
class WVector3;

////////////////////////////////////////////////////////////////////////////////
// Class name: WQuaternion
////////////////////////////////////////////////////////////////////////////////
class WQuaternion
{
private:

public:

	WQuaternion();
	WQuaternion(float _x, float _y, float _z, float _w);
	WQuaternion(WVector2 _vector2);
	WQuaternion(WVector3 _vector3);
	WQuaternion(const WQuaternion& other);
	~WQuaternion();

public:

	// Union with all types of values for this vector
	union
	{
		// For position, size, etc
		struct
		{
			Wfloat x, y, z, w;
		};

		// For color, pixel, etc
		struct
		{
			Wfloat a, b, c, d;
		};

		// Base
		Wfloat v[4];
	};

};

#endif
