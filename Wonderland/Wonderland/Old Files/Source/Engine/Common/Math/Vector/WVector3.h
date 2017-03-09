////////////////////////////////////////////////////////////////////////////////
// Filename: WVector3.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WVector3_H_
#define _WVector3_H_

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
class WVector4;

////////////////////////////////////////////////////////////////////////////////
// Class name: WVector3
////////////////////////////////////////////////////////////////////////////////
class WVector3
{
private:

public:
	WVector3();
	WVector3(float _x, float _y, float _z);
	WVector3(WVector2 _vector2);
	WVector3(WVector4 _vector4);
	WVector3(const WVector3& other);
	~WVector3();

public:

	// Union with all types of values for this vector
	union
	{
		// For position, size, etc
		struct
		{
			Wfloat x, y, z;
		};

		// For color, pixel, etc
		struct
		{
			Wfloat a, b, c;
		};

		// Base
		Wfloat v[3];
	};
};

#endif
