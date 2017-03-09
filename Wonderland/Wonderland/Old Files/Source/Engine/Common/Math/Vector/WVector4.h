////////////////////////////////////////////////////////////////////////////////
// Filename: WVector4.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WVector4_H_
#define _WVector4_H_

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
// Class name: WVector4
////////////////////////////////////////////////////////////////////////////////
class WVector4
{
private:

public:

	WVector4();
	WVector4(float _x, float _y, float _z, float _w);
	WVector4(WVector2 _vector2);
	WVector4(WVector3 _vector3);
	WVector4(const WVector4& other);
	~WVector4();

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
